#include "daemon.h"
#include "localmanager.h"
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <usb.h>

using namespace std;

void printdev(libusb_device *dev); //prototype of the function


#define BUF_SIZE 1024


int main(int argc, char *argv[])
{

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

    localManager l;
    pair<deviceIds, deviceIds> connectedDevices = l.availableDevices(ctx, devs);

    l.canBeRegistered(ctx, devs, r, connectedDevices.);


    //libusb_free_device_list(devs, 1); //free the list, unref the devices in it
    libusb_exit(ctx); //close the session


    return 0;

    /*

    device registered and connected? yes? do ---->
    no? ------> canBeRegistered and see if viable for registtration
    */

}

void available_devices(struct libusb_context *ctx, libusb_device **devs, int r) {
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

    //return 0;


}




/*
void hotplug_callback(struct libusb_context *ctx, struct libusb_device *dev,
                      libusb_hotplug_event event, void *user_data) {
  static libusb_device_handle *handle = NULL;
  struct libusb_device_descriptor desc;
  int rc;
  (void)libusb_get_device_descriptor(dev, &desc);
  if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event) {
    rc = libusb_open(dev, &handle);
    if (LIBUSB_SUCCESS != rc) {
      printf("Could not open USB device\n");
    }
  } else if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event) {
    if (handle) {
      libusb_close(handle);
      handle = NULL;
    }
  } else {
    printf("Unhandled event %d\n", event);
  }
  count++;
}
*/


