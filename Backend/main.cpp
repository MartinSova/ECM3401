#include "daemon.h"
#include "localmanager.h"
#include "connection.h"
#include "filemanager.h"
#include "filemodmanager.h"
#include "statusmanager.h"
#include "heartbeat.h"
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <limits.h>
#include <sys/inotify.h>
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <usb.h>
#include <typeinfo>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <cstdlib>
#include <errno.h>
#include <error.h>
#include <pwd.h>
#include <poll.h>
#include <time.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
// target volume must be format HPFS/NTFS or ____ (any other viable types?)
//#include "mainwindow.h"
// #include <QApplication>

using namespace std;
using namespace boost::filesystem;
using namespace boost::system;

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

static int daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0) {
        StatusManager::writePid(getppid());
        exit(EXIT_SUCCESS);
    }

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/home/martin/ECM3401"); // LATER CHANGE CODE TO AUTOMATICALLY GET CURRENT LOCATION OF MAIN.CPP

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close (x);
    }

    /* Open the log file */
    openlog ("dissertation", LOG_PID, LOG_DAEMON);
    return 0;
}

/**
 * @brief wakeup
 * a method to be called every time daemon wakes up
 * not necessariyl when backup cycles supposed to happen
 */

void wakeup()
{
    filemanager::existsConfigurationFile();
    filemanager::existsStatusFile();
}

/**
 * @brief initiate
 * a method that is run when application first started
 */
void initiate()
{
    filemanager::existsConfigurationFile();
    filemanager::existsStatusFile();
    //filemanager::existsFileModFile();
    deviceIds connectedRegistered = LocalManager::availableRegisteredDevices();;
    deviceIds connectedNotRegistered = LocalManager::availableNotRegisteredDevices();
    StatusManager::overwriteConnectedDevices(connectedNotRegistered, "notRegisteredDevices");
}

int getdir(string rootDir, vector<string> &files)
{
    DIR *dir; //the directory
    struct dirent *dp;

    //open the directory
    if((dir  = opendir(rootDir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << rootDir << endl;
        return errno;
    }

    while ((dp = readdir(dir)) != NULL) {
        files.push_back(string(dp->d_name));


        //if(directory do something) //need help here

        //if(file do something else)
    }
    closedir(dir);
    return 0;
}

bool containsPath(vector<path> pathVector, path p2)
{
    if (find(pathVector.begin(), pathVector.end(), p2) != pathVector.end()) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    syslog (LOG_NOTICE, "-----------------------------------------");
    // initiate method for before daemon starts
    initiate();
    // start daemon
    daemon();
    syslog(LOG_NOTICE, "DAEMON STARTING ...");

    // initiate inotify
    int fd;
    int wd[2], len, i;
    int numDir = 0;

    char buf[sizeof(struct inotify_event) + PATH_MAX];
    if ((fd = inotify_init()) < 0)
        error(EXIT_FAILURE, errno, "failed to initialize inotify instance");
    /*
    if ((wd[0] = inotify_add_watch (fd, "itests", IN_MODIFY)) < 0) {
        syslog(LOG_ERR, "failed to add inotify watch for itests");
    }
    if ((wd[1] = inotify_add_watch (fd, "itests2", IN_MODIFY)) < 0) {
        syslog(LOG_ERR, "failed to add inotify watch for itests2");
    }
    */
    // add watch to all current directories


    string rootDirectory = "/home/martin/Desktop/Tests/";
    filemanager::existsFileModFile();

    for(auto& p: recursive_directory_iterator(rootDirectory)) {
        try {
            if (is_directory(p)) {
                const char *s = p.path().c_str();
                syslog(LOG_NOTICE, "%s", s);
                if ((wd[numDir] = inotify_add_watch (fd, s, IN_MODIFY | IN_DELETE | IN_CREATE | IN_ATTRIB)) < 0) {
                    //syslog(LOG_ERR, "failed to add inotify watch for '%s'", s);
                } else {
                    FileModManager::writeWatchDesc(wd[numDir], string(s));
                    //syslog(LOG_NOTICE, "wd int is: %d'", wd[numDir]);
                    //syslog(LOG_NOTICE, "and pathname is %s", canonical(p).c_str());
                    numDir++;
                }
            }
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

    int count = 0;
    string toRemove1;
    string toRemove2;
    string devicePath = "/media/martin/DISK_IMG/DISSERTATION/";
    int backupFrequency;


    while (count < 12) {

        FileModManager::update();

        syslog(LOG_NOTICE, "count: %d", count);
        vector<string> modifiedFiles;
        struct pollfd pfd = {fd, POLLIN, 0};
        int ret = poll(&pfd, 1, 0);  // timeout of 50ms
        if (ret < 0) {
            fprintf(stderr, "poll failed: %s\n", strerror(errno));
        } else if (ret == 0) {
           // Timeout with no events, move on.
        } else {
            wakeup();
            vector<pair<int,string>> currentWatchDesc = FileModManager::readAllWatchDesc();
            len = read(fd, buf, sizeof(buf));
            i = 0;
            while (i < len) {
                struct inotify_event *ie = (struct inotify_event*) &buf[i];
                if (ie->mask & IN_MODIFY | ie->mask & IN_CREATE | ie->mask & IN_DELETE | ie->mask & IN_ATTRIB) {
                    string toWrite;
                    for(const auto& wd : currentWatchDesc)
                    {
                        if (wd.first == ie->wd) {
                            toWrite = (wd.second + "/" + ie->name);
                            modifiedFiles.push_back(toWrite);
                            break;
                        }
                    }
                    syslog(LOG_NOTICE, "%s file was modified\n", toWrite.c_str());

                    if ( ie->mask & IN_ISDIR ) {
                        string p = toWrite;
                        syslog(LOG_NOTICE, "%s directory was modified", p.c_str());

                        try {
                            if (is_directory(p)) {
                                const char *s = p.c_str();
                                syslog(LOG_NOTICE, "%s watch added", s);
                                if ((wd[numDir] = inotify_add_watch (fd, s, IN_MODIFY | IN_DELETE | IN_CREATE)) < 0) {
                                    //syslog(LOG_ERR, "failed to add inotify watch for '%s'", s);
                                } else {
                                    FileModManager::writeWatchDesc(wd[numDir], string(s));
                                    //syslog(LOG_NOTICE, "wd int is: %d'", wd[numDir]);
                                    //syslog(LOG_NOTICE, "and pathname is %s", canonical(p).c_str());
                                    numDir++;
                                }
                            }
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
                }
                i += sizeof(struct inotify_event) + ie->len;
            }
        // create backup
        }

        if (!modifiedFiles.empty()) {
            FileModManager::writeModFiles(modifiedFiles);
        }
        /*
        deviceIds registeredDeviceIds = ConfigManager::allRegisteredDeviceIds();
        deviceIds availableRegisteredDevices = LocalManager::availableRegisteredDevices();

        for (pair<int, int> dev : registeredDeviceIds) {
            //syslog(LOG_NOTICE, "dev VID is %i", dev.first);
            //syslog(LOG_NOTICE, "dev Pid is %i", dev.second);
            if(find(availableRegisteredDevices.begin(), availableRegisteredDevices.end(), dev) != availableRegisteredDevices.end()) {
                // convert dec to hex
                string hexVID = LocalManager::getHexadecimalValue(dev.first);
                string hexPID = LocalManager::getHexadecimalValue(dev.second);
                LocalManager::getPathToMountedDevices(hexVID, hexPID);
                syslog(LOG_NOTICE, "hex val of available device vendor id is %s", hexVID.c_str());
                syslog(LOG_NOTICE, "hex val of available device product id is %s", hexPID.c_str());
            } else {

            }
        }
        */
        //for (pair<int, int> avDev : availableRegisteredDevices) syslog(LOG_NOTICE, "available device vendor id is %i", avDev.first);

        //for (pair<int, int> avDev : availableRegisteredDevices) syslog(LOG_NOTICE, "available device product id is %i", avDev.second);
        syslog(LOG_NOTICE, "before prepare backup directory");


        heartbeat::prepareBackupDirectory(); // does it actually make sense to write to json is passed straight away?

        if (count == 9) {
                toRemove1 = devicePath + ConfigManager::readLastBackupDir();
        }
        if (count == 11) {
                toRemove2 = devicePath + ConfigManager::readLastBackupDir();
                syslog(LOG_NOTICE, "%s to remove1", toRemove1.c_str());
                syslog(LOG_NOTICE, "%s to remove2", toRemove2.c_str());
                remove_all(toRemove1);
                remove_all(toRemove2);


        }
        count++;
        ifstream backup("/home/martin/build-ECM3401-Desktop_Qt_5_7_0_GCC_64bit-Debug/backupFrequency");
        std::string content( (std::istreambuf_iterator<char>(backup) ),
                               (std::istreambuf_iterator<char>()    ) );
        backupFrequency = stoi(content.c_str());
        sleep(backupFrequency);
    }

    syslog (LOG_NOTICE, "EXITING ...");
    exit(0);
    //error(EXIT_FAILURE, len == 0 ? 0 : errno, "failed to read inotify event");
}







/*
if (availableDevices == nullptr) {
    cerr << "Init Error" << r << endl; //there was an error
    return 1;
}
*/

//libusb_free_device_list(devs, 1); //free the list, unref the devices in it


/*
device registered and connected? yes? do ---->
no? ------> canBeRegistered and see if viable for registtration
*/

