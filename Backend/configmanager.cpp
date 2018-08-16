#include "configmanager.h"

// find if there exist external methods/libraries that convert json objects into C++ objects
vector<RegisteredDevice> ConfigManager::registeredDevices()
{
    if (!ifstream("configuration.json")) {
        // ERROR: no configuration file
    } else {
        ifstream i("configuration.json");
        json j;
        i >> j;
        vector<RegisteredDevice> registeredDevices;
        for ( auto &device : j["registeredDevices"].get<json>() ) {
            struct RegisteredDevice registeredDevice;
            registeredDevice.vendorId = device["vendorId"].get<int>();
            registeredDevice.productId = device["productId"].get<int>();
            vector<string> filesToOmit;
            for ( auto &f : device["filesToOmit"].get<json>()) {
                filesToOmit.push_back(f.get<string>().c_str());
            }
            registeredDevice.filesToOmit = filesToOmit;
            registeredDevice.lastBackupDirName = device["lastBackupDirName"].get<string>().c_str();
            registeredDevice.lastBackupTime = device["lastBackupTime"].get<int>();
            registeredDevices.push_back(registeredDevice);
        }
        return registeredDevices;
    }
}

bool ConfigManager::isRegistered(pair<int,int> device)
{
    if (!ifstream("configuration.json")) {
        // ERROR: no configuration file
    } else {
        ifstream i("configuration.json");
        json j;
        i >> j;
        vector<pair<int,int>> registeredDevices = allRegisteredDeviceIds();
        bool returnValue = (find(registeredDevices.begin(), registeredDevices.end(), device) != registeredDevices.end()) ? true : false;
        return returnValue;
    }
}

deviceIds ConfigManager::allRegisteredDeviceIds()
{
    if (!ifstream("configuration.json")) {
            // ERROR: no configuration file
    } else {
        ifstream i("configuration.json");
        json j;
        i >> j;
        deviceIds registeredDevices;
        for ( auto &device : j["registeredDevices"].get<json>() ) {
            registeredDevices.push_back(make_pair(device["vendorId"], device["productId"]));
        }
        return registeredDevices;
    }
}

vector<tuple<int, int, vector<string>>> ConfigManager::allRegisteredDevices()
{
    if (!ifstream("configuration.json")) {
        // ERROR: no configuration file
    } else {
        ifstream i("configuration.json");
        json j;
        i >> j;
        vector<tuple<int, int, vector<string>>> registeredDevices;
        for ( auto &device : j["registeredDevices"].get<json>() ) {
            tuple<int, int, vector<string>> regDevice;
            get<0>(regDevice) = device["vendorId"];
            get<1>(regDevice) = device["productId"];
            vector<string> filesToOmit;
            for ( auto &f : device["filesToOmit"].get<json>()) {
                filesToOmit.push_back(f.get<string>().c_str());
            }
            get<2>(regDevice) = filesToOmit;
            registeredDevices.push_back(regDevice);
        }
        return registeredDevices;
    }
}

/*
A big stretch but I could actually design this software in such way
that it always checks that the machine time under which it is saved
is always correct (so may be updated) in terms of relevance to the GMT time
-- but this might actually not be the better option.
*/

void ConfigManager::writeLastBackupDir(string dir)
{
    if (!ifstream("configuration.json")) {
        // ERROR: no configuration file
    } else {
        ifstream i("configuration.json");
        json j;
        i >> j;
        j["lastBackupDirName"] = dir;
        ofstream o("configuration.json");
        if (!ifstream("configuration.json")) {
            syslog(LOG_ERR, "configuration.json could not be updated, function: writeLastBackupDir().");
        } else {
            o << setw(4) << j << endl;
        }
    }
}

string ConfigManager::readLastBackupDir()
{
    string lastBackupDirName = "";
    if (!ifstream("configuration.json")) {
        // ERROR: no configuration file
    } else {
        ifstream i("configuration.json");
        json j;
        i >> j;
        lastBackupDirName = j["lastBackupDirName"].get<string>();
    }
    return lastBackupDirName;
}



