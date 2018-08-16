#include "localmanager.h"


// Later change availableRegistedDevices and availableNotRegistedDevices
// to utilize another method for all the code apart from returning
// registered or not registed

deviceIds LocalManager::availableRegisteredDevices()
{
    deviceIds availableDevs = availableDevices();
    deviceIds connectedRegistered;

    for (pair<int, int> device : availableDevs) {
        if (ConfigManager::isRegistered(device))
        {
            connectedRegistered.push_back(device);
        }
    }
    return connectedRegistered;
}

deviceIds LocalManager::availableNotRegisteredDevices()
{
    deviceIds availableDevs = availableDevices();
    deviceIds connectedNotRegistered;

    for (pair<int, int> device : availableDevs) {
        if (!(ConfigManager::isRegistered(device)))
        {
            connectedNotRegistered.push_back(device);
        }
    }
    return connectedNotRegistered;
}

deviceIds LocalManager::availableDevices()
{
    // initiate usb library
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *ctx = NULL; //a libusb session

    deviceIds availableDevices;

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
        pair<int, int> deviceIDPair = make_pair((int)desc.idVendor, (int)desc.idProduct);
        availableDevices.push_back(deviceIDPair);
    }
    return availableDevices;

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

string LocalManager::getPathToMountedDevices(string vendorId, string productId)
{
    const path src = "/sys/bus/usb/devices";
    for (directory_entry& item : directory_iterator(src)) {
        if (is_directory(item.path())) {
            if (exists(item.path().string() + "/idVendor")) {
                
                syslog(LOG_NOTICE, "here");

            }
        }
        syslog(LOG_NOTICE, "directory %s", item.path().c_str());
    }

}

string LocalManager::getHexadecimalValue(int decimal)
{
    char hexDigits[] = "0123456789ABCDEF";
    char hexadecimal[40];
    int index, remaindar;

    index = 0;

        // Convert Decimal Number to Hexadecimal Numbers
    while(decimal != 0) {
        remaindar = decimal % BASE_16;
        hexadecimal[index] = hexDigits[remaindar];
        decimal /= BASE_16;
        index++;
    }
    hexadecimal[index] = '\0';

    char * returnHexadecimal = LocalManager::strrev(hexadecimal);
    if (strlen(returnHexadecimal) < 4) {
        string returnVal = "0";
        string ap(returnHexadecimal);
        return returnVal + ap;
    } else {
        return returnHexadecimal;
    }
}

char * LocalManager::strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}





