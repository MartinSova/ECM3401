#include "daemon.h"
#include "localmanager.h"
#include "connection.h"
#include "filemanager.h"
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <usb.h>
#include <typeinfo>

using namespace std;

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{

    filemanager::existsConfiguration();
    filemanager::existsStatus();

    ConfigManager::registeredDevices();

    // initiate usb library
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *ctx = NULL; //a libusb session
    int r; //for return values
    ssize_t count; //holding number of devices in list

    r = libusb_init(&ctx); //initialize a library session
    if(r < 0) {
        cout<<"Init Error "<<r<<endl; //there was an error
            return 1;
    }
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation

    //localManager l;
    pair<deviceIds, deviceIds> connectedDevices = localManager().availableDevices(ctx, devs);

    //l.canBeRegistered(ctx, devs, r, connectedDevices.);

/*
    libusb_register_hotplug_listeners(ctx, deviceAdded, deviceRemoved, 0);

    while(1) libusb_handle_events(ctx);
*/
    //libusb_free_device_list(devs, 1); //free the list, unref the devices in it






/*


    libusb_hotplug_callback_handle
            handle;
    cout << typeid(handle).name() << '\n';
      int rc;
      libusb_init(NULL);

      rc = libusb_hotplug_register_callback(NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED |
                                            LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, 0, 0x045a, 0x5005,
                                            LIBUSB_HOTPLUG_MATCH_ANY, hotplug_callback, NULL,
                                            &handle);

    if (LIBUSB_SUCCESS != rc) {
        printf("Error creating a hotplug callback\n");
        libusb_exit(NULL);
        return EXIT_FAILURE;
      }
      while (count < 2) {
        libusb_handle_events_completed(NULL, NULL);
        usleep(10000);
      }
      libusb_hotplug_deregister_callback(NULL, handle);

*/

    libusb_hotplug_callback_handle hp[2];
    int product_id, vendor_id, class_id;
    int rc;

    int done = 0;


    libusb_init (NULL);

    if (!libusb_has_capability (LIBUSB_CAP_HAS_HOTPLUG)) {
      printf ("Hotplug not supported by this build of libusb\n");
      libusb_exit (NULL);
      return EXIT_FAILURE;
    }

    rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,
                                           LIBUSB_HOTPLUG_NO_FLAGS , LIBUSB_HOTPLUG_MATCH_ANY,
                                           LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, connection::hotplug_callback, NULL, &hp[0]);
    if (LIBUSB_SUCCESS != rc) {
      fprintf (stderr, "Error registering callback 0\n");
      libusb_exit (NULL);
      return EXIT_FAILURE;
    }

    rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
                                           LIBUSB_HOTPLUG_NO_FLAGS , LIBUSB_HOTPLUG_MATCH_ANY,
                                           LIBUSB_HOTPLUG_MATCH_ANY,LIBUSB_HOTPLUG_MATCH_ANY, connection::hotplug_callback_detach, NULL, &hp[1]);
    if (LIBUSB_SUCCESS != rc) {
      fprintf (stderr, "Error registering callback 1\n");
      libusb_exit (NULL);
      return EXIT_FAILURE;
    }

    while (true) {
      libusb_handle_events (NULL);
    }

    libusb_exit(ctx); //close the session


    return 0;

    /*

    device registered and connected? yes? do ---->
    no? ------> canBeRegistered and see if viable for registtration
    */

}
