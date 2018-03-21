#ifndef LOCALMANAGER_H
#define LOCALMANAGER_H
#include "configmanager.h"
#include <sys/statvfs.h>
#include <stdio.h>
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <usb.h>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <syslog.h>
#include <sstream>
#include <time.h>

using namespace std;

typedef vector<pair<int,int>> deviceIds;

class LocalManager
{
public:
    static void printdev(libusb_device *dev);
    static deviceIds availableRegisteredDevices();
    static deviceIds availableNotRegisteredDevices();
    static void deviceAdded(libusb_device *dev, void *user_data);
    static void deviceRemoved(libusb_device *dev, void *user_data);
    static string currentLocalTime();
};

#endif // LOCALMANAGER_H
