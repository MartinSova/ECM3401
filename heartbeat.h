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

using namespace std;
using namespace boost::filesystem;
using namespace boost::system;

class heartbeat
{
public:
    static void backupModFiles(vector<string> allModifiedFiles);
    static string getNewDirName();
    static void hardlinkLastBackup(const path &rootDirectory, const path &devicePath, const path &src, const path &dst);
    static void prepareBackupDirectory(string rootDirectory);
    static void createHardCopy(const path &src, const path &dst);
};

#endif // HEARTBEAT_H
