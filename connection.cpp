#include "connection.h"

int done = 0;
libusb_device_handle *handle;

libusb_hotplug_callback_handle hp[2];
int rc;

using namespace std;

libusb_context *ctx;
libusb_device *dev;
libusb_hotplug_event event;
void *user_data;

/**
 * @brief Connection::Connection
 * this class will be moved as part of the frontend classes (as new connection only concern frontend)
 */
Connection::Connection()
{
    libusb_init (NULL);

    if (!libusb_has_capability (LIBUSB_CAP_HAS_HOTPLUG)) {
      printf ("Hotplug not supported by this build of libusb\n");
      libusb_exit (NULL);
      //return EXIT_FAILURE;
    }

    rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,
                                           LIBUSB_HOTPLUG_NO_FLAGS , LIBUSB_HOTPLUG_MATCH_ANY,
                                           LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, hotplug_callback, NULL, &hp[0]);
    if (LIBUSB_SUCCESS != rc) {
      fprintf (stderr, "Error registering callback 0\n");
      libusb_exit (NULL);
      //return EXIT_FAILURE;
    }

    rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
                                           LIBUSB_HOTPLUG_NO_FLAGS , LIBUSB_HOTPLUG_MATCH_ANY,
                                           LIBUSB_HOTPLUG_MATCH_ANY,LIBUSB_HOTPLUG_MATCH_ANY, hotplug_callback_detach, NULL, &hp[1]);
    if (LIBUSB_SUCCESS != rc) {
      fprintf (stderr, "Error registering callback 1\n");
      libusb_exit (NULL);
      //return EXIT_FAILURE;
    }

    while (1) libusb_handle_events (NULL);

    libusb_exit(ctx); //close session



}

int Connection::hotplug_callback (libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {
  syslog (LOG_INFO, "CONNECTION DETECTED.");
  struct libusb_device_descriptor desc;
  int rc;

  rc = libusb_get_device_descriptor(dev, &desc);
  if (LIBUSB_SUCCESS != rc) {
    fprintf (stderr, "Error getting device descriptor\n");
  }

  pair<int,int> connectedDevice = make_pair(desc.idVendor, desc.idProduct);

  if(ConfigManager::isRegistered(connectedDevice)) {
      StatusManager::appendConnectedDevice(connectedDevice, "registeredDevices");
  } else {
      pair<bool,string> canRegister = canBeRegistered(connectedDevice);
      // if device is viable for registration (can be written to or has enough space)
      if (canRegister.first) StatusManager::appendConnectedDevice(connectedDevice, canRegister.second);
  }

  //printf ("Device attach: %04x:%04x\n", desc.idVendor, desc.idProduct);

  //libusb_open (dev, &handle);

  return 0;
}

int Connection::hotplug_callback_detach (libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {
  printf ("Device detached\n");

  //libusb_close (handle);

  return 0;
}


pair<bool, string> Connection::canBeRegistered(pair<int,int> devId)
{
    /* Any file on the filesystem in question */

    /*
    const char *filename = "/";

    struct statvfs buf;

    if (!statvfs(filename, &buf))
    {
    unsigned long blksize, blocks, freeblks, disk_size, used, free;

    blksize = buf.f_bsize;
    blocks = buf.f_blocks;
    freeblks = buf.f_bfree;

    disk_size = blocks * blksize;
    free = freeblks * blksize;
    used = disk_size - free;

    printf("Disk usage : %lu GB\t Free space %lu GB\n", used/1000000000, free/1000000000);

    } else {
        printf("Couldn't get file system statistics\n");
    }

    libusb_device_handle *dev_handle; //a device handle
    dev_handle = libusb_open_device_with_vid_pid(ctx, 1452, 33424); //these are vendorID and productID I found for my usb device

    if(dev_handle == NULL) {
        cout<<"Cannot open device"<<endl;
        // this device cannot be used for writing
    }
    else {
        cout<<"Device Opened"<<endl;
        // if device too small
    }
    libusb_free_device_list(devs, 1); //free the list, unref the devices in it

    unsigned char *data = new unsigned char[4]; //data to write
    data[0]='a';data[1]='b';data[2]='c';data[3]='d'; //some dummy values

    int actual; //used to find out how many bytes were written
    if(libusb_kernel_driver_active(dev_handle, 0) == 1) { //find out if kernel driver is attached
        cout<<"Kernel Driver Active"<<endl;
        if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
            cout<<"Kernel Driver Detached!"<<endl;
    }
    r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
    if(r < 0) {
        cout<<"Cannot Claim Interface"<<endl;

        //return 1;
    }
    cout<<"Claimed Interface"<<endl;

    cout<<"Data->"<<data<<"<-"<<endl; //just to see the data we want to write : abcd
    cout<<"Writing Data..."<<endl;
    r = libusb_bulk_transfer(dev_handle, (2 | LIBUSB_ENDPOINT_OUT), data, 4, &actual, 0); //my device's out endpoint was 2, found with trial- the device had 2 endpoints: 2 and 129
    if(r == 0 && actual == 4) //we wrote the 4 bytes successfully
        cout<<"Writing Successful!"<<endl;
    else
        cout<<"Write Error"<<endl;

    r = libusb_release_interface(dev_handle, 0); //release the claimed interface
    if(r!=0) {
        cout<<"Cannot Release Interface"<<endl;

        //return 1;
    }
    cout<<"Released Interface"<<endl;

    libusb_close(dev_handle); //close the device we opened
    libusb_exit(ctx); //needs to be called to end the

    delete[] data; //delete the allocated memory for data
    */
    return make_pair(true, "notRegisteredDevices");
}











