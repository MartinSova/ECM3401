#include "heartbeat.h"


void heartbeat::prepareBackupDirectory()
{ 
    syslog(LOG_NOTICE, "inside prepare backup directory");
    /*
    const char dir_path[] = "c:\\home\\martin\\Documents\\newdir";

    path dir(dir_path);
    if(!create_directory(dir)) {
        syslog(LOG_ERR, "Directory could not be created.");
    }
    */

    //char *devicePath = "/media/" + username;
    //string devicePath = "C:/media/martin/DISK_IMG/";

    /* *

    However, in the future I will need to make sure that a specific
    usb drive is written to (despite the name as names of usb drives
    can be the same). Right now I will identify a usb drive simply by its
    name.
    */
    //deviceIds connectedRegistered = LocalManager::availableRegisteredDevices();

    //vector<string> allModFiles = FileModManager::readAllModFiles();

    // first create entire filesystem and hard link all files from last backup
    // and then copy new modified files and omit any from filesToOmit/directoriesToOmit

    /*
    create new directory
    */

    //deviceIds allRegisteredDevices = ConfigManager::allRegisteredDeviceIds();
    /*
    for(auto const& device : connectedRegistered) {

    }
    int count = 0;
    */
    /*
    for(auto const& device : connectedNotRegistered) {
        syslog(LOG_NOTICE, "vendorId connected not registered %d", device.first);
        syslog(LOG_NOTICE, "productId connected not registered %d", device.second);
        count ++;
    }
    syslog(LOG_NOTICE, "total: %d", count);
    */

    // make method to get device path
    string devicePath = "/media/martin/DISK_IMG/DISSERTATION/";
    string rootDirectory = "/home/martin/Desktop/Tests";
    // still make method to get last backup directory name
    string lastBackupDirName = ConfigManager::readLastBackupDir(); // getLastBackupDirName();

    string newDirName = getNewDirName();
    ConfigManager::writeLastBackupDir(newDirName);
    // LocalManager::writeLastBackupDirName(gmtTime, machineTime);


    //create_directories(devicePath + newDirName);

    //create_directories(devicePath + newDirName + "/home/martin/ECM3401");


    if (!exists(devicePath + lastBackupDirName)) {
        syslog(LOG_NOTICE, "before creating hard copy");
        createHardCopy(rootDirectory, devicePath + newDirName);
    } else {
        hardlinkLastBackup(rootDirectory, devicePath, devicePath + lastBackupDirName, devicePath + newDirName);
        copyModifiedFiles(rootDirectory, devicePath + newDirName);
    }


    /*
    string newDirName = getNewDirName();
    ConfigManager::writeLastBackupDir(newDirName);
    string lastBackupDirName2 = ConfigManager::readLastBackupDir();
    syslog(LOG_NOTICE, "%s last dir name", lastBackupDirName2.c_str());
    */
    /*
    for(auto& p: recursive_directory_iterator(devicePath + oldDirName)) {
        // check if device still connected in each iteration
        // how to deal with this if disconnected half way through?
        path pathToCreate = devicePath + newDirName + p.path().string().substr((devicePath + oldDirName).length());
        if (is_directory(p)) {
            if(!create_directories(pathToCreate)) {
                syslog(LOG_ERR, "%s directory path could not be created.", pathToCreate.c_str());
            } else {}
        } else {
            path filePath = p.path();
            if (link(p.c_str(), pathToCreate.c_str()) != 0) {
                syslog(LOG_ERR, "%s file path could not be created.", pathToCreate.c_str());
            }
        }
    }
    */
}
/*
path heartbeat::getPath(string devicePath, string p, string newDirName) {
    string currPath = p.substr();
    path rootPath (devicePath + newDirName + p.path().string());
    return devicePath +

}
*/

string heartbeat::getNewDirName() {
    string rootDirName = LocalManager::currentLocalTime();
    return rootDirName;
}
/*
void heartbeat::copyTreeStructure() {

}
*/

void heartbeat::createHardCopy(const path &src, const path &dst) {
    syslog(LOG_NOTICE, "inside create hard copy");
    if (is_directory(src)) {
        create_directories(dst);
        for (directory_entry& item : directory_iterator(src)) {
            createHardCopy(item.path(), dst/item.path().filename());
        }
    } else if (is_regular_file(src)) {
        copy(src, dst);
    } else {
        throw runtime_error(dst.generic_string() + " not dir or file");
    }

    /*
    syslog(LOG_NOTICE, "inside create hard copy");
    for(auto& p: recursive_directory_iterator("/home/martin/ECM3401")) { 
        try {
            string destinationPath = devicePath + canonical(p).string();
            syslog(LOG_NOTICE, "source directory: %s", canonical(p).c_str());
            syslog(LOG_NOTICE, destination directory: %s", destinationPath.c_str());
            copy(p, destinationPath);
        } catch(const filesystem_error& e) {
            if(e.code() == errc::permission_denied) {
               std::cout << "Search permission is denied for one of the directories "
                         << "in the path prefix of " << p << "\n";
           } else {
               std::cout << "is_directory(" << p << ") failed with "
                         << e.code().message() << '\n';
           }
        }
    }
    */
}

void heartbeat::hardlinkLastBackup(const path &rootDirectory, const path &devicePath, const path &src, const path &dst) {


    //syslog(LOG_NOTICE, "source path for copy: %s", src.c_str());
    //syslog(LOG_NOTICE, "destination path for copy: %s", dst.c_str());

    if (exists(dst)) {
        throw runtime_error(dst.generic_string() + " exists");
    }
    if (is_directory(src)) {
        create_directories(dst);
        for (directory_entry& item : directory_iterator(src)) {
            hardlinkLastBackup(rootDirectory, devicePath, item.path(), dst/item.path().filename());
        }
    } else if (is_regular_file(src)) {
        //syslog(LOG_NOTICE, "creating hardlink is: %s", dst.c_str());
        create_hard_link(src, dst);
    } else {
        throw runtime_error(dst.generic_string() + " not dir or file");
    }

}

void heartbeat::copyModifiedFiles(const path &rootDirectory, const path &devicePath) {
    // SORT DIRECTORIES BY SHORTEST TO LONGER BEFORE ANY ACTION SO THAT
    // SUBDIRECTORIES GET COPID LAST TO PREVENT ISSUES
    vector<string> modifiedFilePaths = FileModManager::readAllModFiles();
    compare c;
    sort(modifiedFilePaths.begin(), modifiedFilePaths.end(), c);

    for (auto &path : modifiedFilePaths) {

        string withoutRoot = path.substr(rootDirectory.string().length(), path.length());
        string destinationPath = devicePath.string() + withoutRoot;
        //syslog(LOG_NOTICE, "destination modified file path: %s", destinationPath.c_str());
        //syslog(LOG_NOTICE, "source modified file path: %s", path.c_str());


        // edit to that directories can also be modified (user permissions updated and such)
        if (exists(path)) {
            if (is_directory(path)) {
                if (!exists(destinationPath)) {
                    syslog(LOG_NOTICE, "about to create new directory of path: %s", destinationPath.c_str());
                    create_directories(destinationPath);
                    continue;
                }
            }
        } else if (exists(destinationPath)) {
            if (is_directory(destinationPath)) {
                if (!exists(path)) {
                    remove_all(destinationPath);
                    continue;
                }
            }
       } else if (exists(destinationPath)) {
            if (is_directory(destinationPath)) {
                if (exists(path)) {
                    struct stat attr;

                    time_t mtime;
                    struct utimbuf new_times;
                    stat(path.c_str(), &attr);
                    mtime = attr.st_mtime;
                    new_times.actime = attr.st_atime; /* keep atime unchanged */
                    new_times.modtime = attr.st_mtime;    /* set mtime to current time */
                    syslog(LOG_NOTICE, "Last modified time: %s", ctime(&attr.st_mtime));
                    copy(path, destinationPath);
                    utime(destinationPath.c_str(), &new_times);
                    continue;
                }
            }
        }

        if (exists(destinationPath)) {
            remove(destinationPath);
        }
        if (exists(path)) {
            //getFileCreationTime(path.c_str());
            syslog(LOG_NOTICE, "destination path to remove: %s", destinationPath.c_str());
            syslog(LOG_NOTICE, "source path to remove: %s", path.c_str());
            struct stat attr;

            time_t mtime;
            struct utimbuf new_times;
            stat(path.c_str(), &attr);
            mtime = attr.st_mtime;
            new_times.actime = attr.st_atime; /* keep atime unchanged */
            new_times.modtime = attr.st_mtime;    /* set mtime to current time */
            syslog(LOG_NOTICE, "Last modified time: %s", ctime(&attr.st_mtime));
            copy(path, destinationPath);
            utime(destinationPath.c_str(), &new_times);

        }

    }
}

void heartbeat::getFileCreationTime(const char *path) {
    struct stat attr;
    stat(path, &attr);
    syslog(LOG_NOTICE, "Last modified time: %s", ctime(&attr.st_mtime));
}

void heartbeat::backupModFiles(vector<string> allModifiedFiles)
{
    vector<tuple<int, int, vector<string>>> allRegisteredDevices = ConfigManager::allRegisteredDevices();
    for(auto const& regDevice : allRegisteredDevices) {
        int vendorId = get<0>(regDevice);
        //syslog(LOG_NOTICE, "vendor id %d", vendorId);
        int productId = get<1>(regDevice);
        //syslog(LOG_NOTICE, "product id %d", productId);
        vector<string> filesToOmit = get<2>(regDevice);
        for(auto const& file : filesToOmit) {
            //syslog(LOG_NOTICE, "file to omit %s", file.c_str());
        }
    }
}


