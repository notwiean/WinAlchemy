#include "registrymanager.h"

#include <shlobj.h>
#include <algorithm>

RegistryManager::RegistryManager() {}

// Function for reading a value from the registry
RegistryValue RegistryManager::ReadRegistryValue(HKEY rootKey, const std::wstring &subKey, const std::wstring &valueName)
{
    HKEY hKey = nullptr;
    LONG result = RegOpenKeyEx(
        rootKey, // Root section of the registry
        subKey.c_str(), // Path to the registry subsection to be opened
        0, // Key opening options
        KEY_READ, // Access mask
        &hKey // Pointer to a variable that will receive the public key handle (descriptor)
        );

    if (result != ERROR_SUCCESS)
    {
        throw std::runtime_error("Error opening a registry key!");
    }

    // Define data type and size
    DWORD dataType; // Variable that will store the data type of the value in the registry
    DWORD dataSize; // Variable that will store the size of the value data in the registry (in bytes)
    result = RegQueryValueEx(
        hKey, // Handle to the open registry key
        valueName.c_str(), // Name of the value to query
        nullptr, // Reserved, must be NULL
        &dataType, // Pointer to a variable that receives the data type
        nullptr, // Pointer to a buffer that receives the data (NULL to get the size only)
        &dataSize // Pointer to a variable that receives the size of the data (in bytes)
        );

    if (result != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        throw std::runtime_error("Data type and size definition error!");
    }

    // Read data
    std::vector<BYTE> buffer(dataSize); // Create a buffer to store the data

    /*
        std::vector<BYTE> buffer(dataSize) is a dynamic byte array that can store any data as a sequence of bytes.
        In the context of working with the Windows registry, this buffer can contain data of different types,
        depending on what was read from the registry.

        For example, for the string “Hello”, the buffer will contain: H (0x48), e (0x65), l (0x6C), l (0x6C), o (0x6F), \0 (0x00)
    */

    result = RegQueryValueEx(
        hKey, // Handle to the open registry key
        valueName.c_str(), // Name of the value to query
        nullptr, // Reserved, must be NULL
        &dataType, // Pointer to a variable that receives the data type
        buffer.data(), // Pointer to the buffer that will store the data
        &dataSize // Pointer to a variable that specifies the size of the buffer
        );

    if (result != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        throw std::runtime_error("Error reading data from the registry!");
    }

    // Close the registry key
    RegCloseKey(hKey);

    // Return value depending on the data type

    switch (dataType)
    {
    case REG_DWORD:
        return *reinterpret_cast<DWORD*>(buffer.data()); // Converting raw data from buffer to DWORD type value

    /*
        - buffer.data(): If buffer contains bytes {0x39, 0x30, 0x00, 0x00}, then buffer.data() will return a pointer to the first byte (0x39).
        - reinterpret_cast<DWORD*>(...): reinterpret_cast is a type conversion operator in C++ that allows you to interpret a pointer of one type as a pointer of another type.
        In this case BYTE* (a pointer to a byte) is cast to DWORD* (a pointer to a 32-bit integer).

        How it works: buffer.data() returns a BYTE* (a pointer to a byte array). reinterpret_cast<DWORD*>(buffer.data()) interprets this pointer as a pointer to a DWORD.
    */

    case REG_SZ:
        return std::wstring(reinterpret_cast<wchar_t*>(buffer.data())); // Works similarly, but cast to the std::wstring data type

    default:
        throw std::runtime_error("Unsupported registry data type!");
    }
}

// Function for creating a registry subkey
bool RegistryManager::CreateRegistrySubkey(HKEY rootKey, const LPCWSTR &subkey)
{
    HKEY hKey = nullptr;
    LONG result = RegCreateKeyEx(
        rootKey, // The parent section of the registry
        subkey, // The name of the subsection to be created.
        0, // Reserved, must be 0
        NULL, // The class of the partition(not used, you can specify NULL)
        REG_OPTION_NON_VOLATILE, // Partition options (REG_OPTION_NON_VOLATILE means that the partition is saved after reloadng)
        KEY_WRITE, // Access level (KEY_WRITE allows writing data to the partition)
        NULL, // Security attributes (NULL means default)
        &hKey, // Pointer to a variable that will get the descriptor of the created partition
        NULL // Pointer to a variable that will get information about whether the partition was created or opened (not used)
        );

    if (result != ERROR_SUCCESS)
    {
        qDebug() << "Failed to create registry subkey! Error code: " << result;
        return false;
    }

    if (hKey != nullptr)
    {
        RegCloseKey(hKey);
    }

    return true;
}

bool RegistryManager::DeleteRegistrySubkey(HKEY rootKey, const LPCWSTR &subkey)
{
    // Check if the key exists before deleting it
    if (!RegistryKeyExists(rootKey, subkey))
    {
        return true; // // Key does not exist, return true
    }

    // Delete the registry subsection
    LONG result = RegDeleteTree(
        rootKey, // Parent section of the registry
        subkey  // Name of the subsection to be deleted
        );

    if (result != ERROR_SUCCESS)
    {
        qDebug() << "Failed to delete registry subkey! Error code: " << result;
        return false;
    }

    return true;
}

bool RegistryManager::DeleteRegistryValue(HKEY rootKey, const std::wstring &subkey, const std::wstring &valueName)
{
    // Check if the value exists before deletion
    if (!RegistryValueExists(rootKey, subkey, valueName)) {
        return true; // If the value does not exist, return true
    }

    HKEY hKey;
    LONG result;

    // Open the registry key
    result = RegOpenKeyEx(
        rootKey, // Root section of the registry
        subkey.c_str(), // Path to the registry subsection
        0, // Reserved, should be 0
        KEY_WRITE, // Write access rights
        &hKey // Pointer to a variable that will receive the descriptor of an open registry partition
        );

    if (result != ERROR_SUCCESS) {
        qDebug() << "Failed to open registry key: " << subkey;
        return false;
    }

    // Deleting a value from the registry
    result = RegDeleteValue(
        hKey, // Registry public key descriptor
        valueName.c_str() // Name of the value to be deleted
        );

    // Close the registry key
    RegCloseKey(hKey);

    // Check if the value was successfully deleted
    if (result != ERROR_SUCCESS) {
        qDebug() << "Failed to delete a registry value: " << valueName;
        return false;
    }

    return true;
}

bool RegistryManager::RegistryKeyExists(HKEY rootKey, const LPCWSTR &subKey)
{
    HKEY hKey;
    // Trying to open the registry key
    LONG result = RegOpenKeyEx(
        rootKey,   // Root registry partition
        subKey,    // Path to subKey
        0,         // Flags (0 by default)
        KEY_READ,  // Requested access rights (KEY_READ is sufficient to verify existence)
        &hKey      // Public key pointer
        );

    if (result == ERROR_SUCCESS) {
        // The key exists, close it
        RegCloseKey(hKey);
        return true;
    } else if (result == ERROR_FILE_NOT_FOUND) {
        // The key doesn't exist
        return false;
    } else {
        // There was another error
        qDebug() << "Failed to check registry key! Error code:" << result;
        return false;
    }
}

bool RegistryManager::RegistryValueExists(HKEY rootKey, const std::wstring &subKey, const std::wstring &valueName)
{
    HKEY hKey;
    LONG result;

    // Open the registry key
    result = RegOpenKeyEx(
        rootKey,   // Root registry partition
        subKey.c_str(), // Path to subsection
        0,         // Flags (0 by default)
        KEY_READ,  // Requested access rights (KEY_READ is sufficient for verification)
        &hKey      // Public key pointer
        );

    if (result != ERROR_SUCCESS) {
        // If the key could not be opened, then the value definitely does not exist
        qDebug() << "Failed to open registry key! Error code:" << result;
        return false;
    }

    // Check if the value exists
    DWORD type;
    DWORD dataSize = 0;
    result = RegQueryValueEx(
        hKey,           // Public key descriptor
        valueName.c_str(), // Value Name
        nullptr,        // Reserved (must be nullptr)
        &type,          // Pointer to a variable for a data type (optional)
        nullptr,        // Pointer to the buffer for data (not needed, as we only check for existence)
        &dataSize       // Pointer to a variable for the data size
        );

    // Close the registry key
    RegCloseKey(hKey);

    if (result == ERROR_SUCCESS) {
        // Value exists
        return true;
    } else if (result == ERROR_FILE_NOT_FOUND) {
        // Value does not exist
        return false;
    } else {
        // There was another error
        qDebug() << "Error when checking registry value! Error code:" << result;
        return false;
    }
}

bool RegistryManager::BackupRegistryKeys(const std::wstring &backupFolder, const std::vector<std::wstring> &keysToBackup)
{
    // Create a folder for backups
    if (!CreateBackupDirectory(backupFolder)) {
        qDebug() << L"Failed to create backup directory: " << backupFolder;
        return false;
    }

    bool allSuccess = true;

    for (const auto& fullKeyPath : keysToBackup) {
        // Form the file name from the key path
        std::wstring fileName = fullKeyPath; // Original key path
        std::replace(fileName.begin(), fileName.end(), L'\\', L'_'); // Replaces all \ with _
        std::replace(fileName.begin(), fileName.end(), L':', L'_'); // Replaces all : with _
        std::wstring fullPath = backupFolder + L"\\" + fileName + L".reg"; // Generating the full path of a file

        // Exporting
        if (!ExportRegistryKey(fullKeyPath, fullPath)) {
            qDebug() << L"Failed to export key: " << fullKeyPath;
            allSuccess = false;
        }
    }

    return allSuccess;
}

// Function for creating a backup directory
bool RegistryManager::CreateBackupDirectory(const std::wstring &path)
{
    // SHCreateDirectoryEx creates a directory (folder) along with all necessary parent directories (recursively)
    int result = SHCreateDirectoryEx(nullptr, path.c_str(), nullptr);
    return (result == ERROR_SUCCESS) || (result == ERROR_ALREADY_EXISTS);
}

// Function for export registry key
bool RegistryManager::ExportRegistryKey(const std::wstring &keyPath, const std::wstring &backupFilePath)
{
    // Form a command for reg export
    std::wstring command = L"reg export \"" + keyPath + L"\" \"" + backupFilePath + L"\" /y";

    // Execute the command
    int result = _wsystem(command.c_str());

    if (result != 0) {
        throw std::runtime_error("Failed to backup registry key using reg export: " + std::to_string(result));
    }

    return true;
}
