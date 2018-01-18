#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "json.hpp"
#include <iostream>
#include <fstream>

using namespace std;

using json = nlohmann::json;

class filemanager
{
public:
    static void existsConfiguration();
    static void existsStatus();
};

#endif // FILEMANAGER_H
