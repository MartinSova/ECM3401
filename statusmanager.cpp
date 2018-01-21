#include "statusmanager.h"

void StatusManager::overwriteConnectedDevices(deviceIds devs, string type)
{
    if (!ifstream("status.json"))
    {
         cout << "Status file does not exist." << endl;
         // RUN STATUS EXISTS FROM FILEMANAGER?
         //return false;
    } else {

        // iterate over connected not registered devices and write to status file
        ifstream ifs("status.json");
        json j = json::parse(ifs);
        j[type] = nullptr;
        ofstream o("status.json");
    // NEED TO CHANGE THIS TO OVERWRITE NOT APPEND
        for(auto const& d: devs) {
            j[type].push_back({{"vendorId", d.first}, {"productId", d.second}});
        }
        o << setw(4) << j << endl;
    }
}

void StatusManager::appendConnectedDevices(pair<int, int> dev, string type)
{
    if (!ifstream("status.json"))
    {
         cout << "Status file does not exist." << endl;
         // RUN STATUS EXISTS FROM FILEMANAGER?
         //return false;
    } else {

        // iterate over connected not registered devices and write to status file
        ifstream ifs("status.json");
        json j = json::parse(ifs);

        ofstream o("status.json");

        j[type].push_back({{"vendorId", dev.first}, {"productId", dev.second}});

        o << setw(4) << j << endl;
    }
}

