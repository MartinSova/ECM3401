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
    static void existsConfigurationFile();
    static void existsStatusFile();
};

#endif // FILEMANAGER_H
