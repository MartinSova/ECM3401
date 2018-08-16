#include "registereddevice.h"
string RegisteredDevice::getVendorId() const
{
    return vendorId;
}

void RegisteredDevice::setVendorId(const string &value)
{
    vendorId = value;
}

string RegisteredDevice::getProductId() const
{
    return productId;
}

void RegisteredDevice::setProductId(const string &value)
{
    productId = value;
}

vector<string> RegisteredDevice::getFilesToOmit() const
{
    return filesToOmit;
}

void RegisteredDevice::setFilesToOmit(const vector<string> &value)
{
    filesToOmit = value;
}

string RegisteredDevice::getLastBackupDirName() const
{
    return lastBackupDirName;
}

void RegisteredDevice::setLastBackupDirName(const string &value)
{
    lastBackupDirName = value;
}

string RegisteredDevice::getLastBackupTime() const
{
    return lastBackupTime;
}

void RegisteredDevice::setLastBackupTime(const string &value)
{
    lastBackupTime = value;
}

RegisteredDevice::RegisteredDevice()
{
}
