#include "additionalsettings.h"
#include "Managers/registrymanager.h"
#include "Managers/powersettingsmanager.h"

#include <windows.h>
#include <powrprof.h>
#include <initguid.h>

// GUID for the sleep subgroup
DEFINE_GUID(GUID_SLEEP_SUBGROUP,
            0x238C9FA8, 0x0AAD, 0x41ED, 0x83, 0xF4, 0x97, 0xBE, 0x24, 0x2C, 0x8F, 0x20);
// GUID for the video subgroup
DEFINE_GUID(GUID_VIDEO_SUBGROUP,
            0x7516B95F, 0xF776, 0x4464, 0x8C, 0x53, 0x06, 0x16, 0x7F, 0x40, 0xCC, 0x99);
// GUID for the display disable parameter
DEFINE_GUID(GUID_VIDEO_POWERDOWN_TIMEOUT,
            0x3C0BC021, 0xC8A8, 0x4E07, 0xA9, 0x73, 0x6B, 0x14, 0xCB, 0xCB, 0x2B, 0x7E);
// GUID for the sleep parameter
DEFINE_GUID(GUID_STANDBY_TIMEOUT,
            0x29F6C1DB, 0x86DA, 0x48C5, 0x9F, 0xDB, 0xF2, 0xB6, 0x7B, 0x1F, 0x44, 0xDA);

AdditionalSettings::AdditionalSettings() {}

bool AdditionalSettings::SetPageFileSize(const std::wstring &disk, const DWORD &minSizeMB, const DWORD &maxSizeMB)
{
    // Form the value string for PagingFiles
    std::wstring value = disk + L":\\pagefile.sys " + std::to_wstring(minSizeMB) + L" " + std::to_wstring(maxSizeMB);
    RegistryManager rm;

    if(!rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", L"PagingFiles", value)) {
        qDebug() << "Failed to set page file size for " << disk;
        return false;
    }

    return true;
}

// Function to disable Enhanced Pointer Precision in Windows
bool AdditionalSettings::DisableEnhancedPointerPrecision()
{
    RegistryManager rm;
    DWORD value = 0;

    if(!rm.CreateRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseSpeed", value))
    {
        qDebug() << "Failed to disable enhanced pointer precision: failed to disable acceleration!";
        return false;
    }

    if(!rm.CreateRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseThreshold1", value))
    {
        qDebug() << "Failed to disable enhanced pointer precision: failed to disable acceleration!";
        return false;
    }

    if(!rm.CreateRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseThreshold2", value))
    {
        qDebug() << "Failed to disable enhanced pointer precision: failed to disable acceleration!";
        return false;
    }

    return true;
}

// Function for disable Memory Integrity (Core Isolation)
bool AdditionalSettings::DisableMemoryIntegrity()
{
    RegistryManager rm;
    DWORD value = 0;

    if (!rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\DeviceGuard\\Scenarios\\HypervisorEnforcedCodeIntegrity"))
    {
        qDebug() << "Failed to create registry subkey!";
        return false;
    }

    if (!rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\DeviceGuard\\Scenarios\\HypervisorEnforcedCodeIntegrity", L"Enabled", value))
    {
        qDebug() << "Failed to create registry subkey!";
        return false;
    }

    return true;
}

bool AdditionalSettings::SetHighPerformance()
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

bool AdditionalSettings::DisableSleepMode()
{
    // GUID for the display disable parameter
    const GUID& displayTimeoutSettingGuid = GUID_VIDEO_POWERDOWN_TIMEOUT;
    // GUID for the sleep parameter
    const GUID& sleepTimeoutSettingGuid = GUID_STANDBY_TIMEOUT;

    // GUID for the video subgroup
    const GUID& videoSubgroupGuid = GUID_VIDEO_SUBGROUP;
    // GUID for the sleep subgroup
    const GUID& sleepSubgroupGuid = GUID_SLEEP_SUBGROUP;

    PowerSettingsManager psm;

    // Disabling display timeout
    if (!psm.SetPowerSetting(displayTimeoutSettingGuid, videoSubgroupGuid, 0))
    {
        qDebug() << "Failed to disable display timeout!";
        return false;
    }

    // Disabling sleep mode
    if (!psm.SetPowerSetting(sleepTimeoutSettingGuid, sleepSubgroupGuid, 0))
    {
        qDebug() << "Failed to disable sleep timeout!";
        return false;
    }

    return true;
}

bool AdditionalSettings::BackupAllSettings()
{
    // Folder for backup
    std::wstring backupFolder = L"C:\\RegistryBackups";

    // Registry keys for backup
    std::vector<std::wstring> registryKeysForBackup {
            L"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Power\\User\\PowerSchemes",
            L"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management",
            L"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Power\\User\\PowerSchemes",
            L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows Defender",
            L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate",
            L"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\DeviceGuard\\Scenarios",
            L"HKEY_CURRENT_USER\\Control Panel\\Mouse"
        };

    RegistryManager rm;

    if (!rm.BackupRegistryKeys(backupFolder, registryKeysForBackup))
    {
        qDebug() << "Something went wrong during the backup!";
    }

    return true;
}

