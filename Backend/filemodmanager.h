#ifndef FILEMODMANAGER_H
#define FILEMODMANAGER_H

#include <sys/inotify.h>
#include <unistd.h>
#include <syslog.h>
#include "json.hpp"
#include "configmanager.h"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

class FileModManager
{
public:
    static void writeWatchDesc(int wd, string pathname);
    static vector<pair<int, string> > readAllWatchDesc();
    static void update();
    static void writeModFiles(vector<string> sortedPathnames);
    static vector<string> readAllModFiles();
};

#endif // FILEMODMANAGER_H
