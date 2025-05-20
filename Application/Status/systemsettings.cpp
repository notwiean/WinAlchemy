#include "systemsettings.h"
#include "Managers/registrymanager.h"

#include <filesystem>
#include <windows.h>
#include <powrprof.h>

SystemSettings::SystemSettings() {}

bool SystemSettings::SetPageFileSize(const std::wstring &path, const DWORD& minSizeMB, const DWORD& maxSizeMB)
{
    // Form the value string for PagingFiles
    std::wstring value = path + L" " + std::to_wstring(minSizeMB) + L" " + std::to_wstring(maxSizeMB);
    RegistryManager rm;

    if(!rm.SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", L"PagingFiles", value)) {
        qDebug() << "Failed to set page file size for " << path;
        return false;
    }

    qDebug() << "Successful setting page file size for " << path;
    return true;
}

// Function to disable Enhanced Pointer Precision in Windows
bool SystemSettings::DisableEnhancedPointerPrecision()
{
    RegistryManager rm;

    if(!rm.SetRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseSpeed", L"0"))
    {
        qDebug() << "Failed to disable enhanced pointer precision: failed to disable acceleration!";
        return false;
    }

    if(!rm.SetRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseThreshold1", L"0"))
    {
        qDebug() << "Failed to disable enhanced pointer precision: failed to disable acceleration!";
        return false;
    }

    if(!rm.SetRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseThreshold2", L"0"))
    {
        qDebug() << "Failed to disable enhanced pointer precision: failed to disable acceleration!";
        return false;
    }

    return true;
}

// Function for clearing user's temporary files
bool SystemSettings::ClearUserTempFiles()
{
    // Get the path to the temporary directory
    TCHAR tempPath[MAX_PATH] = { 0 };
    DWORD result = GetTempPath(MAX_PATH, tempPath);

    if (result == 0 || result > MAX_PATH) {
        qDebug() << "Failed to get temporary path. Error: " << GetLastError();
        return false;
    }

    // Convert path to std::filesystem::path
    std::filesystem::path tempDir(tempPath);

    // Make sure the path ends with a backslash
    if (!tempDir.empty() && tempDir.string().back() != '\\') {
        tempDir += L'\\';
    }

    // Display the message that cleaning has started
    qDebug() << "Cleaning temporary files in: " << tempDir.wstring();

    try
    {
        // const auto& entry is a reference to the current directory entry. Using const and & avoids copying and modifying the entry
        // std::filesystem::directory_iterator allows you to iterate over all elements (files and directories) in the specified tempDir directory
        for (const auto& entry : std::filesystem::directory_iterator(tempDir))
        {
            try
            {
                // A function that recursively deletes a file or directory at the specified path. It deletes the entire contents if it is a directory
                std::filesystem::remove_all(entry.path());
            }
            catch (const std::filesystem::filesystem_error& ex)
            {
                qDebug() << "Failed to delete: " << entry.path().wstring() << ". Error: " << ex.what();
            }
        }
        qDebug() << "Temporary files cleared successfully!";
        return true;
    }
    catch (const std::exception& ex)
    {
        qDebug() << "Error during cleanup: " << ex.what();
        return false;
    }
}

// Function for disable Memory Integrity (Core Isolation)
bool SystemSettings::DisableMemoryIntegrity()
{
    RegistryManager rm;

    if (!rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\DeviceGuard\\Scenarios\\HypervisorEnforcedCodeIntegrity"))
    {
        qDebug() << "Failed to create registry subkey!";
        return false;
    }

    if (!rm.SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\DeviceGuard\\Scenarios\\HypervisorEnforcedCodeIntegrity", L"Enabled", 0))
    {
        qDebug() << "Failed to create registry subkey!";
        return false;
    }

    qDebug() << "Successful DisableMemoryIntegrity!";
    return true;
}

// Function to set the “High Performance” mode
bool SystemSettings::SetHighPerformance()
{
    // GUID of the “High Performance” scheme
    GUID highPerformanceGuid = { 0x8c5e7fda, 0xe8bf, 0x4a96, { 0x9a, 0x85, 0xa6, 0xe2, 0x3a, 0x8c, 0x63, 0x5c } };

    // Set the “High Performance” mode
    if (PowerSetActiveScheme(NULL, &highPerformanceGuid) == ERROR_SUCCESS) {
        qDebug() << "The 'High Performance' plan has been successfully activated.";
        return true;
    }
    else {
        qDebug() << "Failed to set the power scheme. Error code: " << GetLastError();
        return false;
    }
}

// Function for disabling Windows Defender
bool SystemSettings::DisableWindowsDefender()
{
    LPCWSTR subKeyWindowsDefender = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender";
    LPCWSTR subKeyRealTimeProtection = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection";
    LPCWSTR subKeySignatureUpdate = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Signature Update";
    LPCWSTR subKeySpynet = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Spynet";

    RegistryManager rm;

    if (!rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableAntiSpyware", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableRealtimeMonitoring", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableAntiVirus", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableSpecialRunningModes", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableRoutinelyTakingAction", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"ServiceKeepAlive", 0) ||

        !rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection) ||

        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableBehaviorMonitoring", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableOnAccessProtection", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableRealtimeMonitoring", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableScanOnRealtimeEnable", 1) ||

        !rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeySignatureUpdate) ||

        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeySignatureUpdate, L"ForceUpdateFromMU", 1) ||

        !rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeySpynet) ||

        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeySpynet, L"DisableBlockAtFirstSeen", 1))
    {
        qDebug() << "Failed shutdown of Windows Defender!";
        return false;
    }

    qDebug() << "Successfully shutting down Windows Defender!";
    return true;
}

// Function for disabling Windows Update
bool SystemSettings::DisableWindowsUpdate()
{
    LPCWSTR subKeyWindowsUpdate = L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate";
    LPCWSTR subKeyAU = L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU";

    RegistryManager rm;

    if (!rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate) ||

        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DisableOSUpgrade", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DisableWindowsUpdateAccess", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DoNotConnectToWindowsUpdateInternetLocations", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"UpdateServiceUrlAlternate", L"wsus.localdomain.localserver") ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"WUServer", L"localserver.localdomain.wsus") ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"WUStatusServer", L"localserver.localdomain.wsus") ||

        !rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate) ||

        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyAU, L"NoAutoUpdate", 1) ||
        !rm.SetRegistryValue(HKEY_LOCAL_MACHINE, subKeyAU, L"UseWUServer", 1))
    {
        qDebug() << "Failed shutdown of Windows Update!";
        return false;
    }

    qDebug() << "Successfully shutting down Windows Update!";
    return true;
}
