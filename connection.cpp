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

libusb_hotplug_callback_handle hp[2];
int rc;

using namespace std;

libusb_context *ctx;
libusb_device *dev;
libusb_hotplug_event event;
void *user_data;

connection::connection()
{
    libusb_init (NULL);

    if (!libusb_has_capability (LIBUSB_CAP_HAS_HOTPLUG)) {
      printf ("Hotplug not supported by this build of libusb\n");
      libusb_exit (NULL);
      //return EXIT_FAILURE;
    }

    rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,
                                           LIBUSB_HOTPLUG_NO_FLAGS , LIBUSB_HOTPLUG_MATCH_ANY,
                                           LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, hotplug_callback, NULL, &hp[0]);
    if (LIBUSB_SUCCESS != rc) {
      fprintf (stderr, "Error registering callback 0\n");
      libusb_exit (NULL);
      //return EXIT_FAILURE;
    }

    rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
                                           LIBUSB_HOTPLUG_NO_FLAGS , LIBUSB_HOTPLUG_MATCH_ANY,
                                           LIBUSB_HOTPLUG_MATCH_ANY,LIBUSB_HOTPLUG_MATCH_ANY, hotplug_callback_detach, NULL, &hp[1]);
    if (LIBUSB_SUCCESS != rc) {
      fprintf (stderr, "Error registering callback 1\n");
      libusb_exit (NULL);
      //return EXIT_FAILURE;
    }

    while (1) libusb_handle_events (NULL);

    libusb_exit(ctx); //close the session



}

int connection::hotplug_callback (libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {

  struct libusb_device_descriptor desc;
  int rc;

  rc = libusb_get_device_descriptor(dev, &desc);
  if (LIBUSB_SUCCESS != rc) {
    fprintf (stderr, "Error getting device descriptor\n");
  }

  printf ("Device attach: %04x:%04x\n", desc.idVendor, desc.idProduct);

  //libusb_open (dev, &handle);

  return 0;
}

int connection::hotplug_callback_detach (libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {
  printf ("Device detached\n");

  //libusb_close (handle);

  return 0;
}


