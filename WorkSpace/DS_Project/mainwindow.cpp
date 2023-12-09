#include "./ui_mainwindow.h"
#include "customtabwidget.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QTabBar>
#include <QLineEdit>
#include <QMouseEvent>
#include <QTextBrowser>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), tabCounter(2) // Initialize the tab counter to 2
{
    ui->setupUi(this);
    ui->tabWidget->installEventFilter(this); // Install event filter on tabWidget
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::createNewTab);
}

void MainWindow::createNewTab()
{
    // Create a new QTextEdit for the tab content
    QTextEdit *textEdit = new QTextEdit;

    // // Create a close button for the tab
    // QPushButton *closeButton = new QPushButton("x");
    // closeButton->setFixedSize(20, 20); // Set a fixed size for the close button

    // Set the close button within the tab's title area
    int tabIndex = ui->tabWidget->addTab(textEdit, "new " + QString::number(tabCounter++));
    //ui->tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);
    ui->tabWidget->setCurrentIndex(tabIndex); // Set the current tab to the newly created one

    // // Connect the close button's clicked signal to a slot that closes the corresponding tab
    // connect(closeButton, &QPushButton::clicked, [=]() {
    //     int closeIndex = ui->tabWidget->indexOf(textEdit);
    //     if (closeIndex != -1) {
    //         delete ui->tabWidget->widget(closeIndex);

    //         // Check if all tabs are closed
    //         if (ui->tabWidget->count() == 1) {
    //             tabCounter = 2; // Reset the tab counter to 2
    //         }
    //     }
    // });
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->tabWidget && event->type() == QEvent::MouseButtonDblClick) {
        createNewTab(); // Create a new tab on double-click event
        return true; // Event handled
    }
    return false; // Event not handled
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

MainWindow::~MainWindow()
{
    delete ui;
}
