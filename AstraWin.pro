QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Application/Managers/powersettingsmanager.cpp \
    Application/Managers/registrymanager.cpp \
    Application/Managers/servicemanager.cpp \
    Application/Status/status.cpp \
    Application/additionalsettings.cpp \
    Application/cleaner.cpp \
    Application/generalsettings.cpp \
    aboutprogram.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Application/Managers/powersettingsmanager.h \
    Application/Managers/registrymanager.h \
    Application/Managers/servicemanager.h \
    Application/Status/status.h \
    Application/additionalsettings.h \
    Application/cleaner.h \
    Application/generalsettings.h \
    aboutprogram.h \
    mainwindow.h

FORMS += \
    aboutprogram.ui \
    mainwindow.ui

LIBS += -lpowrprof -lole32

TRANSLATIONS += translations/ru.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    style/darkstyle.qrc \
    translations.qrc
