#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include <string>

// Pre-declaration for DWORD
#ifndef _WINDOWS_
using DWORD = unsigned long;
#endif

class SystemSettings
{
public:
    SystemSettings();

    // Function for changing the size of the swap file (pagefile.sys) in Windows via the registry
    bool SetPageFileSize(const std::wstring& path, const DWORD& minSizeMB, const DWORD& maxSizeMB);
    // Function to disable Enhanced Pointer Precision in Windows
    bool DisableEnhancedPointerPrecision();
    // Function for clearing user's temporary files
    bool ClearUserTempFiles();
    // Function for disable Memory Integrity (Core Isolation)
    bool DisableMemoryIntegrity();
    // Function to set the “High Performance” mode
    bool SetHighPerformance();
    // Function for disabling Windows Defender
    bool DisableWindowsDefender();
    // Function for disabling Windows Update
    bool DisableWindowsUpdate();
};

#endif // SYSTEMSETTINGS_H
