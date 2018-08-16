#ifndef LOCALMANAGER_H
#define LOCALMANAGER_H
#include "configmanager.h"
#include <sys/statvfs.h>
#include <stdio.h>
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <dirent.h>
#include <malloc.h>
#include <usb.h>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <syslog.h>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#define BASE_16 16

using namespace std;
using namespace boost::filesystem;
using namespace boost::system;

typedef vector<pair<int,int>> deviceIds;

class LocalManager
{
public:
    static void printdev(libusb_device *dev);
    static deviceIds availableRegisteredDevices();
    static deviceIds availableNotRegisteredDevices();
    static deviceIds availableDevices();
    static void deviceAdded(libusb_device *dev, void *user_data);
    static void deviceRemoved(libusb_device *dev, void *user_data);
    static string currentLocalTime();
    static string getHexadecimalValue(int value);
    static char *strrev(char *str);
    static string getPathToMountedDevices(string vendorId, string productId);
};

#endif // LOCALMANAGER_H
