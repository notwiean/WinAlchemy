#include "generalsettings.h"
#include "Managers/registrymanager.h"
#include "Managers/servicemanager.h"

#include <windows.h>
#include <powrprof.h>

GeneralSettings::GeneralSettings() {}

bool GeneralSettings::TamperProtectionIsEnable()
{
    try
    {
        // Reading Tamper Protection value from the registry
        RegistryManager rm;

        RegistryValue tamperProtectionValue = rm.ReadRegistryValue(
            HKEY_LOCAL_MACHINE, // Root key
            L"SOFTWARE\\Microsoft\\Windows Defender\\Features", // SubKey
            L"TamperProtection" // Value name
            );

        // Checking the value type and outputting the result
        if (std::holds_alternative<DWORD>(tamperProtectionValue))

        /*
            std::holds_alternative<T>(...) used to work with std::variant type.
            It allows to check if the std::variant object contains a value of a certain type T.
        */

        {
            DWORD value = std::get<DWORD>(tamperProtectionValue);

            /*
                std::get<T>(...) is used to safely retrieve a value if you are
                sure that std::variant contains a value of type T
            */

            if (value == 5)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            qDebug() << "Unsupported data type for Tamper Protection value.";
            return false;
        }
    }
    catch (const std::exception &e)
    {
        qDebug() << "Error: " << e.what();
        return false;
    }

    return 0;
}

bool GeneralSettings::WindowsDefenderIsEnable()
{
    if (GeneralSettings::TamperProtectionIsEnable())
    {
        qDebug() << "Windows Defender enabled, because Tamper Protection is enabled!";
        return true;
    }

    LPCWSTR subKeyWindowsDefender = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender";
    LPCWSTR subKeyRealTimeProtection = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection";
    LPCWSTR subKeySignatureUpdate = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Signature Update";
    LPCWSTR subKeySpynet = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Spynet";

    RegistryManager rm;

    if (rm.RegistryKeyExists(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection) &&
        rm.RegistryKeyExists(HKEY_LOCAL_MACHINE, subKeySignatureUpdate) &&
        rm.RegistryKeyExists(HKEY_LOCAL_MACHINE, subKeySpynet))
    {
        if (rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableAntiSpyware") &&
            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableRealtimeMonitoring") &&
            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableAntiVirus") &&
            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableSpecialRunningModes") &&
            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableRoutinelyTakingAction") &&
            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"ServiceKeepAlive") &&

            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableBehaviorMonitoring") &&
            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableOnAccessProtection") &&
            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableRealtimeMonitoring") &&
            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableScanOnRealtimeEnable") &&

            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeySignatureUpdate, L"ForceUpdateFromMU") &&

            rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeySpynet, L"DisableBlockAtFirstSeen"))
        {
            return false;
        }
    }

    return true;
}

bool GeneralSettings::WindowsUpdateIsEnable()
{
    LPCWSTR subKeyWindowsUpdate = L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate";
    LPCWSTR subKeyAU = L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU";

    RegistryManager rm;
    ServiceManager sm;

    if (!sm.IsServiceRunning(L"wuauserv"))
    {
        if (rm.RegistryKeyExists(HKEY_LOCAL_MACHINE, subKeyAU))
        {
            if (rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DisableOSUpgrade") &&
                rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DisableWindowsUpdateAccess") &&
                rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DoNotConnectToWindowsUpdateInternetLocations") &&
                rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"UpdateServiceUrlAlternate") &&
                rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"WUServer") &&
                rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"WUStatusServer") &&

                rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyAU, L"NoAutoUpdate") &&
                rm.RegistryValueExists(HKEY_LOCAL_MACHINE, subKeyAU, L"UseWUServer"))
            {
                return false;
            }
        }
    }

    return true;
}

bool GeneralSettings::DisableWindowsDefender()
{
    if (GeneralSettings::TamperProtectionIsEnable())
    {
        qDebug() << "Windows Defender cann't be disabled, because Tamper Protection is enabled!";
        return true;
    }

    LPCWSTR subKeyWindowsDefender = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender";
    LPCWSTR subKeyRealTimeProtection = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection";
    LPCWSTR subKeySignatureUpdate = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Signature Update";
    LPCWSTR subKeySpynet = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Spynet";

    RegistryManager rm;

    if (!rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyWindowsDefender) ||

        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableAntiSpyware", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableRealtimeMonitoring", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableAntiVirus", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableSpecialRunningModes", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableRoutinelyTakingAction", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"ServiceKeepAlive", static_cast<DWORD>(0)) ||

        !rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection) ||

        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableBehaviorMonitoring", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableOnAccessProtection", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableRealtimeMonitoring", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection, L"DisableScanOnRealtimeEnable", static_cast<DWORD>(1)) ||

        !rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeySignatureUpdate) ||

        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeySignatureUpdate, L"ForceUpdateFromMU", static_cast<DWORD>(1)) ||

        !rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeySpynet) ||

        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeySpynet, L"DisableBlockAtFirstSeen", static_cast<DWORD>(1)))
    {
        qDebug() << "Failed shutdown of Windows Defender!";
        return false;
    }

    qDebug() << "Successfully shutting down Windows Defender!";
    return true;
}

bool GeneralSettings::DisableWindowsUpdate()
{
    LPCWSTR subKeyWindowsUpdate = L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate";
    LPCWSTR subKeyAU = L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU";

    RegistryManager rm;
    ServiceManager sm;

    if (!rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate) ||

        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DisableOSUpgrade", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DisableWindowsUpdateAccess", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DoNotConnectToWindowsUpdateInternetLocations", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"UpdateServiceUrlAlternate", static_cast<std::wstring>(L"wsus.localdomain.localserver")) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"WUServer", static_cast<std::wstring>(L"localserver.localdomain.wsus")) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"WUStatusServer", static_cast<std::wstring>(L"localserver.localdomain.wsus")) ||

        !rm.CreateRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyAU) ||

        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyAU, L"NoAutoUpdate", static_cast<DWORD>(1)) ||
        !rm.CreateRegistryValue(HKEY_LOCAL_MACHINE, subKeyAU, L"UseWUServer", static_cast<DWORD>(1)) ||

        !sm.LockService(L"wuauserv"))
    {
        qDebug() << "Failed shutdown of Windows Update!";
        return false;
    }

    qDebug() << "Successfully shutting down Windows Update!";
    return true;
}

bool GeneralSettings::EnableWindowsDefender()
{
    LPCWSTR subKeyWindowsDefender = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender";
    LPCWSTR subKeyRealTimeProtection = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection";
    LPCWSTR subKeySignatureUpdate = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Signature Update";
    LPCWSTR subKeySpynet = L"SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Spynet";

    RegistryManager rm;

    if (!rm.DeleteRegistrySubkey(HKEY_LOCAL_MACHINE, subKeySpynet) ||
        !rm.DeleteRegistrySubkey(HKEY_LOCAL_MACHINE, subKeySignatureUpdate) ||
        !rm.DeleteRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyRealTimeProtection) ||

        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"ServiceKeepAlive") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableRoutinelyTakingAction") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableSpecialRunningModes") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableAntiVirus") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableRealtimeMonitoring") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsDefender, L"DisableAntiSpyware"))
    {
        qDebug() << "Failed to turn on of Windows Defender!";
        return false;
    }

    qDebug() << "Successfully Windows Defender activation!";
    return true;
}

bool GeneralSettings::EnableWindowsUpdate()
{
    LPCWSTR subKeyWindowsUpdate = L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate";
    LPCWSTR subKeyAU = L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU";

    RegistryManager rm;
    ServiceManager sm;

    if (!rm.DeleteRegistrySubkey(HKEY_LOCAL_MACHINE, subKeyAU) ||

        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"WUStatusServer") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"WUServer") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"UpdateServiceUrlAlternate") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DoNotConnectToWindowsUpdateInternetLocations") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DisableWindowsUpdateAccess") ||
        !rm.DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKeyWindowsUpdate, L"DisableOSUpgrade") ||

        !sm.UnlockService(L"wuauserv"))
    {
        qDebug() << "Failed to turn on of Windows Update!";
        return false;
    }

    qDebug() << "Successfully Windows Update activation!";
    return true;
}
