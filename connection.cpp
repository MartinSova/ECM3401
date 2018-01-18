#include "connection.h"




#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <libusb-1.0/libusb.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>

int done = 0;
libusb_device_handle *handle;

using namespace std;

int connection::hotplug_callback (libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {
  struct libusb_device_descriptor desc;
  int rc;

  rc = libusb_get_device_descriptor(dev, &desc);
  if (LIBUSB_SUCCESS != rc) {
    fprintf (stderr, "Error getting device descriptor\n");
  }

  printf ("Device attach: %04x:%04x\n", desc.idVendor, desc.idProduct);

  libusb_open (dev, &handle);

  return 0;
}

int connection::hotplug_callback_detach (libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {
  printf ("Device detached\n");

  libusb_close (handle);

  return 0;
}


