#ifndef CONNECTION_H
#define CONNECTION_H
#include <libusb-1.0/libusb.h>


class connection
{
public:
    connection();
    static int hotplug_callback(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);
    static int hotplug_callback_detach(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);
};

#endif // CONNECTION_H
