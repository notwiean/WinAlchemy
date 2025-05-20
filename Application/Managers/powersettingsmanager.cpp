#include "powersettingsmanager.h"

#include <powrprof.h>
#include <QDebug>

PowerSettingsManager::PowerSettingsManager() {}

bool PowerSettingsManager::WritePowerValue(const GUID *activeSchemeGuid, const GUID &subGroupGuid, const GUID &settingGuid, DWORD value)
{
    // Check for null pointer
    if (!activeSchemeGuid)
    {
        qDebug() << "Error: activeSchemeGuid is nullptr!";
        return false;
    }

    // Function call for setting the mains power supply (AC)
    DWORD resultAC = PowerWriteACValueIndex(
        nullptr,               // Root power key (NULL for default)
        activeSchemeGuid,      // Active power scheme GUID
        &subGroupGuid,         // Subgroup GUID
        &settingGuid,          // Specific power setting GUID
        value                  // Value to set
        );

    // Checking the result for AC
    if (resultAC != ERROR_SUCCESS)
    {
        qDebug() << "Failed to set AC value for the power setting!";
        return false;
    }

    // Function call for battery power (DC) setting
    DWORD resultDC = PowerWriteDCValueIndex(
        nullptr,               // Root power key (NULL for default)
        activeSchemeGuid,      // Active power scheme GUID
        &subGroupGuid,         // Subgroup GUID
        &settingGuid,          // Specific power setting GUID
        value                  // Value to set
        );

    // Checking the result for DC
    if (resultDC != ERROR_SUCCESS)
    {
        qDebug() << "Failed to set DC value for the power setting!";
        return false;
    }

    return true; // Successful execution
}

bool PowerSettingsManager::SetPowerSetting(const GUID &settingGuid, const GUID &subGroupGuid, DWORD value)
{
    // Open the active energy saving scheme
    GUID* activeSchemeGuid = nullptr;
    DWORD result = PowerGetActiveScheme(NULL, &activeSchemeGuid);

    // Checking for successful acquisition of an active circuit
    if (result != ERROR_SUCCESS)
    {
        qDebug() << "Failed to get active power scheme!";
        return false;
    }

    // Use unique_ptr to automatically free memory
    // std::unique_ptr<(Type of object), (Type of removal method)> schemeGuard(Object, Removal method)
    std::unique_ptr<GUID, decltype(&LocalFree)> schemeGuard(activeSchemeGuid, LocalFree);

    // Write the value
    if (!WritePowerValue(activeSchemeGuid, subGroupGuid, settingGuid, value))
    {
        qDebug() << "Failed to write power value!";
        return false;
    }

    return true;
}
