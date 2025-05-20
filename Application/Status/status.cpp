#include "status.h"

#include <windows.h>

Status::Status() {}

void Status::setLabelPixmap(bool isActive, QLabel *label)
{
    if (label == nullptr)
    {
        qDebug() << "QLabel is nullptr!";
    }

    if (isActive)
    {
        // Upload a png for disable lock status
        QPixmap pixmap(":/images/off.png");
        if (pixmap.isNull())
        {
            qDebug() << "Failed to upload off.png!";
            return;
        }
        if (label)
        {
            label->setPixmap(pixmap);
        }
    }
    else
    {
        // Upload a png for enable lock status
        QPixmap pixmap(":/images/on.png");
        if (pixmap.isNull())
        {
            qDebug() << "Failed to upload on.png!";
            return;
        }
        if (label)
        {
            label->setPixmap(pixmap);
        }
    }
}

void Status::fillComboBox(QComboBox *comboBox)
{
    Status s;
    const std::vector<std::string> items = s.GetDriveLetters();

    comboBox->clear();
    for (const auto& item : items) {
        comboBox->addItem(QString::fromStdString(item));
    }
}

// Function to get all drive letters
std::vector<std::string> Status::GetDriveLetters()
{
    std::vector<std::string> drives;

    // Get the bitmask of all available disks
    DWORD drivesMask = GetLogicalDrives();

    // Go through all possible disks (from A to Z)
    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        // Check if the corresponding bit is set
        if (drivesMask & 1) {
            // Add a drive letter to the vector
            drives.push_back(std::string(1, drive));
        }
        // Slide the mask to the right to check the next disk
        drivesMask >>= 1;
    }

    return drives;
}
