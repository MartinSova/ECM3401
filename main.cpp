#include "daemon.h"
#include "localmanager.h"
#include "connection.h"
#include "filemanager.h"
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
#include <poll.h>

using namespace std;

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
    pair<deviceIds, deviceIds> availableDevices = getAvailableDevices();
    deviceIds connectedRegistered = availableDevices.first;
    deviceIds connectedNotRegistered = availableDevices.second;
    StatusManager::overwriteConnectedDevices(connectedNotRegistered, "notRegisteredDevices");
}

int main(int argc, char *argv[])
{
    initiate();
    daemon();


    int fd, wd, len, i;
        char buf[sizeof(struct inotify_event) + PATH_MAX];

        if (argc < 2)
            error(EXIT_FAILURE, 0, "missing argument");

        if ((fd = inotify_init()) < 0)
            error(EXIT_FAILURE, errno, "failed to initialize inotify instance");

        for (i = 1; i < argc; i++) {
             if ((wd = inotify_add_watch (fd, argv[i],
                                          IN_MODIFY | IN_CREATE | IN_DELETE)) < 0)
                 error(EXIT_FAILURE, errno,
                       "failed to add inotify watch for '%s'", argv[i]);
        }
syslog (LOG_NOTICE, "daemon started.");
        int count = 0;
        while (count < 4)
        {
        syslog (LOG_NOTICE, "count: %d", count);
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
                             struct inotify_event *ie = (struct inotify_event*) &buf[i];

                             printf("event occured for '%s': ", argv[ie->wd]);
                             if (ie->mask & IN_MODIFY)
                        syslog (LOG_NOTICE, "%s was modified\n", ie->len ? ie->name : "file");

                             else if (ie->mask & IN_CREATE)
                                 syslog (LOG_NOTICE, "%s was created\n",  ie->name);
                             else if (ie->mask & IN_DELETE)
                                 syslog (LOG_NOTICE, "%s was deleted\n",  ie->name);
                             else
                                 syslog (LOG_NOTICE, "unexpected event\n");

                             i += sizeof(struct inotify_event) + ie->len;
                         }


            }
            //heartbeat();
            count++;
            sleep(10);
            //break;
        }

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




