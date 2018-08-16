#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QWidget>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <jsonmanager.h>
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

using namespace std;

class JsonManager
{
public:
    static bool notRegistered(string path);
    static bool registered(string path);
    static void deRegister(vector<string> toDeregister);
    static void Register(vector<string> toRegister);
};

#endif // JSONMANAGER_H
