#include "filemanager.h"

void filemanager::existsConfigurationFile()
{
    if (ifstream("configuration.json")) {
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
            j["registeredDevices"] = {{{"vendorId", 2385}, {"productId", 5675}, {"filesToOmit", {"path1", "path2"}}, {"lastBackupDirName", ""}}, {{"vendorId", 2408124}, {"productId", 1212421}, {"filesToOmit", {"path3", "path4"}}, {"lastBackupDirName", ""}}};
            o << setw(4) << j << endl;
            syslog (LOG_INFO, "configuration.json created.");
        }

    }
}

void filemanager::existsStatusFile()
{
    if (ifstream("status.json")) {
         syslog (LOG_INFO, "status.json already exists.");
         //return false;
    } else {
        // create and write json skeleton data to status json file
        ofstream o("status.json");
        if (!ifstream("status.json")) {
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

/* I don't think this functon behaves the way I want to
 * in terms of wiping certain data and keeping some e.g. watchDesc*/
void filemanager::existsFileModFile()
{
    json j;
    ofstream o("filemod.json");
    if (!ifstream("filemod.json")) {
        syslog (LOG_ERR, "filemod.json could not be created.");
    } else {
        syslog (LOG_INFO, "filemod.json exists.");
        // create json file
        j["modFiles"]= {};
        j["watchDesc"] = {};
    }
    o << setw(4) << j << endl;
}
