#include "heartbeat.h"

/*
function should also return which
*/
void heartbeat::prepareBackupDirectory()
{
    register struct passwd *pw;
    register uid_t uid;
    int c;

    uid = geteuid ();
    pw = getpwuid (uid);
    char *username;
    if (pw) {
        username = pw->pw_name;
    } else {
        syslog(LOG_ERR, "Could not get username.");
    }

    //char *devicePath = "/home/" + username;
    string devicePath = "/home/media/martin";

    /* *

    For now I will automatically write to my usb flashstick.
    However, in the future I will need to make sure that a specific
    usb drive is written to (despite the name as names of usb drives
    can be the same). Right now I will identify a usb drive simply by its
    name.
    */
    deviceIds connectedRegistered = LocalManager::availableRegisteredDevices();





    deviceIds allRegisteredDevices = ConfigManager::allRegisteredDeviceIds();
    for(auto const& device : connectedRegistered) {

    }
    int count = 0;
    /*
    for(auto const& device : connectedNotRegistered) {
        syslog(LOG_NOTICE, "vendorId connected not registered %d", device.first);
        syslog(LOG_NOTICE, "productId connected not registered %d", device.second);
        count ++;
    }
    syslog(LOG_NOTICE, "total: %d", count);
    */
    /*
    for(auto& p: recursive_directory_iterator("/home/martin/ECM3401")) {
        if (is_directory(p)) {
            const char *s = p.path().c_str();
            syslog(LOG_NOTICE, "%s", s);
        }
    }
    */
}

void heartbeat::backupModFiles(vector<string> allModifiedFiles)
{
    vector<tuple<int, int, vector<string>>> allRegisteredDevices = ConfigManager::allRegisteredDevices();
    for(auto const& regDevice : allRegisteredDevices) {
        int vendorId = get<0>(regDevice);
        //syslog(LOG_NOTICE, "vendor id %d", vendorId);
        int productId = get<1>(regDevice);
        //syslog(LOG_NOTICE, "product id %d", productId);
        vector<string> filesToOmit = get<2>(regDevice);
        for(auto const& file : filesToOmit) {
            //syslog(LOG_NOTICE, "file to omit %s", file.c_str());
        }
    }
}


