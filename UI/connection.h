#ifndef CONNECTION_H
#define CONNECTION_H
#include <libusb-1.0/libusb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <libusb-1.0/libusb.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <syslog.h>

class Connection
{
public:
    Connection();
    static int hotplug_callback(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);
    static int hotplug_callback_detach(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);
};

#endif // CONNECTION_H
