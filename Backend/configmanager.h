#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <vector>
#include <string>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <tuple>
#include <syslog.h>

using namespace std;
using json = nlohmann::json;
typedef vector<pair<int,int>> deviceIds;

struct RegisteredDevice
{
    int vendorId;
    int productId;
    vector<string> filesToOmit;
    string lastBackupDirName;
    int lastBackupTime;
};

class ConfigManager
{
public:
    static bool isRegistered(pair<int,int> device);
    static vector<tuple<int, int, vector<string>>> allRegisteredDevices();
    static deviceIds allRegisteredDeviceIds();
    static void writeLastBackupDir(string dir);
    static string readLastBackupDir();
    static vector<RegisteredDevice> registeredDevices();
};

#endif // CONFIGMANAGER_H
