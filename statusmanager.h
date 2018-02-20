#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <vector>
#include <string>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

typedef vector<pair<int,int>> deviceIds;

class StatusManager
{
public:
    static void overwriteConnectedDevices(deviceIds devs, string type);
    static void appendConnectedDevice(pair<int, int> dev, string type);
    static void writePid(pid_t pid);
};

#endif // STATUSMANAGER_H
