#include "filemodmanager.h"

void FileModManager::clearModFiles()
{
    if (!ifstream("filemod.json"))
    {
         cout << "File mod file does not exist." << endl;
         // RUN STATUS EXISTS FROM FILEMANAGER?
         //return false;
    } else {

        // iterate over connected not registered devices and write to status file

        ifstream i("filemod.json");
        json j;
        i >> j;
        vector<pair<int,int>> registeredDevices;

        for ( auto &device : j.get<json>() ) {
            registeredDevices.push_back(make_pair(device["vendorId"], device["productId"]));
        }

        for (const auto& p : registeredDevices)
        {
          syslog(LOG_NOTICE, "k: %d", p.first);
          // or std::cout << std::get<0>(p) << ", " << std::get<1>(p) << std::endl;
        }
        //i << setw(4) << j << endl;
    }
}


void FileModManager::write(int wd, string pathname)
{   
    if (!ifstream("filemod.json"))
    {
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


