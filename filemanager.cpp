#include "filemanager.h"

void filemanager::existsConfigurationFile()
{
    if (ifstream("configuration.json"))
    {
        syslog (LOG_INFO, "configuration.json already exists.");
    } else {
        // create and write json skeleton data to configuration json file
        ofstream o("configuration.json");
        if (!ifstream("configuration.json"))
        {
            syslog (LOG_ERR, "configuration.json could not be created.");
        } else {
            // create json file
            json j;
            j["registeredDevices"] = {{{"vendorId", 213}, {"productId", 2312}, {"filesToOmmit", {"path1", "path2"}}}, {{"vendorId", 2408124}, {"productId", 1212421}, {"filesToOmmit", {"path1", "path2"}}}};
            o << setw(4) << j << endl;
            syslog (LOG_INFO, "configuration.json created.");
        }

    }
}

void filemanager::existsStatusFile()
{
    if (ifstream("status.json"))
    {
         syslog (LOG_INFO, "status.json already exists.");
         //return false;
    } else {
        // create and write json skeleton data to status json file
        ofstream o("status.json");
        if (!ifstream("status.json"))
        {
             syslog (LOG_ERR, "status.json could not be created.");
        } else {
            // create json file
            json j;
            j["registeredDevices"] = {{{"vendorId", 213}, {"productId", 2312}, {"lastBackup", 1}}, {{"vendorId", 2408124}, {"productId", 1212421}, {"lastBackup", 1}}};
            j["notRegisteredDevices"] = {};
            // subset of not registered devices since they can be registered they just do not have enough space
            j["insufficientSpaceDevices"] = {{{"vendorId", 213}, {"productId", 2312}}, {{"vendorId", 2408124}, {"productId", 1212421}}};
            o << setw(4) << j << endl;
            syslog (LOG_INFO, "status.json created.");
        }
    }
}

void filemanager::existsFileModFile()
{
    vector<pair<int,string>> existingWd;
    if (ifstream("filemod.json"))
    {
         syslog (LOG_INFO, "filemod.json already exists.");
         ifstream i("filemod.json");
         json k;
         i >> k;
         for ( auto &wd : k["watchDesc"].get<json>()) {
             existingWd.push_back(make_pair(wd["wdInt"], wd["path"].get<string>()));
         }
         //return false;
    }
    // create and write json skeleton data to file mod json file
    ofstream o("filemod.json");
    if (!ifstream("filemod.json")) {
        syslog (LOG_ERR, "filemod.json could not be created.");
    } else {
        syslog (LOG_INFO, "filemod.json exists.");
        // create json file
        json j;
        deviceIds allRegDevices = ConfigManager::allRegisteredDevices();
        for (pair<int,int> &device : allRegDevices)
            j["modFiles"].push_back({{"vendorId", device.first}, {"productId", device.second}, {"modFilesToBackup", {}}});
        if (existingWd.size() > 0) {
            syslog (LOG_INFO, "existingWD not empty");
                /*
                for (pair<int,string> &wd : existingWd)
                    j["watchDesc"].push_back({{"wdInt", wd.first}, {"path", wd.second}});
                */
        } else {
            syslog (LOG_INFO, "existingWD empty");
            j["watchDesc"] = {};
        }
        o << setw(4) << j << endl;

    }
}
