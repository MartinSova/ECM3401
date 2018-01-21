#include "daemon.h"
#include "localmanager.h"
#include "connection.h"
#include "filemanager.h"
#include "statusmanager.h"
#include <iostream>
#include <libusb-1.0/libusb.h>
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

using namespace std;

#define BUF_SIZE 1024



static void daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

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
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("dissertation", LOG_PID, LOG_DAEMON);
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
    pair<deviceIds, deviceIds> connectedDevices = localManager::availableDevices(ctx, devs);
    return connectedDevices;
}

int main(int argc, char *argv[])
{
    deviceIds myvector;

    myvector.push_back(make_pair(000000,00000000));

    StatusManager::writeConnectedDevices(myvector, true);
    syslog (LOG_NOTICE, "HEY.");
    /*
    daemon();
    int count = 0;
    while (count < 3)
    {
        //TODO: Insert daemon code here.
        syslog (LOG_NOTICE, "d daemon started.");




        //connection *c = new connection();



        //filemanager::existsConfigurationFile();
        //filemanager::existsStatusFile();
        //pair<deviceIds, deviceIds> availableDevices = getAvailableDevices();

        sleep (20);

        count++;
        //break;
    }
    syslog (LOG_NOTICE, "d daemon terminated.");


    */
    closelog();
    return EXIT_SUCCESS;

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
}


