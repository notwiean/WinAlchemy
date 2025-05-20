/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *enableWindowsUpdateRadioButton;
    QRadioButton *disableWindowsUpdateRadioButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *statusWindowsUpdateLabel;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *enableWindowsDefenderRadioButton;
    QRadioButton *disableWindowsDefenderRadioButton;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLabel *statusWindowsDefenderLabel;
    QLabel *tamperProtectionLabel;
    QPushButton *openProtectionSettingsButton;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *diskComboBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QComboBox *pageFileComboBox;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout;
    QCheckBox *setHighPerfomanceCheckBox;
    QCheckBox *disableSleepModeCheckBox;
    QCheckBox *disableEnhancedPointerPrecisionCheckBox;
    QCheckBox *disableCoreIsolationCheckBox;
    QCheckBox *backUpCheckBox;
    QVBoxLayout *verticalLayout_9;
    QPushButton *applyButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *aboutProgramButton;
    QPushButton *updateStatusButton;
    QPushButton *languagesPushButton;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_8;
    QLabel *label_7;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(422, 449);
        MainWindow->setMinimumSize(QSize(287, 449));
        MainWindow->setMaximumSize(QSize(1000, 1000));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 401, 433));
        verticalLayout_6 = new QVBoxLayout(layoutWidget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(layoutWidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        enableWindowsUpdateRadioButton = new QRadioButton(groupBox);
        enableWindowsUpdateRadioButton->setObjectName("enableWindowsUpdateRadioButton");
        enableWindowsUpdateRadioButton->setChecked(true);

        verticalLayout_3->addWidget(enableWindowsUpdateRadioButton);

        disableWindowsUpdateRadioButton = new QRadioButton(groupBox);
        disableWindowsUpdateRadioButton->setObjectName("disableWindowsUpdateRadioButton");
        disableWindowsUpdateRadioButton->setChecked(false);

        verticalLayout_3->addWidget(disableWindowsUpdateRadioButton);


        horizontalLayout_2->addLayout(verticalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        label_3->setFont(font);

        horizontalLayout_5->addWidget(label_3);

        statusWindowsUpdateLabel = new QLabel(groupBox);
        statusWindowsUpdateLabel->setObjectName("statusWindowsUpdateLabel");
        statusWindowsUpdateLabel->setMinimumSize(QSize(0, 0));
        statusWindowsUpdateLabel->setMaximumSize(QSize(31, 31));
        statusWindowsUpdateLabel->setAcceptDrops(false);
        statusWindowsUpdateLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/on.png")));
        statusWindowsUpdateLabel->setScaledContents(true);
        statusWindowsUpdateLabel->setWordWrap(false);
        statusWindowsUpdateLabel->setOpenExternalLinks(false);

        horizontalLayout_5->addWidget(statusWindowsUpdateLabel);


        horizontalLayout_2->addLayout(horizontalLayout_5);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);


        horizontalLayout_3->addWidget(groupBox);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        enableWindowsDefenderRadioButton = new QRadioButton(groupBox_2);
        enableWindowsDefenderRadioButton->setObjectName("enableWindowsDefenderRadioButton");
        enableWindowsDefenderRadioButton->setChecked(true);

        verticalLayout_4->addWidget(enableWindowsDefenderRadioButton);

        disableWindowsDefenderRadioButton = new QRadioButton(groupBox_2);
        disableWindowsDefenderRadioButton->setObjectName("disableWindowsDefenderRadioButton");
        disableWindowsDefenderRadioButton->setChecked(false);

        verticalLayout_4->addWidget(disableWindowsDefenderRadioButton);


        horizontalLayout_9->addLayout(verticalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setFont(font);

        horizontalLayout_6->addWidget(label_4);

        statusWindowsDefenderLabel = new QLabel(groupBox_2);
        statusWindowsDefenderLabel->setObjectName("statusWindowsDefenderLabel");
        statusWindowsDefenderLabel->setMinimumSize(QSize(0, 0));
        statusWindowsDefenderLabel->setMaximumSize(QSize(31, 31));
        statusWindowsDefenderLabel->setAcceptDrops(false);
        statusWindowsDefenderLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/on.png")));
        statusWindowsDefenderLabel->setScaledContents(true);

        horizontalLayout_6->addWidget(statusWindowsDefenderLabel);


        horizontalLayout_9->addLayout(horizontalLayout_6);


        gridLayout_2->addLayout(horizontalLayout_9, 0, 1, 1, 1);

        tamperProtectionLabel = new QLabel(groupBox_2);
        tamperProtectionLabel->setObjectName("tamperProtectionLabel");
        tamperProtectionLabel->setWordWrap(true);

        gridLayout_2->addWidget(tamperProtectionLabel, 1, 1, 1, 1);

        openProtectionSettingsButton = new QPushButton(groupBox_2);
        openProtectionSettingsButton->setObjectName("openProtectionSettingsButton");

        gridLayout_2->addWidget(openProtectionSettingsButton, 2, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName("gridLayout_4");
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setObjectName("gridLayout_5");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        diskComboBox = new QComboBox(groupBox_3);
        diskComboBox->setObjectName("diskComboBox");
        diskComboBox->setMinimumSize(QSize(60, 24));
        diskComboBox->setMaximumSize(QSize(60, 24));

        horizontalLayout->addWidget(diskComboBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label = new QLabel(groupBox_3);
        label->setObjectName("label");

        horizontalLayout_8->addWidget(label);

        pageFileComboBox = new QComboBox(groupBox_3);
        pageFileComboBox->addItem(QString());
        pageFileComboBox->addItem(QString());
        pageFileComboBox->addItem(QString());
        pageFileComboBox->addItem(QString());
        pageFileComboBox->addItem(QString());
        pageFileComboBox->addItem(QString());
        pageFileComboBox->addItem(QString());
        pageFileComboBox->addItem(QString());
        pageFileComboBox->addItem(QString());
        pageFileComboBox->setObjectName("pageFileComboBox");
        pageFileComboBox->setMinimumSize(QSize(100, 24));
        pageFileComboBox->setMaximumSize(QSize(100, 24));

        horizontalLayout_8->addWidget(pageFileComboBox);


        verticalLayout_2->addLayout(horizontalLayout_8);


        gridLayout_5->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 0, 1, 1, 1);

        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_6 = new QGridLayout(groupBox_4);
        gridLayout_6->setObjectName("gridLayout_6");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        setHighPerfomanceCheckBox = new QCheckBox(groupBox_4);
        setHighPerfomanceCheckBox->setObjectName("setHighPerfomanceCheckBox");
        setHighPerfomanceCheckBox->setChecked(false);

        verticalLayout->addWidget(setHighPerfomanceCheckBox);

        disableSleepModeCheckBox = new QCheckBox(groupBox_4);
        disableSleepModeCheckBox->setObjectName("disableSleepModeCheckBox");
        disableSleepModeCheckBox->setChecked(false);

        verticalLayout->addWidget(disableSleepModeCheckBox);

        disableEnhancedPointerPrecisionCheckBox = new QCheckBox(groupBox_4);
        disableEnhancedPointerPrecisionCheckBox->setObjectName("disableEnhancedPointerPrecisionCheckBox");
        disableEnhancedPointerPrecisionCheckBox->setEnabled(true);
        disableEnhancedPointerPrecisionCheckBox->setChecked(false);

        verticalLayout->addWidget(disableEnhancedPointerPrecisionCheckBox);

        disableCoreIsolationCheckBox = new QCheckBox(groupBox_4);
        disableCoreIsolationCheckBox->setObjectName("disableCoreIsolationCheckBox");
        disableCoreIsolationCheckBox->setChecked(false);

        verticalLayout->addWidget(disableCoreIsolationCheckBox);

        backUpCheckBox = new QCheckBox(groupBox_4);
        backUpCheckBox->setObjectName("backUpCheckBox");
        QFont font1;
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        backUpCheckBox->setFont(font1);
        backUpCheckBox->setChecked(false);

        verticalLayout->addWidget(backUpCheckBox);


        gridLayout_6->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 1, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_6->addWidget(tabWidget);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        applyButton = new QPushButton(layoutWidget);
        applyButton->setObjectName("applyButton");
        QFont font2;
        font2.setBold(true);
        font2.setStrikeOut(false);
        applyButton->setFont(font2);

        verticalLayout_9->addWidget(applyButton);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        aboutProgramButton = new QPushButton(layoutWidget);
        aboutProgramButton->setObjectName("aboutProgramButton");

        horizontalLayout_4->addWidget(aboutProgramButton);

        updateStatusButton = new QPushButton(layoutWidget);
        updateStatusButton->setObjectName("updateStatusButton");

        horizontalLayout_4->addWidget(updateStatusButton);

        languagesPushButton = new QPushButton(layoutWidget);
        languagesPushButton->setObjectName("languagesPushButton");
        languagesPushButton->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

        horizontalLayout_4->addWidget(languagesPushButton);


        verticalLayout_9->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName("label_8");
        label_8->setMaximumSize(QSize(21, 21));
        label_8->setMouseTracking(false);
        label_8->setTabletTracking(false);
        label_8->setAcceptDrops(false);
        label_8->setAutoFillBackground(false);
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/images/dollar.png")));
        label_8->setScaledContents(true);
        label_8->setWordWrap(false);
        label_8->setOpenExternalLinks(false);

        horizontalLayout_7->addWidget(label_8);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");
        label_7->setOpenExternalLinks(true);

        horizontalLayout_7->addWidget(label_7);


        verticalLayout_9->addLayout(horizontalLayout_7);


        verticalLayout_6->addLayout(verticalLayout_9);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        pageFileComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "WinAlchemy", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Windows Update", nullptr));
        enableWindowsUpdateRadioButton->setText(QCoreApplication::translate("MainWindow", "Enable", nullptr));
        disableWindowsUpdateRadioButton->setText(QCoreApplication::translate("MainWindow", "Disable", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Lock status:", nullptr));
        statusWindowsUpdateLabel->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Windows Defender", nullptr));
        enableWindowsDefenderRadioButton->setText(QCoreApplication::translate("MainWindow", "Enable", nullptr));
        disableWindowsDefenderRadioButton->setText(QCoreApplication::translate("MainWindow", "Disable", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Lock status:", nullptr));
        statusWindowsDefenderLabel->setText(QString());
        tamperProtectionLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Before using you must manually disable the \342\200\234Tamper Protection\342\200\235!</p></body></html>", nullptr));
        openProtectionSettingsButton->setText(QCoreApplication::translate("MainWindow", "Open protection settings", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "General", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Virtual memory", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Select disk:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Set page file :", nullptr));
        pageFileComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Don't change", nullptr));
        pageFileComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "0 MB", nullptr));
        pageFileComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "512 MB", nullptr));
        pageFileComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "1024 MB", nullptr));
        pageFileComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "2048 MB", nullptr));
        pageFileComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "4096 MB", nullptr));
        pageFileComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "8192 MB", nullptr));
        pageFileComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "16384 MB", nullptr));
        pageFileComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "32768 MB", nullptr));

        pageFileComboBox->setCurrentText(QCoreApplication::translate("MainWindow", "Don't change", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Other options", nullptr));
        setHighPerfomanceCheckBox->setText(QCoreApplication::translate("MainWindow", "Set High Performance Mode", nullptr));
        disableSleepModeCheckBox->setText(QCoreApplication::translate("MainWindow", "Disable Sleep Mode", nullptr));
        disableEnhancedPointerPrecisionCheckBox->setText(QCoreApplication::translate("MainWindow", "Disable Enhanced Pointer Precision", nullptr));
        disableCoreIsolationCheckBox->setText(QCoreApplication::translate("MainWindow", "Disable Core Isolation", nullptr));
        backUpCheckBox->setText(QCoreApplication::translate("MainWindow", "Back up all settings", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Additional options", nullptr));
        applyButton->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        aboutProgramButton->setText(QCoreApplication::translate("MainWindow", "About program", nullptr));
        updateStatusButton->setText(QCoreApplication::translate("MainWindow", "Update status", nullptr));
        languagesPushButton->setText(QCoreApplication::translate("MainWindow", "Languages", nullptr));
        label_8->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "<a href='https://adult.noodlemagazine.com/watch/-209155965_456245642'>Thanks to the author :)</a>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
