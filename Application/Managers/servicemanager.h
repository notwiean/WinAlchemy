#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <windows.h>
#include <string>

class ServiceManager
{
public:
    ServiceManager();

    // Function to fully lock down a service and protect its parameters
    bool LockService(const std::wstring& serviceName);
    // Function to fully unlock a service
    bool UnlockService(const std::wstring& serviceName);
    // Function to check if the service is running
    bool IsServiceRunning(const std::wstring& serviceName);
private:
    // Function to stop service
    bool StopService(SC_HANDLE ServiceHandle);
    // Function to disable service startup
    bool DisableServiceStartup(SC_HANDLE ServiceHandle);
    // Function to protect the service from changes
    bool ProtectServiceFromChanges(SC_HANDLE ServiceHandle);
    // Function to protect the service from deletion
    bool ProtectServiceFromDeletion(SC_HANDLE ServiceHandle);

    // Function to enable service startup
    bool EnableServiceStartup(SC_HANDLE ServiceHandle);
    // // Function to unprotect the service from changes
    bool UnprotectServiceFromChanges(SC_HANDLE ServiceHandle);
    // Function to unprotect the service from deletion
    bool UnprotectServiceFromDeletion(SC_HANDLE ServiceHandle);
    //Function to start the service
    bool StartService(SC_HANDLE ServiceHandle);

    // Function for opening the service handle
    SC_HANDLE OpenServiceHandle(const std::wstring& serviceName, DWORD accessRights);
};

#endif // SERVICEMANAGER_H
