#include "localmanager.h"


// Later change availableRegistedDevices and availableNotRegistedDevices
// to utilize another method for all the code apart from returning
// registered or not registed

deviceIds LocalManager::availableRegisteredDevices()
{
    // initiate usb library
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *ctx = NULL; //a libusb session

    deviceIds connectedRegistered;

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

    ssize_t i; //for iterating through the list

    libusb_device_descriptor desc;

    for (i = 0; i < count; i++) {
        //bool found = (std::find(my_list.begin(), my_list.end(), my_var) != my_list.end());
        //printdev(devs[i]); //print specs of this device

        int r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            cout<<"failed to get device descriptor"<<endl;
            //return;
        }

        pair<int, int> pairTest = make_pair((int)desc.idVendor, (int)desc.idProduct);

        if (ConfigManager::isRegistered(pairTest)) {
            connectedRegistered.push_back(pairTest);
        }
    }
    return connectedRegistered;
}

deviceIds LocalManager::availableNotRegisteredDevices()
{
    // initiate usb library
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *ctx = NULL; //a libusb session

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

    ssize_t i; //for iterating through the list

    libusb_device_descriptor desc;

    for (i = 0; i < count; i++) {
        //bool found = (std::find(my_list.begin(), my_list.end(), my_var) != my_list.end());
        //printdev(devs[i]); //print specs of this device

        int r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            cout<<"failed to get device descriptor"<<endl;
            //return;
        }

        pair<int, int> pairTest = make_pair((int)desc.idVendor, (int)desc.idProduct);

        if (!(ConfigManager::isRegistered(pairTest)))
        {
            connectedNotRegistered.push_back(pairTest);
        }
    }
    return connectedNotRegistered;
}

string LocalManager::currentLocalTime()
{
    time_t t = time(0);
    tm *localTime = localtime(&t);
    stringstream date;
    date << 1900 + localTime->tm_year
         << localTime->tm_mday
         << localTime->tm_mon
         << localTime->tm_hour
         << localTime->tm_min
         << localTime->tm_sec;
    syslog(LOG_NOTICE, "%s time being returned from currentLocalTime", date.str().c_str());
    return date.str();
}





