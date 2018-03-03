#include "configmanager.h"

bool ConfigManager::isRegistered(pair<int,int> device)
{
    if (!ifstream("configuration.json")) {
        // ERROR: no configuration file
    }
    else {
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
        }
    else {
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
    }
    else {
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



