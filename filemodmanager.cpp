#include "filemodmanager.h"


void FileModManager::writeWatchDesc(int wd, string pathname)
{   
    if (!ifstream("filemod.json")) {
         cout << "File mod file does not exist." << endl;
         // RUN FILE MOD EXISTS FROM FILEMANAGER?
         //return false;
    } else {
        ifstream i("filemod.json");
        json k;
        i >> k;
        k["watchDesc"].push_back({{"wdInt", wd}, {"path", pathname}});
        ofstream o("filemod.json");
        o << setw(4) << k << endl;
    }
}

void FileModManager::writeModFiles(vector<string> sortedPathnames)
{
    /*
    for (auto &f : pathnames) {
        syslog(LOG_NOTICE, "modified file is: %s", f.c_str());
    }
    */
    if (!ifstream("filemod.json")) {
         cout << "File mod file does not exist." << endl;
         // RUN FILE MOD EXISTS FROM FILEMANAGER?
         //return false;
    } else {
        ifstream i("filemod.json");
        json k;
        i >> k;
        vector<string> newMod;
        // iterate over all current modified files in json file
        for ( auto &f : k["modFiles"].get<json>()) {
            string currJsonString = f.get<string>().c_str();
            string currNewString = sortedPathnames.at(sortedPathnames.size()-1);
            // if mod file already marked
            if (currJsonString.compare(currNewString) == 0) {
                // add string once again
                newMod.push_back(currJsonString);
                sortedPathnames.pop_back();
                continue;
            } else if (currNewString.compare(currJsonString) > 0) {
                // if already marked mod file has alphabetical priority
                newMod.push_back(currJsonString);
            } else {
                // while the new strings have alphabetical priority
                while (currNewString.compare(currJsonString) < 0) {
                    newMod.push_back(currNewString);
                    sortedPathnames.pop_back();
                    currNewString = sortedPathnames.at(sortedPathnames.size()-1);
                }
                newMod.push_back(currJsonString);
            }
            //syslog(LOG_NOTICE, "modified file is: %s", f.get<string>().c_str());
        }
        if (!sortedPathnames.empty()) {
            newMod.insert(newMod.end(), sortedPathnames.rbegin(), sortedPathnames.rend());
        }
        k["modFiles"] = {};
        for(auto const& value: newMod) {
            k["modFiles"].push_back(value);
        }
        ofstream o("filemod.json");
        o << setw(4) << k << endl;
    }
}

void FileModManager::clearDuplicates()
{

}

//add a delete method for when a directory is deleted

vector<pair<int,string>> FileModManager::readAllWatchDesc()
{
    vector<pair<int,string>> allWatchDesc;
    if (!ifstream("filemod.json")) {
         cout << "File mod file does not exist." << endl;
         // RUN FILE MOD EXISTS FROM FILEMANAGER?
         //return false;
    } else {
        ifstream i("filemod.json");
        json j;
        i >> j;
        for ( auto &wd : j["watchDesc"].get<json>()) {
            allWatchDesc.push_back(make_pair(wd["wdInt"], wd["path"].get<string>()));
        }
    }
    return allWatchDesc;
}

vector<string> FileModManager::readAllModFiles()
{
    vector<string> allModFiles;
    ifstream i("filemod.json");
    json j;
    i >> j;
    for (auto &path : j["modFiles"].get<json>()) {
        allModFiles.push_back(path.get<string>());
        //syslog (LOG_INFO, "pushing back file: ");
    }
    return allModFiles;
}

void FileModManager::update()
{
    // OLD CODE KEEP FOR A BIT FOR GUIDANCE
    /*
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
            syslog (LOG_INFO, "from update existingWD not empty");
                for (pair<int,string> &wd : existingWd)
                    j["watchDesc"].push_back({{"wdInt", wd.first}, {"path", wd.second}});
        } else {
            syslog (LOG_INFO, "from update existingWD empty");
            j["watchDesc"] = {};
        }
        o << setw(4) << j << endl;

    }
    */
    if (!ifstream("filemod.json")) {
        syslog (LOG_ERR, "filemod.json does not exist.");
    } else {
        ifstream i("filemod.json");
        syslog (LOG_INFO, "filemod.json is being updated.");
        json j;
        i >> j;
        /*
        for (auto &device : j["modFiles"].get<json>())
            device["modFilesToBackup"] = {};
        */
        ofstream o("filemod.json");
        if (!ifstream("filemod.json")) {
            syslog (LOG_ERR, "filemod.json could not be created.");
        } else {
            o << setw(4) << j << endl;
        }
    }
}
