#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Application/Status/status.h"
#include "Application/Managers/servicemanager.h"
#include "Application/additionalsettings.h"
#include "Application/generalsettings.h"

#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Status status;
    ServiceManager sm;
    GeneralSettings gs;
    AdditionalSettings as;
    QTranslator *m_translator;

    bool applyAllSettings();
    void applyGeneralSettings();
    void applyAdditionalSettings();
    void applyPageFileSettings(AdditionalSettings& as);

    void onApplyButtonClicked();

    void updateStatus();
    void retranslateUi();
    void switchLanguage(const QString &language);
};

#endif // MAINWINDOW_H
