#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabmanager.h"
#include "qtexteditsetting.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabmanager.h"
#include "qtexteditsetting.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a TabManager instance and pass the QTabWidget
    tabManager = new TabManager(ui->tabWidget);

    // // Set default text editor settings
    // QTextEditSettings textEditSettings;
    // textEditSettings.setFont(QFont("Arial", 15));

    // // Pass the text editor settings to the TabManager
    // tabManager->setTextEditSettings(textEditSettings);

    // Initialize the TabManager
    //tabManager->initializeTabBar();

    // Connect the Exit action to TabManager's exitApplication slot
    connect(ui->actionExit, &QAction::triggered, tabManager, &TabManager::exitApplication);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tabManager; // Release the memory of TabManager
}



void MainWindow::on_actionExit_triggered()
{
    statusBar()->showMessage("App will be killed in 3 seconds...", 5000);
    QTimer::singleShot(3000, this , SLOT(quitApp()));
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPast_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::quitApp()
{
    QApplication::quit();
}


