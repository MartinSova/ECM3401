#ifndef HEARTBEAT_H
#define HEARTBEAT_H
#include "configmanager.h"
#include "localmanager.h"
#include <syslog.h>
#include <pwd.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <libusb-1.0/libusb.h>

using namespace std;
using namespace boost::filesystem;
using namespace boost::system;

class heartbeat
{
public:
    static void prepareBackupDirectory();
    static void backupModFiles(vector<string> allModifiedFiles);
};

#endif // HEARTBEAT_H
