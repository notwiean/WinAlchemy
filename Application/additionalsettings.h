#ifndef ADDITIONALSETTINGS_H
#define ADDITIONALSETTINGS_H

#include <string>

using DWORD = unsigned long;

class AdditionalSettings
{
public:
    AdditionalSettings();

    bool SetPageFileSize(const std::wstring &disk, const DWORD& minSizeMB, const DWORD& maxSizeMB);
    // Function for disable Enhanced Pointer Precision in Windows
    bool DisableEnhancedPointerPrecision();
    // Function for disable Memory Integrity (Core Isolation)
    bool DisableMemoryIntegrity();
    // Function to set the “High Performance” mode
    bool SetHighPerformance();
    // Function for disable sleep mode
    bool DisableSleepMode();
    // Function for backup settings
    bool BackupAllSettings();
};

#endif // ADDITIONALSETTINGS_H
