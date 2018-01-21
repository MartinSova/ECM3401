#include "statusmanager.h"

void StatusManager::writeConnectedDevices(deviceIds devs, bool registered)
{

    string deviceType = (registered) ? ("connectedRegistered") : ("connectedNotRegistered");
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

        for(auto const& d: devs) {
            j["connectedRegistered"].push_back({{"vendorId", d.first}, {"productId", d.second}});
        }
        o << setw(4) << j << endl;
    }
}

