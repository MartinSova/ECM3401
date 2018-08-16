#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "json.hpp"
#include <iostream>
#include <fstream>
#include <syslog.h>
#include "configmanager.h"

using namespace std;
using json = nlohmann::json;
typedef vector<pair<int,int>> deviceIds;

class filemanager
{
public:
    static void existsConfigurationFile();
    static void existsStatusFile();
    static void existsFileModFile();
    static void write(int fd, char *buf);
};

#endif // FILEMANAGER_H
