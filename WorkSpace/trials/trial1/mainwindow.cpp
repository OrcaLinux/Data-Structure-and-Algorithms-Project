#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "error_detect.h"
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
#include <QScrollBar>
#include <QTextBlock>

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
/********************************************< Tab Bar Action ********************************************/
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

    // Create a QTextEdit for line numbers
    QTextEdit* lineNumberArea = new QTextEdit;
    setLineNumberAreaProperties(lineNumberArea);

    // Connect scrolling between textEdit and lineNumberArea
    connect(textEdit->verticalScrollBar(), &QScrollBar::valueChanged,
            lineNumberArea->verticalScrollBar(), &QScrollBar::setValue);

    connect(lineNumberArea->verticalScrollBar(), &QScrollBar::valueChanged,
            textEdit->verticalScrollBar(), &QScrollBar::setValue);

    // Disable the vertical scrollbar in lineNumberArea
    lineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Connect text changes to update line numbers
    connect(textEdit->document(), &QTextDocument::blockCountChanged,
            this, [=]() {
                QTextBlock block = textEdit->document()->firstBlock();
                QString numbers;
                while (block.isValid()) {
                    numbers += QString::number(block.blockNumber() + 1) + "\n";
                    block = block.next();
                }
                lineNumberArea->setText(numbers);
            });

    connect(textEdit, &QTextEdit::cursorPositionChanged,
            this, [=]() {
                QTextCursor cursor = textEdit->textCursor();
                QTextBlock block = cursor.block();
                int lineNumber = block.blockNumber() + 1;
                statusBar()->showMessage("Line: " + QString::number(lineNumber));
            });

    // Create a horizontal layout to contain textEdit and lineNumberArea
    QHBoxLayout *textEditLayout = new QHBoxLayout;
    textEditLayout->addWidget(lineNumberArea);
    textEditLayout->addWidget(textEdit);

    // Create four push buttons for the tab
    QPushButton *button1 = new QPushButton("Visualize");
    QPushButton *button2 = new QPushButton("Correct");
    QPushButton *button3 = new QPushButton("XML -> JSON");
    QPushButton *button4 = new QPushButton("Compresse");

    // Create a layout for the buttons and add them to it
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);
    buttonLayout->addWidget(button4);

    // Create a layout for the entire tab's content
    QVBoxLayout *tabLayout = new QVBoxLayout;
    tabLayout->addLayout(textEditLayout); // Add the text edit layout to the tab layout
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

    connect(button2, &QPushButton::clicked, this, [=](){
        correct();
    });

    // Trigger an initial update of line numbers upon tab creation
    QTextBlock block = textEdit->document()->firstBlock();
    QString numbers;
    while (block.isValid()) {
        numbers += QString::number(block.blockNumber() + 1) + "\n";
        block = block.next();
    }
    lineNumberArea->setText(numbers);
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

        // Create a QTextEdit for line numbers
        QTextEdit *lineNumberArea = new QTextEdit;
        setLineNumberAreaProperties(lineNumberArea);

        // Connect scrolling between textEdit and lineNumberArea
        connect(textEdit->verticalScrollBar(), &QScrollBar::valueChanged,
                lineNumberArea->verticalScrollBar(), &QScrollBar::setValue);

        connect(lineNumberArea->verticalScrollBar(), &QScrollBar::valueChanged,
                textEdit->verticalScrollBar(), &QScrollBar::setValue);

        // Disable the vertical scrollbar in lineNumberArea
        lineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Connect text changes to update line numbers
        connect(textEdit->document(), &QTextDocument::blockCountChanged,
                this, [=]() {
                    QTextBlock block = textEdit->document()->firstBlock();
                    QString numbers;
                    while (block.isValid()) {
                        numbers += QString::number(block.blockNumber() + 1) + "\n";
                        block = block.next();
                    }
                    lineNumberArea->setText(numbers);
                });

        // Update line numbers immediately after setting text content
        QTextBlock block = textEdit->document()->firstBlock();
        QString numbers;
        while (block.isValid()) {
            numbers += QString::number(block.blockNumber() + 1) + "\n";
            block = block.next();
        }
        lineNumberArea->setText(numbers);

        // Create four push buttons for the tab
        QPushButton *button1 = new QPushButton("Visualize");
        QPushButton *button2 = new QPushButton("Correct");
        QPushButton *button3 = new QPushButton("XML -> JSON");
        QPushButton *button4 = new QPushButton("Compress");

        // Layout setup for buttons
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(button1);
        buttonLayout->addWidget(button2);
        buttonLayout->addWidget(button3);
        buttonLayout->addWidget(button4);

        // Main layout for the tab's content including textEdit and lineNumberArea
        QVBoxLayout *tabLayout = new QVBoxLayout;
        QHBoxLayout *textEditLayout = new QHBoxLayout;
        textEditLayout->addWidget(lineNumberArea);
        textEditLayout->addWidget(textEdit);
        tabLayout->addLayout(textEditLayout);
        tabLayout->addLayout(buttonLayout);

        // Create a widget to hold the layout
        QWidget *tabWidget = new QWidget;
        tabWidget->setLayout(tabLayout);

        // Add the new tab with the file name as the tab title
        int tabIndex = ui->tabWidget->addTab(tabWidget, QFileInfo(fileName).fileName());
        ui->tabWidget->setCurrentIndex(tabIndex);
        ui->tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);

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

        // Connect close button's clicked signal to a slot that closes the corresponding tab
        // Pass file type information to the function for processing
        connect(button1, &QPushButton::clicked, this, [=](){
            handleFormatTheFileRequest(fileName, textEdit, lineNumberArea);
        });
        connect(button2, &QPushButton::clicked, this, [=](){
            correct(textEdit);
        });

    }
}

void MainWindow::setTextEditProperties(QTextEdit* textEdit) {
    textEdit->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu); // Enable context menu
    textEdit->setUndoRedoEnabled(true); // Enable undo and redo
    textEdit->setAcceptRichText(true); // Enable rich text
    textEdit->setReadOnly(false); // Set it to editable

    // Set the font and its properties for the text edit
    QFont font;
    font.setFamily("Open Sans"); // Set the font family
    font.setPointSize(10); // Set the font size
    textEdit->setFont(font); // Apply the font to the text edit

    // Set additional style properties
    // Setting background color and text color
    //textEdit->setStyleSheet("background-color: #F0F0F0; color: #333333;");

    // Set the current text edit to the newly created one
    currentTextEdit = textEdit;
}

void MainWindow::setLineNumberAreaProperties(QTextEdit* lineNumberArea) {
    lineNumberArea->setReadOnly(true);
    lineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNumberArea->setTextInteractionFlags(Qt::NoTextInteraction);
    lineNumberArea->setFixedWidth(40);

    // Set the font and its properties for the text edit
    QFont font;
    font.setFamily("Open Sans"); // Set the font family
    font.setPointSize(10); // Set the font size
    lineNumberArea->setFont(font); // Apply the font to the text edit

    // Set additional style properties
    // Setting background color and text color
    //textEdit->setStyleSheet("background-color: #F0F0F0; color: #333333;");
}

/********************************************< Button Actions ********************************************/
void MainWindow::handleFormatTheFileRequest(const QString& fileName, QTextEdit* textEdit, QTextEdit* lineNumberArea) {
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

                // Set the formatted content with HTML-like tags in QTextEdit
                textEdit->setHtml(indentedXml);
                qDebug () << "Hello After Fomrmat the xml";
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
        if (currentTextEdit) {
            QString xmlContent = currentTextEdit->toPlainText().trimmed(); // Get XML content and trim whitespace

            // Check if the content starts with a common XML declaration or tag
            if (!xmlContent.isEmpty() && (xmlContent.startsWith("<?xml") || xmlContent.startsWith("<"))) {
                QDomDocument document;
                QString errorMsg;
                int errorLine, errorColumn;

                // Attempt to parse the XML content
                if (!document.setContent(xmlContent, true, &errorMsg, &errorLine, &errorColumn)) {
                    QMessageBox::critical(this, tr("XML Error"),
                                          tr("XML Syntax Error at line %1, column %2: %3")
                                              .arg(errorLine).arg(errorColumn).arg(errorMsg));
                    return;
                }

                // XML content is valid, set indentation and colorization
                QString indentedXml = formatXml(xmlContent);
                currentTextEdit->clear();

                // Set the formatted content with HTML-like tags in QTextEdit
                currentTextEdit->setHtml(indentedXml);
            } else {
                QMessageBox::warning(this, tr("File Format Error"),
                                     tr("The opened file does not appear to be an XML file."));
            }
        }
    }
}


void MainWindow::correct(QTextEdit* textEdit) {

    QString xmlContent = textEdit->toPlainText();
                string input = xmlContent.toStdString();
                vector<string> tok = tokenizeFileFromTextInput(input);
                if (bool_errorDetection(tok)){
                    vector<error_detect> errors = int_errorDetection(tok,input);
                    string corrected = input;
                    for ( auto &error : errors) {
                        corrected = errorCorrect(error,corrected,errors);
                    }
                    currentTextEdit->clear();
                    QString qtString = QString::fromStdString(corrected);
                    QTextEdit textEdit;
                    currentTextEdit->setPlainText(qtString);
                    //qDebug () << "Hello After Fomrmat the xml";
                }
}

void MainWindow::correct() {

    if (ui->tabWidget->currentWidget()) {
        if (currentTextEdit) {
            QString xmlContent = currentTextEdit->toPlainText(); // Get XML content and trim whitespace
                string input = xmlContent.toStdString();
                vector<string> tok = tokenizeFileFromTextInput(input);
                if (!bool_errorDetection(tok)){
                    vector<error_detect> errors = int_errorDetection(tok,input);
                    string corrected = input;
                    for ( auto &error : errors) {
                        corrected = errorCorrect(error,corrected,errors);
                    }
                    currentTextEdit->clear();
                    QString Corrected = QString::fromStdString(corrected);
                    //Corrected = "<s>somaya</s>";
                    currentTextEdit->setPlainText(Corrected);
                    //qDebug () << "Hello After Fomrmat the xml";
                }
                else {
                QMessageBox::warning(this, tr("Correct!"),
                                     tr("Your file is correct"));
            }
        }
    }

}

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
                stream << "&nbsp;&nbsp;&nbsp;&nbsp;"; // Use non-breaking spaces for indentation
            }

            // Output the start tag with color formatting
            QDomElement element = currentNode.toElement();
            stream << "<font color=\"#0000FF\">&lt;" << element.tagName() << "&gt;</font>";

            // Check if the element has child nodes
            if (currentNode.hasChildNodes()) {
                stream << "<br>"; // Move to the next line after the start tag

                // Recursively format child nodes
                formatNode(currentNode.firstChild(), stream, indentation + 1);

                // Add indentation before the end tag
                for (int i = 0; i < indentation; ++i) {
                    stream << "&nbsp;&nbsp;&nbsp;&nbsp;";
                }
            }

            // Output the end tag with color formatting
            stream << "<font color=\"#0000FF\">&lt;/" << element.tagName() << "&gt;</font><br>";
        } else if (currentNode.isText()) {
            // Output the text content of the node with indentation
            QString textContent = currentNode.toText().data().trimmed(); // Trim whitespace
            if (!textContent.isEmpty()) {
                for (int i = 0; i < indentation; ++i) {
                    stream << "&nbsp;&nbsp;&nbsp;&nbsp;";
                }
                stream << textContent << "<br>";
            }
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
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(currentTextEdit->textCursor().selectedText());
    }
}

void MainWindow::on_actionCut_triggered() {
    if (ui->tabWidget->currentWidget()) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(currentTextEdit->textCursor().selectedText());
        currentTextEdit->textCursor().removeSelectedText();
    }
}

void MainWindow::on_actionPast_triggered() {
    if (ui->tabWidget->currentWidget()) {
        qDebug() << "Paste clicked";
        QClipboard *clipboard = QGuiApplication::clipboard();
        currentTextEdit->insertPlainText(clipboard->text());
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


