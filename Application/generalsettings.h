#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

class GeneralSettings
{
public:
    GeneralSettings();

    // Function to check if Tamper Protection is enabled
    bool TamperProtectionIsEnable();

    // Function to check if Windows Defender is enabled
    bool WindowsDefenderIsEnable();
    // Function to check if Windows Update is enabled
    bool WindowsUpdateIsEnable();

    // Function for disabling Windows Defender
    bool DisableWindowsDefender();
    // Function for disabling Windows Update
    bool DisableWindowsUpdate();

    // Function for enabling Windows Defender
    bool EnableWindowsDefender();
    // Function for enabling Windows Update
    bool EnableWindowsUpdate();
};

#endif // GENERALSETTINGS_H
