#ifndef DAEMON_H
#define DAEMON_H

#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>


class Daemon
{
public:
    Daemon();
    void heartbeat();
    void runDaemon();
};

#endif // DAEMON_H
