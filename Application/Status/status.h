#ifndef STATUS_H
#define STATUS_H

#include <QComboBox>
#include <QLabel>
#include <vector>
#include <string>

class Status
{
public:
    Status();

    // Function for setting label pixmap
    void setLabelPixmap(bool isActive, QLabel* label);
    // Function for filling a combobox
    void fillComboBox(QComboBox* comboBox);

private:
    // Function to get all drive letters
    std::vector<std::string> GetDriveLetters();
};

#endif // STATUS_H
