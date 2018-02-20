#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <vector>
#include <string>
#include "json.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

typedef vector<pair<int,int>> deviceIds;

class ConfigManager
{
public:
    static bool isRegistered(pair<int,int> device);
    static deviceIds allRegisteredDevices();
};

#endif // CONFIGMANAGER_H
