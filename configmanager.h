#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <vector>
#include <string>

using namespace std;

typedef vector<pair<int,int> > deviceIds;

class ConfigManager
{
public:
    static deviceIds registeredDevices();
};

#endif // CONFIGMANAGER_H
