#include "mainwindow.h"

#include <QApplication>
#include <QStyle>
#include <QFile>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // Загрузка файла стиля
    QFile styleSheetFile(":/qdarkstyle/dark/darkstyle.qss");
    if (!styleSheetFile.exists()) {
        qWarning("Unable to set stylesheet, file not found");
    } else {
        if (styleSheetFile.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream ts(&styleSheetFile);
            QString styleSheet = ts.readAll();
            a.setStyleSheet(styleSheet);
            styleSheetFile.close();
        } else {
            qWarning("Unable to open stylesheet file");
        }
    }

    MainWindow w;
    w.show();
    return a.exec();
}
