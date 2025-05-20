#include "mainwindow.h"
#include "ui_aboutprogram.h"
#include "ui_mainwindow.h"
#include "Application/additionalsettings.h"

#include <QMessageBox>
#include <QPropertyAnimation>
#include <QCoreApplication>
#include <QPushButton>
#include <QTimer>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , status()
    , sm()
    , gs()
    , as()
    , m_translator(nullptr)
{
    ui->setupUi(this);
    updateStatus();

    m_translator = new QTranslator(this);

    connect(ui->applyButton, &QPushButton::clicked, this, &MainWindow::onApplyButtonClicked);
    connect(ui->aboutProgramButton,  &QPushButton::clicked, this, []()
    {
        QDialog dialog;
        Ui::AboutProgram uiAboutProgram;
        uiAboutProgram.setupUi(&dialog);
        dialog.exec();
    });
    connect(ui->updateStatusButton, &QPushButton::clicked, this, &MainWindow::updateStatus);

    // Create languages menu
    QMenu *languagesMenu = new QMenu(this);
    QAction *actionEnglish = languagesMenu->addAction(tr("English"));
    QAction *actionRussian = languagesMenu->addAction(tr("Russian"));

    connect(actionEnglish, &QAction::triggered, [this]()
    {
        switchLanguage("en");
    });
    connect(actionRussian, &QAction::triggered, [this]()
            {
                switchLanguage("ru");
            });

    connect(ui->languagesPushButton, &QPushButton::clicked, [=]() {
        languagesMenu->exec(ui->languagesPushButton->mapToGlobal(QPoint(0, ui->languagesPushButton->height())));
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::applyAllSettings()
{
    try {
        // General settings
        applyGeneralSettings();

        // Additional settings
        applyAdditionalSettings();

        QMessageBox::information(this, tr("Success!"), tr("All settings applied!"));
        updateStatus();
        return true;
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Error"),
                              tr("Failed to apply settings: %1").arg(e.what()));
        return false;
    }
}

void MainWindow::applyGeneralSettings()
{
    // Windows Update
    if (ui->enableWindowsUpdateRadioButton->isChecked()) {
        gs.EnableWindowsUpdate();
    } else {
        gs.DisableWindowsUpdate();
    }

    // Windows Defender
    if (ui->enableWindowsDefenderRadioButton->isChecked()) {
        gs.EnableWindowsDefender();
    } else {
        gs.DisableWindowsDefender();
    }
}

void MainWindow::applyAdditionalSettings()
{
    AdditionalSettings as;

    // Page file settings
    applyPageFileSettings(as);

    // Other additional settings
    if (ui->setHighPerfomanceCheckBox->isChecked()) {
        as.SetHighPerformance();
    }

    if (ui->disableSleepModeCheckBox->isChecked()) {
        as.DisableSleepMode();
    }

    if (ui->disableEnhancedPointerPrecisionCheckBox->isChecked()) {
        as.DisableEnhancedPointerPrecision();
    }

    if (ui->disableCoreIsolationCheckBox->isChecked()) {
        as.DisableMemoryIntegrity();
    }

    if (ui->backUpCheckBox->isChecked()) {
        if (as.BackupAllSettings()) {
            QMessageBox::information(this, tr("Success!"),
                                     tr("A backup of the settings is saved in the path: 'C:\\RegistryBackups'!"));
        } else {
            throw std::runtime_error("Failed to create backup");
        }
    }
}

void MainWindow::applyPageFileSettings(AdditionalSettings& as)
{
    if (ui->pageFileComboBox->currentIndex() != 0) {
        std::wstring disk = (ui->diskComboBox->currentText()).toStdWString();


        DWORD minSizeMB = ui->pageFileComboBox->currentText().chopped(3).toULong();
        DWORD maxSizeMB = ui->pageFileComboBox->currentText().chopped(3).toULong();

        as.SetPageFileSize(disk, minSizeMB, maxSizeMB);
    }
}

void MainWindow::onApplyButtonClicked()
{
    QString originalText = ui->applyButton->text();

    // Changing the button text
    ui->applyButton->setText(tr("Applying."));
    ui->applyButton->setEnabled(false);
    QCoreApplication::processEvents(); // Forced interface update

    // Create animation timer
    QTimer* animationTimer = new QTimer(this); // Creating timer
    int dotCount = 1; // Initializing the dot counter
    connect(animationTimer, &QTimer::timeout, [this, &dotCount]()
    {
        dotCount = (dotCount % 3) + 1; // Cyclic change of dotCount between values 1, 2 and 3
        ui->applyButton->setText(tr("Applying") + QString(".").repeated(dotCount)); // Updating the button text
        QCoreApplication::processEvents(); // Forced interface update
    });

    animationTimer->start(300); // Update every 300ms

    // Perform the applying settings
    applyAllSettings();

    // Clean up animation
    animationTimer->stop();
    animationTimer->deleteLater();

    // Return to the original button state
    ui->applyButton->setText(originalText);
    ui->applyButton->setEnabled(true);
}

void MainWindow::updateStatus() {
    if (!gs.TamperProtectionIsEnable())
    {
        ui->enableWindowsDefenderRadioButton->setEnabled(1);
        ui->disableWindowsDefenderRadioButton->setEnabled(1);

        ui->tamperProtectionLabel->setHidden(1);
        ui->openProtectionSettingsButton->setHidden(1);
    }
    else
    {
        ui->enableWindowsDefenderRadioButton->setEnabled(0);
        ui->disableWindowsDefenderRadioButton->setEnabled(0);

        ui->tamperProtectionLabel->setHidden(0);
        ui->openProtectionSettingsButton->setHidden(0);
    }

    if (gs.WindowsUpdateIsEnable())
    {
        ui->enableWindowsUpdateRadioButton->setChecked(true);
    }
    else
    {
        ui->disableWindowsUpdateRadioButton->setChecked(true);
    }

    if (gs.WindowsDefenderIsEnable())
    {
        ui->enableWindowsDefenderRadioButton->setChecked(true);
    }
    else
    {
        ui->disableWindowsDefenderRadioButton->setChecked(true);
    }

    status.setLabelPixmap(gs.WindowsUpdateIsEnable(), ui->statusWindowsUpdateLabel);
    status.setLabelPixmap(gs.WindowsDefenderIsEnable(), ui->statusWindowsDefenderLabel);

    status.fillComboBox(ui->diskComboBox);
}

void MainWindow::switchLanguage(const QString &language)
{
    if (language == "ru")
    {
        if (m_translator->load(":/translations/ru.qm"))
        {
            qApp->installTranslator(m_translator);
        }
        else
        {
            qWarning() << "Failed to load Russian translation!";
        }
    }
    else
    {
        qApp->removeTranslator(m_translator);
    }

    ui->retranslateUi(this);
}
