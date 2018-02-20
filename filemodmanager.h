#ifndef FILEMODMANAGER_H
#define FILEMODMANAGER_H

#include <sys/inotify.h>
#include <unistd.h>
#include <syslog.h>
#include "json.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

typedef vector<pair<int,int>> deviceIds;

class FileModManager
{
public:
    static void write(int wd, string pathname);
    static void clearModFiles();
};

#endif // FILEMODMANAGER_H
