#ifndef LOCALMANAGER_H
#define LOCALMANAGER_H
#include <configmanager.h>
#include <sys/statvfs.h>
#include <stdio.h>
#include<iostream>
#include<libusb-1.0/libusb.h>
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <usb.h>
#include <vector>
#include <algorithm>

using namespace std;

class localManager
{
public:
    localManager();
    void canBeRegistered(struct libusb_context *ctx, libusb_device **devs, int r);
    void printdev(libusb_device *dev);
    pair<deviceIds, deviceIds> availableDevices(libusb_context *ctx, libusb_device **devs);
};

#endif // LOCALMANAGER_H
