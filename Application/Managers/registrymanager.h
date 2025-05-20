#ifndef REGISTRYMANAGER_H
#define REGISTRYMANAGER_H

#include <QDebug>
#include <windows.h>
#include <string>

// Registry data types
using RegistryValue = std::variant<DWORD, std::wstring, std::vector<BYTE>>;

class RegistryManager
{
public:
    RegistryManager();

    // Function for reading a value from the registry
    RegistryValue ReadRegistryValue(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName);

    // Function for creating a registry subkey
    bool CreateRegistrySubkey(HKEY rootKey, const LPCWSTR& subkey);
    // Function for deleting a registry subkey
    bool DeleteRegistrySubkey(HKEY rootKey, const LPCWSTR& subkey);

    // Function for setting a value in the registry
    template <typename T>
    bool CreateRegistryValue(HKEY rootKey, const std::wstring& subkey, const std::wstring& valueName, const T& value);
    // Function for deleting a registry value
    bool DeleteRegistryValue(HKEY rootKey, const std::wstring& subkey, const std::wstring& valueName);

    // Function to check if such a key exists
    bool RegistryKeyExists(HKEY rootKey, const LPCWSTR& subKey);
    // Function to check if such a value exists
    bool RegistryValueExists(HKEY rootKey, const std::wstring& subKey, const std::wstring& valueName);

    // Function for back up specified registry keys
    bool BackupRegistryKeys(const std::wstring& backupFolder,
                            const std::vector<std::wstring>& keysToBackup);
private:
    // Function for creating a backup directory
    bool CreateBackupDirectory(const std::wstring& path);
    // Function for export registry key
    bool ExportRegistryKey(const std::wstring& keyPath, const std::wstring& backupFilePath);
};

template<typename T>
bool RegistryManager::CreateRegistryValue(HKEY rootKey, const std::wstring& subkey, const std::wstring& valueName, const T& value)
{
    HKEY hKey;
    LONG result;

    // Open the registry key
    result = RegOpenKeyEx(
        rootKey, // Root registry partition to open
        subkey.c_str(), // Path to the registry subsection to be opened
        0, // Reserved, must be 0
        KEY_WRITE, // Access rights to the registry section
        &hKey // Pointer to a variable that will receive the descriptor of an open registry partition
        );

    if (result != ERROR_SUCCESS) {
        qDebug() << "Failed to open registry key: " << subkey;
        return false;
    }

    // Determine the value type based on the type of T
    DWORD valueType;
    if constexpr (std::is_same_v<T, std::wstring>) {
        valueType = REG_SZ;
    } else if constexpr (std::is_same_v<T, DWORD>) {
        valueType = REG_DWORD;
    } else {
        // Handle unsupported types (optional)
        qDebug() << "Unsupported value type!";
        RegCloseKey(hKey);
        return false;
    }

    /*
    This is a C++17 construct that allows you to perform type checking at compile time.
    If the condition is true, the corresponding code block will be compiled;
    if false, it will be skipped.
    */

    // Set the value in the registry
    if constexpr (std::is_same_v<T, std::wstring>) {
        result = RegSetValueEx(
            hKey, // Handle to an open registry key.
            valueName.c_str(), // Name of the value to set.
            0, // Reserved parameter, must be zero.
            valueType, // Type of the value being set (e.g., REG_SZ for strings).
            reinterpret_cast<const BYTE*>(value.c_str()), // Pointer to the string data as a byte array.
            (value.size() + 1) * sizeof(wchar_t) // Size of the data in bytes, including the null terminator.
            );
    } else if constexpr (std::is_same_v<T, DWORD>) {
        result = RegSetValueEx(
            hKey,
            valueName.c_str(),
            0,
            valueType,
            reinterpret_cast<const BYTE*>(&value),
            sizeof(DWORD)
            );
    }

    // Close the registry key
    RegCloseKey(hKey);

    // Check if setting the value was successful
    if (result != ERROR_SUCCESS) {
        qDebug() << "Failed to set registry value: " << valueName;
        return false;
    }

    return true;
}

#endif // REGISTRYMANAGER_H
