#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QTabBar>
#include <QLineEdit>
#include <QMouseEvent>
#include <QTextBrowser>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QGuiApplication>
#include <QTextEdit>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), currentTextEdit(nullptr)
{
    ui->setupUi(this);

    // Apply a style sheet to the QTabWidget to set the margin
    ui->tabWidget->setStyleSheet("QTabWidget::pane { margin: 5px; }");

    // Call the function to create and connect the close button
    initializeCloseButton();

    ui->tabWidget->installEventFilter(this); // Install event filter on tabWidget
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->tabWidget && event->type() == QEvent::MouseButtonDblClick) {
        createNewTab(); // Create a new tab on double-click event
        return true; // Event handled
    }
    return false; // Event not handled
}

void MainWindow::initializeCloseButton() {
    // Create a close button for the default tab
    QPushButton *closeButton = new QPushButton("X");
    closeButton->setFixedSize(16, 16); // Set a fixed size for the close button

    // Set the background color of the close button to a red color from the Qt palette
    QString redColor = QApplication::palette().color(QPalette::Button).name();
    closeButton->setStyleSheet("background-color: " + redColor + ";");

    // Set the close button within the default tab's title area
    ui->tabWidget->tabBar()->setTabButton(ui->tabWidget->currentIndex(), QTabBar::RightSide, closeButton);

    int tabIndex = ui->tabWidget->currentIndex();

    // Connect the close button's clicked signal to close the default tab
    connect(closeButton, &QPushButton::clicked, this, [=]() {
        closeTab(tabIndex);
    });
}

void MainWindow::closeTab(int index)
{
    int totalTabs = ui->tabWidget->count();
    if (totalTabs == 1) {
        // Do nothing when there's only one tab left
        return;
    }

    QWidget* tabItem = ui->tabWidget->widget(index);
    if (tabItem) {
        QWidget* textEditWidget = ui->tabWidget->widget(index)->findChild<QTextEdit *>();
        if (textEditWidget) {
            delete textEditWidget; // Delete the text editor widget
        }

        ui->tabWidget->removeTab(index);
        delete tabItem; // Delete the tab
    }
}

void MainWindow::createNewTab() {
    // Create a new QTextEdit for the tab content
    QTextEdit *textEdit = new QTextEdit;
    qDebug() << "Hello from ins no" << textEdit;

    // Set the current text edit to the newly created one
    currentTextEdit = textEdit;

    // Set properties for the new QTextEdit
    setTextEditProperties(textEdit);

    // Create a close button for the tab
    QPushButton *closeButton = new QPushButton("X");
    closeButton->setFixedSize(16, 16); // Set a fixed size for the close button

    // Set the background color of the close button to a red color from the Qt palette
    QString redColor = QApplication::palette().color(QPalette::Button).name();
    closeButton->setStyleSheet("background-color: " + redColor + ";");

    // Set the close button within the tab's title area
    int tabIndex = ui->tabWidget->addTab(textEdit, "New Tab");
    ui->tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);
    ui->tabWidget->setCurrentIndex(tabIndex); // Set the current tab to the newly created one

    // Connect the close button's clicked signal to a slot that closes the corresponding tab
    connect(closeButton, &QPushButton::clicked, this, [=]() {
        // Check for the total number of tabs
        int totalTabs = ui->tabWidget->count();
        if (totalTabs == 1) {
            // Do nothing when there's only one tab left
            return;
        }

        int closeIndex = ui->tabWidget->indexOf(textEdit);
        if (closeIndex != -1) {
            ui->tabWidget->removeTab(closeIndex);
            delete textEdit;
        }
    });
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("XML Files (*.xml);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        QString xmlContent = in.readAll();
        file.close();

        // Create a QTextEdit for the tab content
        QTextEdit *textEdit = new QTextEdit;

        // Set properties for the new QTextEdit
        setTextEditProperties(textEdit);
        textEdit->setText(xmlContent);

        // Create a close button for the tab (similar to createNewTab() function)
        QPushButton *closeButton = new QPushButton("X");
        closeButton->setFixedSize(16, 16);
        QString redColor = QApplication::palette().color(QPalette::Button).name();
        closeButton->setStyleSheet("background-color: " + redColor + ";");

        // Add the textEdit and closeButton to the tabWidget
        int tabIndex = ui->tabWidget->addTab(textEdit, QFileInfo(fileName).fileName());
        ui->tabWidget->setCurrentIndex(tabIndex);

        // Set the close button within the tab's title area
        ui->tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);

        // Connect close button's clicked signal to a slot that closes the corresponding tab
        connect(closeButton, &QPushButton::clicked, this, [=]() {
            // Check for the total no of tabs
            int totalTabs = ui->tabWidget->count();
            if (totalTabs == 1) {
                // Do nothing when there's only one tab left
                return;
            }

            int closeIndex = ui->tabWidget->indexOf(textEdit);
            if (closeIndex != -1) {
                ui->tabWidget->removeTab(closeIndex);
                delete textEdit;
            }
        });
    }
}

// Connect the undo, redo, copy, and paste actions to the respective QTextEdit slots
void MainWindow::connectTextEditActions(QTextEdit* textEdit) {
    qDebug() << "Connect the signals for ins" << textEdit;
    connect(ui->actionCopy, &QAction::triggered, textEdit, &QTextEdit::copy);
    connect(ui->actionCut, &QAction::triggered, textEdit, &QTextEdit::cut);
    connect(ui->actionPast, &QAction::triggered, textEdit, &QTextEdit::paste);
    connect(ui->actionUndo, &QAction::triggered, textEdit, &QTextEdit::undo);
    connect(ui->actionRedo, &QAction::triggered, textEdit, &QTextEdit::redo);
}

void MainWindow::setTextEditProperties(QTextEdit* textEdit) {
    textEdit->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu); // Enable context menu
    textEdit->setUndoRedoEnabled(true); // Enable undo and redo
    textEdit->setAcceptRichText(true); // Enable rich text
    textEdit->setReadOnly(false); // Set it to editable
    qDebug() << "Set the Properties for ins" << textEdit;

    // Connect signals for actions to the respective slots in the QTextEdit
    connectTextEditActions(textEdit); // Connect actions to this specific QTextEdit

}

void MainWindow::on_actionExit_triggered()
{
    statusBar()->showMessage("App will be killed in 3 seconds...", 3000);
    QTimer::singleShot(3000, this , SLOT(quitApp()));
}

// In the implementation file (mainwindow.cpp), define the quitApp slot
void MainWindow::quitApp() {
    QApplication::quit(); // Terminates the application
}

void MainWindow::on_actionCopy_triggered() {
    // Check if there's a selected text edit
    if (ui->tabWidget->currentWidget()) {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(ui->tabWidget->currentWidget());
        if (textEdit) {
            QClipboard *clipboard = QGuiApplication::clipboard();
            clipboard->setText(textEdit->textCursor().selectedText());
        }
    }
}

void MainWindow::on_actionCut_triggered() {
    // Check if there's a selected text edit
    if (ui->tabWidget->currentWidget()) {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(ui->tabWidget->currentWidget());
        if (textEdit) {
            QClipboard *clipboard = QGuiApplication::clipboard();
            clipboard->setText(textEdit->textCursor().selectedText());
            textEdit->textCursor().removeSelectedText();
        }
    }
}

void MainWindow::on_actionPast_triggered() {
    // Check if there's a selected text edit
    if (ui->tabWidget->currentWidget()) {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(ui->tabWidget->currentWidget());
        if (textEdit) {
            QClipboard *clipboard = QGuiApplication::clipboard();
            textEdit->insertPlainText(clipboard->text());
        }
    }
}

void MainWindow::on_actionUndo_triggered() {
    if (currentTextEdit) {
        currentTextEdit->undo();
    } else {
        ui->textEdit->undo();
    }
}

void MainWindow::on_actionRedo_triggered() {
    if (currentTextEdit) {
        currentTextEdit->redo();
    } else {
        ui->textEdit->redo();
    }
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}



