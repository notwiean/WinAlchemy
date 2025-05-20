#ifndef CLEANER_H
#define CLEANER_H

#include <string>

class cleaner
{
public:
    cleaner();

    bool ClearWindowsTempDirectory;
private:
    // Function for clearing all files in the specified directory
    bool ClearFilesInDirectory(const std::wstring& directoryPath);
};

#endif // CLEANER_H
