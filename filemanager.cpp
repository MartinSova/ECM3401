#include "filemanager.h"

void filemanager::existsConfiguration()
{
    if (ifstream("configuration.json"))
    {
         cout << "File already exists" << endl;
         //return false;
    } else {
        // create json file
        json j;
        j["registeredDevices"] = {{{"vendorId", 213}, {"productId", 2312}}, {{"vendorId", 2408124}, {"productId", 1212421}}};
        // create and write json skeleton data to configuration json file
        ofstream o("configuration.json");
        o << setw(4) << j << endl;

        if (!ifstream("configuration.json"))
        {
             cout << "File could not be created" << endl;
             //return false;
        }
    }
}

void filemanager::existsStatus()
{
    if (ifstream("status.json"))
    {
         cout << "File already exists" << endl;
         //return false;
    } else {
        // create json file
        json j;
        j["connectedRegistered"] = {nullptr};
        j["connectedNotRegistered"] = {nullptr};
        j["lastBackup"] = nullptr;

        // create and write json skeleton data to configuration json file
        ofstream o("status.json");
        o << setw(4) << j << endl;

        if (!ifstream("status.json"))
        {
             cout << "File could not be created" << endl;
             //return false;
        }
    }
}
