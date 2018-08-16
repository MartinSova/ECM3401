#include "jsonmanager.h"

void JsonManager::deRegister(vector<string> toDeregister)
{
    if (!ifstream("devices.json")) {
        // ERROR: no devices JSON file
    } else {
        ifstream i("devices.json");
        json j;
        i >> j;
        json newJ;
        newJ["registeredDevices"] = {};
        for ( auto &device : j["registeredDevices"].get<json>() ) {
            string deviceName = device["name"].get<string>();
            if (find(toDeregister.begin(), toDeregister.end(), deviceName) != toDeregister.end())
            {
              // Element in vector.
            } else {
                newJ["registeredDevices"].push_back({{"name", deviceName}});
            }
        }
        ofstream o("devices.json");
        o << setw(4) << newJ << endl;
    }
}

void JsonManager::Register(vector<string> toRegister)
{
    if (!ifstream("devices.json")) {
        // ERROR: no devices JSON file
    } else {
        ifstream i("devices.json");
        json j;
        i >> j;
        for (auto &device : toRegister)
        {
            j["registeredDevices"].push_back({{"name", device}});
        }
        ofstream o("devices.json");
        o << setw(4) << j << endl;
    }
}

bool JsonManager::notRegistered(string path)
{
    if (!ifstream("devices.json")) {
        // ERROR: no devices JSON file
    } else {
        ifstream i("devices.json");
        json j;
        i >> j;
        for ( auto &device : j["registeredDevices"].get<json>() ) {
            string deviceName = device["name"].get<string>();
            if (strcmp(path.c_str(), deviceName.c_str()) == 0) {
                return false;
            }
        }
        return true;
    }
}

bool JsonManager::registered(string path)
{
    if (!ifstream("devices.json")) {
        // ERROR: no devices JSON file
    } else {
        ifstream i("devices.json");
        json j;
        i >> j;
        for ( auto &device : j["registeredDevices"].get<json>() ) {
            string deviceName = device["name"].get<string>();
            if (strcmp(path.c_str(), deviceName.c_str()) == 0) {
                return true;
            }
        }
        return false;
    }
}


