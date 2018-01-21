#include "filemanager.h"

void filemanager::existsConfigurationFile()
{
    if (ifstream("configuration.json"))
    {
        syslog (LOG_INFO, "configuration.json already exists.");
    } else {
        // create and write json skeleton data to configuration json file
        ofstream o("configuration.json");
        ofstream a("AAAAAAAA.json");
        if (!ifstream("configuration.json"))
        {
            syslog (LOG_ERR, "configuration.json could not be created.");
        } else {
            // create json file
            json j;
            j["registeredDevices"] = {{{"vendorId", 213}, {"productId", 2312}}, {{"vendorId", 2408124}, {"productId", 1212421}}};
            o << setw(4) << j << endl;
        }

    }
}

void filemanager::existsStatusFile()
{
    if (ifstream("status.json"))
    {
         syslog (LOG_INFO, "status.json already exists.");
         //return false;
    } else {
        // create and write json skeleton data to configuration json file
        ofstream o("status.json");
        if (!ifstream("status.json"))
        {
             syslog (LOG_ERR, "status.json could not be created.");
        } else {
            // create json file
            json j;
            j["registeredDevices"] = {{{"vendorId", 213}, {"productId", 2312}, {"lastBackup", 1}}, {{"vendorId", 2408124}, {"productId", 1212421}, {"lastBackup", 1}}};
            j["notRegisteredDevices"] = {{{"vendorId", 213}, {"productId", 2312}}, {{"vendorId", 2408124}, {"productId", 1212421}}};
            j["insufficientSpaceDevices"] = {{{"vendorId", 213}, {"productId", 2312}}, {{"vendorId", 2408124}, {"productId", 1212421}}};

            o << setw(4) << j << endl;
        }
    }
}
