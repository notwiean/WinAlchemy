#include "cleaner.h"

#include <filesystem>
#include <windows.h>
#include <qDebug>

cleaner::cleaner() {}

// Function for clearing all files in the specified directory
bool cleaner::ClearFilesInDirectory(const std::wstring &directoryPath)
{
    // Convert path to std::filesystem::path
    std::filesystem::path targetDir(directoryPath);

    // Make sure the path ends with backlash
    if (!targetDir.empty() && targetDir.wstring().back() != L'\\')
    {
        targetDir += L'\\';
    }

    // Display the message that cleaning has started
    qDebug() << L"Cleaning files in: " << targetDir.wstring();

    try
    {
        // Check the directory exists
        if (!std::filesystem::exists(targetDir))
        {
            qDebug() << L"Directory does not exist: " << targetDir.wstring();
            return false;
        }

        // Iterate through all entries in the directory
        for (const auto& entry : std::filesystem::directory_iterator(targetDir))
        {
            try
            {
                // Delete the file or directory
                std::filesystem::remove_all(entry.path());
                qDebug() << L"Deleted: " << entry.path().wstring();
            }
            catch(const std::filesystem::filesystem_error& ex)
            {
                qDebug() << L"Failed to delete: " << entry.path().wstring() << L". Error: " << ex.what();
            }
        }

        qDebug() << L"Files cleared successfully in: " << targetDir.wstring();
        return true;
    }
    catch (const std::exception& ex)
    {
        qDebug() << L"Error during cleanup: " << ex.what();
        return false;
    }
}
