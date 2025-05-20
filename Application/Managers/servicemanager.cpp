#include "servicemanager.h"

#include <QDebug>

ServiceManager::ServiceManager() {}

bool ServiceManager::StopService(SC_HANDLE ServiceHandle)
{
    SERVICE_STATUS Status;

    // Get the current state of the service
    if (!QueryServiceStatus(ServiceHandle, &Status))
    {
        return false;
    }

    // If the service is already stopped, do nothing
    if (Status.dwCurrentState == SERVICE_STOPPED)
    {
        return true;
    }

    // Send a command to stop the service
    if (!ControlService(
            ServiceHandle,           // This is the service descriptor obtained earlier using OpenService
            SERVICE_CONTROL_STOP,    // Specifies the control command to be sent to the service.
            &Status))                // Will be populated with information about the current state of the service after the command is executed.
    {
        return false;
    }

    // Wait for the service to stop
    while (Status.dwCurrentState != SERVICE_STOPPED)
    {
        Sleep(100); // Wait 100 ms before checking again
        if (!QueryServiceStatus(ServiceHandle, &Status))
        {
            return false; // If the service state could not be obtained, return false
        }
    }

    return true;
}

bool ServiceManager::DisableServiceStartup(SC_HANDLE ServiceHandle)
{
    if (!ChangeServiceConfig(
            ServiceHandle,       // Service descriptor
            SERVICE_NO_CHANGE,   // Service type (do not change)
            SERVICE_DISABLED,    // Startup mode: disabled
            SERVICE_NO_CHANGE,   // Error control (do not change)
            NULL,                // Path to executable file (do not change)
            NULL,                // Boot group (do not change)
            NULL,                // Load group tag identifier (do not change)
            NULL,                // Service dependencies (do not change)
            NULL,                // Account name (do not change)
            NULL,                // Account password (do not change)
            NULL))               // Displayed service name (do not change)
    {
        return false;
    }
    return true;
}

// Function to protect the service from changes
bool ServiceManager::ProtectServiceFromChanges(SC_HANDLE ServiceHandle)
{
    // Protect service parameters from changes
    if (!ChangeServiceConfig2( // The function is used to change additional Windows service settings
            ServiceHandle, // This is the service descriptor that was obtained using the OpenService functions
            SERVICE_CONFIG_SERVICE_SID_INFO, // This is the parameter that indicates that we want to change the SID (Security Identifier) information of the service
            NULL)) /* The third parameter(lpInfo) is NULL, it means that we set the SID type for the service as SERVICE_SID_TYPE_NONE.
        Setting SERVICE_SID_TYPE_NONE protects the service from change because it removes the ability to use special access rights through the SID */
    {
        return false;
    }

    return true;
}

// Function to protect the service from deletion
bool ServiceManager::ProtectServiceFromDeletion(SC_HANDLE ServiceHandle)
{
    // Set protection flag against deletion
    SECURITY_DESCRIPTOR SecurityDescriptor; // Variable that will be used to store the new service security configuration

    // Initializes the SECURITY_DESCRIPTOR structure
    if (!InitializeSecurityDescriptor(
            &SecurityDescriptor, // Points to a previously created security descriptor
            SECURITY_DESCRIPTOR_REVISION)) // Indicates the version of the security descriptor format (typically the SECURITY_DESCRIPTOR_REVISION value is used)
    {
        return false;
    }

    //  Sets the DACL (Discretionary Access Control List) to a security descriptor.
    if (!SetSecurityDescriptorDacl(
            &SecurityDescriptor, // Indicates the security descriptor we are modifying.
            TRUE, // Indicates that the DACL is to be activated (it will be used for access control)
            NULL, // Indicates that the DACL will be empty (no users or groups will have access rights)
            FALSE)) // Indicates that the DACL has been explicitly set by the user or program
    {
        return false;
    }

    if (!SetServiceObjectSecurity( // The function is used to set a security descriptor (SECURITY_DESCRIPTOR) on a service object
            ServiceHandle, // This is the service descriptor obtained earlier
            DACL_SECURITY_INFORMATION, // This parameter specifies what type of information we want to set in the security descriptor
            &SecurityDescriptor)) // This is a pointer to a SECURITY_DESCRIPTOR structure that contains the new security configuration for the service
    {
        return false;
    }

    return true;
}

bool ServiceManager::EnableServiceStartup(SC_HANDLE ServiceHandle)
{
    if (!ChangeServiceConfig(
            ServiceHandle,       // Service descriptor
            SERVICE_NO_CHANGE,   // Service type (do not change)
            SERVICE_AUTO_START,  // Startup mode: auto start
            SERVICE_NO_CHANGE,   // Error control (do not change)
            NULL,                // Path to executable file (do not change)
            NULL,                // Boot group (do not change)
            NULL,                // Load group tag identifier (do not change)
            NULL,                // Service dependencies (do not change)
            NULL,                // Account name (do not change)
            NULL,                // Account password (do not change)
            NULL))               // Displayed service name (do not change)
    {
        return false;
    }
    return true;
}

bool ServiceManager::UnprotectServiceFromChanges(SC_HANDLE ServiceHandle)
{
    SERVICE_SID_INFO sidInfo;
    sidInfo.dwServiceSidType = SERVICE_SID_TYPE_UNRESTRICTED;

    if (!ChangeServiceConfig2(
            ServiceHandle,
            SERVICE_CONFIG_SERVICE_SID_INFO,
            &sidInfo))
    {
        return false;
    }
    return true;
}

bool ServiceManager::UnprotectServiceFromDeletion(SC_HANDLE ServiceHandle)
{
    SECURITY_DESCRIPTOR SecurityDescriptor;

    if (!InitializeSecurityDescriptor(
            &SecurityDescriptor,
            SECURITY_DESCRIPTOR_REVISION))
    {
        return false;
    }

    // Installing a DACL that allows access
    if (!SetSecurityDescriptorDacl(
            &SecurityDescriptor,
            TRUE,
            NULL,
            FALSE))
    {
        return false;
    }

    if (!SetServiceObjectSecurity(
            ServiceHandle,
            DACL_SECURITY_INFORMATION,
            &SecurityDescriptor))
    {
        return false;
    }

    return true;
}

bool ServiceManager::StartService(SC_HANDLE ServiceHandle)
{
    SERVICE_STATUS status;

    // Verification of the current status of the service
    if (!QueryServiceStatus(ServiceHandle, &status))
    {
        return false;
    }

    // If the service is already running, do nothing
    if (status.dwCurrentState == SERVICE_RUNNING)
    {
        return true;
    }

    // Service startup
    if (!::StartService(
            ServiceHandle,  // Service descriptor
            0,             // Number of arguments
            NULL))         // Arguments (if any)
    {
        return false;
    }

    // Waiting for the service to start
    while (status.dwCurrentState != SERVICE_RUNNING)
    {
        Sleep(100); // Waiting 100 ms before retesting
        if (!QueryServiceStatus(ServiceHandle, &status))
        {
            return false; // If the service state could not be retrieved, return false
        }
    }

    return true;
}

SC_HANDLE ServiceManager::OpenServiceHandle(const std::wstring &serviceName, DWORD accessRights)
{
    SC_HANDLE scm = OpenSCManager(
        NULL,                  // Name of the remote machine or NULL for the local machine
        NULL,                  // Name of the services database or NULL for a standard database
        SC_MANAGER_ALL_ACCESS  // Required access rights
        );
    if (scm == NULL) {
        qDebug() << "Failed to open SCM! Service: " << serviceName;
        return nullptr;
    }

    SC_HANDLE service = OpenService(
        scm,                  // SCM descriptor obtained via OpenSCManager
        serviceName.c_str(),  // Service Name
        accessRights          // Required access rights to the service
        );
    if (service == NULL) {
        qDebug() << "Failed to open service! Service: " << serviceName;
        CloseServiceHandle(scm); // Close SCM if the service could not be opened
        return nullptr;
    }

    CloseServiceHandle(scm); // Closing SCM as it is no longer needed.
    return service;
}

// Function to fully lock down a service and protect its parameters
bool ServiceManager::LockService(const std::wstring& serviceName)
{
    SC_HANDLE service = OpenServiceHandle(serviceName, SERVICE_ALL_ACCESS);
    if (service == nullptr) {
        return false;
    }

    bool result = false;

    // Stop the service
    if (!StopService(service))
    {
        qDebug() << "Failed to stop service! Service: " << serviceName;
        goto cleanup;
    }

    // Disable service startup
    if (!DisableServiceStartup(service))
    {
        qDebug() << "Failed to disable service startup! Service: " << serviceName;
        goto cleanup;
    }

    // Call the ProtectService function to protect the service from changes
    if (!ProtectServiceFromChanges(service))
    {
        qDebug() << "Failed to protect the service from changes! Service: " << serviceName;
        goto cleanup;
    }

    // Call the ProtectService function to protect the service from deletion
    if (!ProtectServiceFromDeletion(service))
    {
        qDebug() << "Failed to protect the service from deletion! Service: " << serviceName;
        goto cleanup;
    }

    result = true;

cleanup:
    // Close handle (if it's open)
    if (service != NULL) {
        CloseServiceHandle(service);
    }

    return result;
}

bool ServiceManager::UnlockService(const std::wstring &serviceName)
{
    SC_HANDLE service = OpenServiceHandle(serviceName, SERVICE_ALL_ACCESS);
    if (service == nullptr) {
        return false;
    }

    bool result = false;

    // Enabling service autorun
    if (!EnableServiceStartup(service))
    {
        qDebug() << "Failed to enable service startup! Service: " << serviceName;
        goto cleanup;
    }

    // Removing protection against change
    if (!UnprotectServiceFromChanges(service))
    {
        qDebug() << "Failed to unprotect the service from changes! Service: " << serviceName;
        goto cleanup;
    }

    // Removing protection against deletion
    if (!UnprotectServiceFromDeletion(service))
    {
        qDebug() << "Failed to unprotect the service from deletion! Service: " << serviceName;
        goto cleanup;
    }

    // Starting the service
    if (!StartService(service))
    {
        qDebug() << "Failed to start service! Service: " << serviceName;
        goto cleanup;
    }

    result = true;

cleanup:
    // Closing the handle (if it is open)
    if (service != NULL) {
        CloseServiceHandle(service);
    }

    return result;
}

// Function to check if the service is running
bool ServiceManager::IsServiceRunning(const std::wstring &serviceName)
{
    SC_HANDLE service = OpenServiceHandle(serviceName, SERVICE_QUERY_STATUS);
    if (service == NULL)
    {
        qDebug() << "Failed to open service! Service: " << serviceName;

        CloseServiceHandle(service);
        return false;
    }

    SERVICE_STATUS status;
    if (!QueryServiceStatus(service, &status))
    {
        qDebug() << "Service Status Query error! Service: " << serviceName;

        CloseServiceHandle(service);
        return false;
    }

    CloseServiceHandle(service);
    return (status.dwCurrentState == SERVICE_RUNNING);
}
