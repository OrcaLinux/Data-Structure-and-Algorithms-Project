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
#include <QtXml/QDomDocument>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QBuffer>
//#include <Qsci/qsciscintilla.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), currentTextEdit(nullptr)
{
    ui->setupUi(this);

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

    // Set properties for the new QTextEdit
    setTextEditProperties(textEdit);

    // Create a close button for the tab
    QPushButton *closeButton = new QPushButton("X");
    closeButton->setFixedSize(16, 16); // Set a fixed size for the close button

    // Set the background color of the close button to a red color from the Qt palette
    QString redColor = QApplication::palette().color(QPalette::Button).name();
    closeButton->setStyleSheet("background-color: " + redColor + ";");

    // Create four push buttons for the tab
    QPushButton *button1 = new QPushButton("Forman the file");
    QPushButton *button2 = new QPushButton("Correct the errors");
    QPushButton *button3 = new QPushButton("Convert to json");
    QPushButton *button4 = new QPushButton("Compressed the file");

    // Create a layout for the buttons and add them to it
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);
    buttonLayout->addWidget(button4);

    // Create a layout for the entire tab's content
    QVBoxLayout *tabLayout = new QVBoxLayout;
    tabLayout->addWidget(textEdit);
    tabLayout->addLayout(buttonLayout); // Add the button layout to the tab layout

    // Create a widget to hold the layout
    QWidget *tabWidget = new QWidget;
    tabWidget->setLayout(tabLayout);

    // Set the tab widget as the content for the new tab
    int tabIndex = ui->tabWidget->addTab(tabWidget, "New Tab");
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

        int closeIndex = ui->tabWidget->indexOf(tabWidget);
        if (closeIndex != -1) {
            ui->tabWidget->removeTab(closeIndex);
            delete tabWidget;
        }
    });

    // Connect button1's clicked signal to handleFormatTheFileRequest
    connect(button1, &QPushButton::clicked, this, [=](){
        handleFormatTheFileRequest();
    });
}

void MainWindow::on_actionOpen_triggered()
{
    // Open a file dialog to select a file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("XML Files (*.xml);;All Files (*)"));
    if (!fileName.isEmpty()) {
        // Read the contents of the selected file
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();

        // Create a QTextEdit widget to display file content
        QTextEdit *textEdit = new QTextEdit;
        setTextEditProperties(textEdit);
        textEdit->setText(fileContent);

        // Create a close button for the tab
        QPushButton *closeButton = new QPushButton("X");
        closeButton->setFixedSize(16, 16);
        QString redColor = QApplication::palette().color(QPalette::Button).name();
        closeButton->setStyleSheet("background-color: " + redColor + ";");

        // Create buttons for the tab
        QPushButton *button1 = new QPushButton("Forman the file");
        QPushButton *button2 = new QPushButton("Correct the errors");
        QPushButton *button3 = new QPushButton("Convert to json");
        QPushButton *button4 = new QPushButton("Compressed the file");

        // Layout setup for buttons
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(button1);
        buttonLayout->addWidget(button2);
        buttonLayout->addWidget(button3);
        buttonLayout->addWidget(button4);

        // Main layout for the tab's content
        QVBoxLayout *tabLayout = new QVBoxLayout;
        tabLayout->addWidget(textEdit);
        tabLayout->addLayout(buttonLayout);

        // Create a widget to hold the layout
        QWidget *tabWidget = new QWidget;
        tabWidget->setLayout(tabLayout);

        // Add the new tab with the file name as the tab title
        int tabIndex = ui->tabWidget->addTab(tabWidget, QFileInfo(fileName).fileName());
        ui->tabWidget->setCurrentIndex(tabIndex);
        ui->tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);

        // Connect the close button's clicked signal to close the default tab
        connect(closeButton, &QPushButton::clicked, this, [=]() {
            closeTab(tabIndex);
        });

        // Connect close button's clicked signal to a slot that closes the corresponding tab
        // Pass file type information to the function for processing
        connect(button1, &QPushButton::clicked, this, [=](){
            handleFormatTheFileRequest(fileName, textEdit);
        });

    }
}

void MainWindow::setTextEditProperties(QTextEdit* textEdit) {
    textEdit->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu); // Enable context menu
    textEdit->setUndoRedoEnabled(true); // Enable undo and redo
    textEdit->setAcceptRichText(true); // Enable rich text
    textEdit->setReadOnly(false); // Set it to editable

    // Set the current text edit to the newly created one
    currentTextEdit = textEdit;
}

/********************************************< Button Actions ********************************************/
void MainWindow::handleFormatTheFileRequest(const QString& fileName, QTextEdit* textEdit) {
    // Extract the file extension to determine the file type
    QString fileType = QFileInfo(fileName).suffix().toLower();

    if (textEdit) {
        QString fileContent = textEdit->toPlainText();

        if (!fileContent.isEmpty()) {
            // Check if the file type is XML
            if (fileType == "xml") {
                // Attempt to parse the XML content
                QDomDocument document;
                QString errorMsg;
                int errorLine, errorColumn;

                if (!document.setContent(fileContent, true, &errorMsg, &errorLine, &errorColumn)) {
                    // Display error message for XML syntax errors
                    QMessageBox::critical(this, tr("XML Error"),
                                          tr("XML Syntax Error at line %1, column %2: %3")
                                              .arg(errorLine).arg(errorColumn).arg(errorMsg));
                    return;
                }

                // Format the XML content and update the QTextEdit
                QString indentedXml = formatXml(fileContent);
                textEdit->clear();
                // After setting the formatted XML content in handleFormatTheFileRequest
                textEdit->setPlainText(indentedXml);
            } else {
                // Handle other file types or show a message (not XML)
                QMessageBox::information(this, tr("File Format"),
                                         tr("This is not an XML file."));
            }
        } else {
            QMessageBox::information(this, tr("Empty File"),
                                     tr("The file is empty."));
        }
    }
}

void MainWindow::handleFormatTheFileRequest() {
    if (ui->tabWidget->currentWidget()) {
        QWidget *currentWidget = ui->tabWidget->currentWidget();
        QTextEdit *textEdit = currentWidget->findChild<QTextEdit *>();
        if (textEdit) {
            QString xmlContent = textEdit->toPlainText(); // Get XML content
            if (!xmlContent.isEmpty()) {
                // Check if the file is an XML file
                //if (currentWidget->objectName().endsWith(".xml", Qt::CaseInsensitive)) {
                // Validate XML content
                QDomDocument document;
                QString errorMsg;
                int errorLine, errorColumn;
                if (!document.setContent(xmlContent, true, &errorMsg, &errorLine, &errorColumn)) {
                    QMessageBox::critical(this, tr("XML Error"),
                                          tr("XML Syntax Error at line %1, column %2: %3")
                                              .arg(errorLine).arg(errorColumn).arg(errorMsg));
                    return;
                }

                // XML content is valid, set indentation and colorization
                QString indentedXml = formatXml(xmlContent);
                textEdit->clear();
                textEdit->setPlainText(indentedXml);
                //} else {
                //    QMessageBox::warning(this, tr("File Format Error"),
                //                         tr("The opened file is not an XML file."));
                //}
            } else {
                QMessageBox::information(this, tr("Empty File"),
                                         tr("The file is empty."));
            }
        }
    }
}

// QString MainWindow::formatXml(const QString &xmlContent) {
//     // Create a QDomDocument to parse the XML content
//     QDomDocument document;
//     document.setContent(xmlContent);

//     // Convert the QDomDocument back to a QString with indentation
//     QString indentedXml;
//     QTextStream stream(&indentedXml);
//     document.save(stream, 4); // Indentation level = 4 spaces

//     return indentedXml;
// }

QString MainWindow::formatXml(const QString &xmlContent) {
    QDomDocument document;
    document.setContent(xmlContent);

    QString indentedXml;
    QTextStream stream(&indentedXml);
    formatNode(document.documentElement(), stream, 0); // Start formatting from the root element

    return indentedXml;
}

void MainWindow::formatNode(const QDomNode &node, QTextStream &stream, int indentation) {
    QDomNode currentNode = node;

    while (!currentNode.isNull()) {
        if (currentNode.isElement()) {
            // Add indentation
            for (int i = 0; i < indentation; ++i) {
                stream << "    ";
            }

            // Output the start tag
            QDomElement element = currentNode.toElement();
            stream << "<" << element.tagName() << ">";

            // Check if the element has child nodes
            if (currentNode.hasChildNodes()) {
                stream << Qt::endl; // Move to the next line after the start tag

                // Recursively format child nodes
                formatNode(currentNode.firstChild(), stream, indentation + 1);

                // Add indentation before the end tag
                for (int i = 0; i < indentation; ++i) {
                    stream << "    ";
                }
            }

            // Output the end tag
            stream << "</" << element.tagName() << ">" << Qt::endl;
        } else if (currentNode.isText()) {
            // Output the text content of the node without a preceding newline
            stream << currentNode.toText().data().trimmed() << Qt::endl; // Trim whitespace
        }

        currentNode = currentNode.nextSibling();
    }
}

/********************************************< tabBar Actions ********************************************/
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
    if (ui->tabWidget->currentWidget()) {
        qDebug() << "Copy clicked";
        QWidget *currentWidget = ui->tabWidget->currentWidget();
        QTextEdit *textEdit = currentWidget->findChild<QTextEdit *>();
        if (textEdit) {
            QClipboard *clipboard = QGuiApplication::clipboard();
            clipboard->setText(textEdit->textCursor().selectedText());
        }
    }
}

void MainWindow::on_actionCut_triggered() {
    if (ui->tabWidget->currentWidget()) {
        qDebug() << "Cut clicked";
        QWidget *currentWidget = ui->tabWidget->currentWidget();
        QTextEdit *textEdit = currentWidget->findChild<QTextEdit *>();
        if (textEdit) {
            QClipboard *clipboard = QGuiApplication::clipboard();
            clipboard->setText(textEdit->textCursor().selectedText());
            textEdit->textCursor().removeSelectedText();
        }
    }
}

void MainWindow::on_actionPast_triggered() {
    if (ui->tabWidget->currentWidget()) {
        qDebug() << "Paste clicked";
        QWidget *currentWidget = ui->tabWidget->currentWidget();
        QTextEdit *textEdit = currentWidget->findChild<QTextEdit *>();
        if (textEdit) {
            qDebug() << "Paste occurred";
            QClipboard *clipboard = QGuiApplication::clipboard();
            textEdit->insertPlainText(clipboard->text());
        }
    }
}

void MainWindow::on_actionUndo_triggered() {
    if (currentTextEdit) {
        currentTextEdit->undo();
    }
}

void MainWindow::on_actionRedo_triggered() {
    if (currentTextEdit) {
        currentTextEdit->redo();
    }
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}
/********************************************< End of tabBar Actions ********************************************/


