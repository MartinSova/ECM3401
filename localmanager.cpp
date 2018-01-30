#include "localmanager.h"

pair<deviceIds, deviceIds> LocalManager::availableDevices(struct libusb_context *ctx, libusb_device **devs)
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

    for(i = 0; i < count; i++) {
        //bool found = (std::find(my_list.begin(), my_list.end(), my_var) != my_list.end());
        //printdev(devs[i]); //print specs of this device

        int r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            cout<<"failed to get device descriptor"<<endl;
            //return;
        }

        pair<int, int> pairTest = make_pair((int)desc.idVendor, (int)desc.idProduct);

        if (ConfigManager::isRegistered(pairTest))
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





