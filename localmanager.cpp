#include "localmanager.h"

pair<deviceIds, deviceIds> localManager::availableDevices(struct libusb_context *ctx, libusb_device **devs)
{
    deviceIds connectedRegistered;
    deviceIds connectedNotRegistered;

    //pair<availableRegistered>, availableNotRegistered> availableDevices;

    int r; // for return values
    ssize_t count; // holding number of devices in list
    r = libusb_init(&ctx); // initialize a library session
    if (r < 0) {
        cout << "Init Error" << r << endl; //there was an error
        //return 1;
    }
    count = libusb_get_device_list(ctx, &devs); //get the list of devices
    if (count < 0) {
        cout<<"Get Device Error"<<endl; //there was an error
    }
    cout<<count<<" Devices in list."<<endl; //print total number of usb devices
    ssize_t i; //for iterating through the list

    libusb_device_descriptor desc;

    deviceIds currentlyRegisteredDevices = ConfigManager::readRegisteredDevices();

    for(i = 0; i < count; i++) {
        //bool found = (std::find(my_list.begin(), my_list.end(), my_var) != my_list.end());
        //printdev(devs[i]); //print specs of this device

        int r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            cout<<"failed to get device descriptor"<<endl;
            //return;
        }

        pair<int, int> pairTest = make_pair((int)desc.idVendor, (int)desc.idProduct);

        if (find(currentlyRegisteredDevices.begin(), currentlyRegisteredDevices.end(), pairTest) != currentlyRegisteredDevices.end())
        {
            connectedRegistered.push_back(pairTest);
        } else {
            connectedNotRegistered.push_back(pairTest);
        }
        cout << "VendorID: "<<(int)desc.idVendor<<"  ";
        cout << "ProductID: "<<(int)desc.idProduct<<endl;
        cout << endl;
    }
    std::cout << "reg size: " << connectedRegistered.size() << '\n';
    std::cout << "NOT reg size: " << connectedNotRegistered.size() << '\n';
    return make_pair(connectedRegistered, connectedNotRegistered);
}

void localManager::canBeRegistered(struct libusb_context *ctx, libusb_device **devs, int r)
{
    /* Any file on the filesystem in question */
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
}





