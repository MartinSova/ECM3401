#include "filemanager.h"

void filemanager::existsConfigurationFile()
{
    if (ifstream("configuration.json"))
    {
         cout << "configuration.json already exists" << endl;
    } else {
        // create and write json skeleton data to configuration json file
        ofstream o("configuration.json");
        if (!ifstream("configuration.json"))
        {
            cerr << "configuration.json could not be created" << endl;
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
         cout << "status.json already exists" << endl;
         //return false;
    } else {
        // create and write json skeleton data to configuration json file
        ofstream o("status.json");
        if (!ifstream("status.json"))
        {
             cerr << "File could not be created" << endl;
             //return false;
        } else {
            // create json file
            json j;
            j["connectedNotRegistered"] = {{{"vendorId", 213}, {"productId", 2312}}, {{"vendorId", 2408124}, {"productId", 1212421}}};
            //j["connectedRegistered"] = {nullptr};
            //j["connectedNotRegistered"] = {nullptr};
            //j["lastBackup"] = nullptr;
            o << setw(4) << j << endl;
        }
    }
}
