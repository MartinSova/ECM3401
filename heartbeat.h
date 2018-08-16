#ifndef HEARTBEAT_H
#define HEARTBEAT_H
#include "configmanager.h"
#include "localmanager.h"
#include "filemodmanager.h"
#include <syslog.h>
#include <pwd.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <libusb-1.0/libusb.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>

using namespace std;
using namespace boost::filesystem;
using namespace boost::system;

struct compare {
    bool operator()(const std::string& first, const std::string& second) {
        return first.size() < second.size();
    }
};

class heartbeat
{
public:
    static void backupModFiles(vector<string> allModifiedFiles);
    static string getNewDirName();
    static void hardlinkLastBackup(const path &rootDirectory, const path &devicePath, const path &src, const path &dst);
    static void prepareBackupDirectory();
    static void createHardCopy(const path &src, const path &dst);
    static void copyModifiedFiles(const path &rootDirectory, const path &devicePath);
    static void getFileCreationTime(const char *path);
};

#endif // HEARTBEAT_H
