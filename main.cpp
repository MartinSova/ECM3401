#include "daemon.h"
#include "localmanager.h"
#include "connection.h"
#include "filemanager.h"
#include "filemodmanager.h"
#include "statusmanager.h"
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
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace boost::system;

/*
inodes unique only on same partition, so when getting inode must from that specific partition
*/

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
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("dissertation", LOG_PID, LOG_DAEMON);
    return 0;
}

pair<deviceIds, deviceIds> getAvailableDevices()
{
    // initiate usb library
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *ctx = NULL; //a libusb session
    int r; //for return values
    r = libusb_init(&ctx); //initialize a library session
    if(r < 0) {
        nullptr;
    }
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
    pair<deviceIds, deviceIds> connectedDevices = LocalManager::availableDevices(ctx, devs);
    return connectedDevices;
}

/**
 * @brief heartbeat
 * a method to be called every time daemon wakes up
 */

void heartbeat()
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
    pair<deviceIds, deviceIds> availableDevices = getAvailableDevices();
    deviceIds connectedRegistered = availableDevices.first;
    deviceIds connectedNotRegistered = availableDevices.second;
    StatusManager::overwriteConnectedDevices(connectedNotRegistered, "notRegisteredDevices");
}

int getdir(string rootDir, vector<string> &files)
{
    DIR *dir; //the directory
    struct dirent *dp;

    //open the directory
    if((dir  = opendir(rootDir.c_str())) == NULL)
    {
        cout << "Error(" << errno << ") opening " << rootDir << endl;
        return errno;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        files.push_back(string(dp->d_name));


        //if(directory do something) //need help here

        //if(file do something else)
    }

    closedir(dir);
    return 0;
}

bool containsPath(vector<path> pathVector, path p2)
{
    if (find(pathVector.begin(), pathVector.end(), p2) != pathVector.end())
    {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[])
{
    // initiate method for before daemon starts
    initiate();
    // start daemon
    daemon();
    syslog (LOG_NOTICE, "-------------------");
    syslog (LOG_NOTICE, "DAEMON STARTING ...");

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

    for(auto& p: recursive_directory_iterator("/home/martin/ECM3401")) {
        try {
            if (is_directory(p)) {
                const char *s = p.path().c_str();
                //syslog(LOG_NOTICE, "%s", s);
                if ((wd[numDir] = inotify_add_watch (fd, s, IN_MODIFY | IN_DELETE)) < 0) {
                    syslog(LOG_ERR, "failed to add inotify watch for '%s'", s);
                } else {
                    /FileModManager::write(wd[numDir], string(s));
                    syslog(LOG_NOTICE, "wd int is: %d'", wd[numDir]);
                    syslog(LOG_NOTICE, "and pathname is");
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
    while (count < 4) {
        filemanager::existsFileModFile();
        syslog(LOG_NOTICE, "count: %d", count);
        struct pollfd pfd = {fd, POLLIN, 0};
        int ret = poll(&pfd, 1, 0);  // timeout of 50ms
        if (ret < 0) {
            fprintf(stderr, "poll failed: %s\n", strerror(errno));
        } else if (ret == 0) {
            // Timeout with no events, move on.
        } else {
            len = read(fd, buf, sizeof(buf));
            i = 0;
            while (i < len) {
                syslog(LOG_NOTICE, "%d", i);
                struct inotify_event *ie = (struct inotify_event*) &buf[i];
                if (ie->mask & IN_MODIFY) {
                    if ( ie->mask & IN_ISDIR ) {
                        syslog(LOG_NOTICE, "directory was modified");
                    } else {
                        syslog(LOG_NOTICE, "%s file was modified\n", ie->name);
                        syslog(LOG_NOTICE, "%d wd was modified\n", ie->wd);
                    }
                }
                i += sizeof(struct inotify_event) + ie->len;

                //FileModManager::sort(&fd, &buf);
                //FileModManager::write(struct inotify_event *ie);
            }
        }



        count++;
        sleep(10);
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

