/********************************************************************************
** Form generated from reading UI file 'aboutprogram.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTPROGRAM_H
#define UI_ABOUTPROGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutProgram
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_15;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLabel *label_10;

    void setupUi(QDialog *AboutProgram)
    {
        if (AboutProgram->objectName().isEmpty())
            AboutProgram->setObjectName("AboutProgram");
        AboutProgram->resize(528, 350);
        AboutProgram->setMinimumSize(QSize(528, 350));
        AboutProgram->setMaximumSize(QSize(528, 350));
        layoutWidget = new QWidget(AboutProgram);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 507, 331));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName("label_15");
        label_15->setMaximumSize(QSize(31, 31));
        label_15->setPixmap(QPixmap(QString::fromUtf8(":/images/whitelogo.png")));
        label_15->setScaledContents(true);

        horizontalLayout->addWidget(label_15);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setMouseTracking(true);
        label->setTabletTracking(false);
        label->setAcceptDrops(false);
        label->setScaledContents(false);
        label->setWordWrap(false);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setWordWrap(true);
        label_5->setOpenExternalLinks(false);

        verticalLayout->addWidget(label_5);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_8->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_8);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setMinimumSize(QSize(31, 31));
        label_12->setMaximumSize(QSize(31, 31));
        label_12->setLineWidth(4);
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/images/author.png")));
        label_12->setScaledContents(true);

        horizontalLayout_7->addWidget(label_12);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_4->addWidget(label_6);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");

        horizontalLayout_4->addWidget(label_11);


        horizontalLayout_7->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setMinimumSize(QSize(31, 31));
        label_14->setMaximumSize(QSize(31, 31));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/images/donate.png")));
        label_14->setScaledContents(true);
        label_14->setWordWrap(false);

        horizontalLayout_6->addWidget(label_14);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_3->addWidget(label_7);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setOpenExternalLinks(true);
        label_9->setTextInteractionFlags(Qt::TextInteractionFlag::LinksAccessibleByMouse);

        horizontalLayout_3->addWidget(label_9);


        horizontalLayout_6->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName("label_13");
        label_13->setMinimumSize(QSize(31, 31));
        label_13->setMaximumSize(QSize(31, 31));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/images/gmail.png")));
        label_13->setScaledContents(true);

        horizontalLayout_5->addWidget(label_13);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_2->addWidget(label_8);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");

        horizontalLayout_2->addWidget(label_10);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_5);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);


        retranslateUi(AboutProgram);

        QMetaObject::connectSlotsByName(AboutProgram);
    } // setupUi

    void retranslateUi(QDialog *AboutProgram)
    {
        AboutProgram->setWindowTitle(QCoreApplication::translate("AboutProgram", "About", nullptr));
        groupBox->setTitle(QString());
        label_15->setText(QString());
        label->setText(QCoreApplication::translate("AboutProgram", "<html><head/><body><p>WinAlchemy v0.1</p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("AboutProgram", "This tool is designed to easily disable Windows Updates and Windows Defender, clean up your system, customize your swap file and a number of other settings.", nullptr));
        label_3->setText(QCoreApplication::translate("AboutProgram", "License: MIT (opensource.org/licenses/MIT) ", nullptr));
        label_4->setText(QCoreApplication::translate("AboutProgram", "Source code: github.com/notwiean/winalchemy  ", nullptr));
        label_2->setText(QCoreApplication::translate("AboutProgram", "<html><head/><body><p>\302\251 2025, @notwiean</p></body></html>", nullptr));
        groupBox_2->setTitle(QString());
        label_12->setText(QString());
        label_6->setText(QCoreApplication::translate("AboutProgram", "Author:", nullptr));
        label_11->setText(QCoreApplication::translate("AboutProgram", "@notwiean", nullptr));
        label_14->setText(QString());
        label_7->setText(QCoreApplication::translate("AboutProgram", "Donate: ", nullptr));
        label_9->setText(QCoreApplication::translate("AboutProgram", "<a href='https://adult.noodlemagazine.com/watch/-209155965_456245642'>DonationAlerts</a>", nullptr));
        label_13->setText(QString());
        label_8->setText(QCoreApplication::translate("AboutProgram", "Gmail:", nullptr));
        label_10->setText(QCoreApplication::translate("AboutProgram", "notwiean@gmail.com", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutProgram: public Ui_AboutProgram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTPROGRAM_H
