#ifndef POWERSETTINGSMANAGER_H
#define POWERSETTINGSMANAGER_H

#include <windows.h>

class PowerSettingsManager
{
public:
    PowerSettingsManager();

    // Function for writing a value to the power settings
    bool WritePowerValue(const GUID *activeSchemeGuid, const GUID& subGroupGuid, const GUID& settingGuid, DWORD value);
    // Function for setting the power parameter
    bool SetPowerSetting(const GUID& settingGuid, const GUID& subGroupGuid, DWORD value);
};

#endif // POWERSETTINGSMANAGER_H
