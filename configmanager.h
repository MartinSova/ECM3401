#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <vector>
#include <string>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <tuple>

using namespace std;
using json = nlohmann::json;
typedef vector<pair<int,int>> deviceIds;

class ConfigManager
{
public:
    static bool isRegistered(pair<int,int> device);
    static vector<tuple<int, int, vector<string>>> allRegisteredDevices();
    static deviceIds allRegisteredDeviceIds();
};

#endif // CONFIGMANAGER_H
