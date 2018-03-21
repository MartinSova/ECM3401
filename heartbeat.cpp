#include "heartbeat.h"

/*
*/
void heartbeat::prepareBackupDirectory()
{
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

    // still make method to get last backup directory name
    string lastBackupDirName = "hardcopy"; // getLastBackupDirName();

    string newDirName = "testhardlink3"; //getNewDirName();

    //create_directories(devicePath + newDirName);

    //create_directories(devicePath + newDirName + "/home/martin/ECM3401");

    //createHardCopy("/home/martin/ECM3401", "/media/martin/DISK_IMG/DISSERTATION/" + lastBackupDirName);
    hardlinkLastBackup(devicePath + lastBackupDirName, devicePath + newDirName);
    /*
    if (!exists(devicePath) || lastBackupDirName.empty()) {
        if(!create_directories(devicePath + "/" + newDirName)) {
            syslog(LOG_ERR, "%s directory path could not be created.", devicePath.c_str());
        } else {
            createHardCopy(devicePath + "/" + newDirName);
            syslog(LOG_NOTICE, "dissertation directory created");
        }
    } else {
        syslog(LOG_NOTICE, "dissertation directory already exists");
    }
    */
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
    if (exists(dst)) {
        throw runtime_error(dst.generic_string() + " exists");
    }
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
            syslog(LOG_NOTICE, "destination directory: %s", destinationPath.c_str());
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

void heartbeat::hardlinkLastBackup(const path &src, const path &dst) {
    if (exists(dst)) {
        throw runtime_error(dst.generic_string() + " exists");
    }
    if (is_directory(src)) {
        create_directories(dst);
        for (directory_entry& item : directory_iterator(src)) {
            hardlinkLastBackup(item.path(), dst/item.path().filename());
        }
    } else if (is_regular_file(src)) {
        syslog(LOG_NOTICE, "creating hardlink is: %s", dst.c_str());
        //copy(src, dst);
        create_hard_link(src, dst);
        //link(src.c_str(), dst.c_str());
    } else {
        throw runtime_error(dst.generic_string() + " not dir or file");
    }
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


