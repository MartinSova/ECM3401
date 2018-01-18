#include "configmanager.h"

deviceIds ConfigManager::registeredDevices()
{
    std::ifstream i("configuration.json");
    json j;
    i >> j;
    deviceIds registeredDevices;
    int n;
    for (auto it = j["vendorId"].begin(); it != j["vendorId"].end(); ++it)
    {
        //registeredDevices.push_back((int)*it["vendorId"], (int)*it["productId"]});
        //n = *it["vendorId"].get<int>();;
        cout << *it << "\n";
    }
    /*
    if (j["registeredDevices"].size() == 0) {
        return nullptr;
    } else {
        registeredDevices = j["registeredDevices"];
    }
    */

    return registeredDevices;
}



