#ifndef REGISTEREDDEVICE_H
#define REGISTEREDDEVICE_H

#include <string>
#include <vector>

using namespace std;

class RegisteredDevice
{
private:
    string vendorId;
    string productId;
    vector<string> filesToOmit;
    string lastBackupDirName;
    string lastBackupTime;
public:
    RegisteredDevice();
    string getVendorId() const;
    void setVendorId(const string &value);
    string getProductId() const;
    void setProductId(const string &value);
    vector<string> getFilesToOmit() const;
    void setFilesToOmit(const vector<string> &value);
    string getLastBackupDirName() const;
    void setLastBackupDirName(const string &value);
    string getLastBackupTime() const;
    void setLastBackupTime(const string &value);
};

#endif // REGISTEREDDEVICE_H
