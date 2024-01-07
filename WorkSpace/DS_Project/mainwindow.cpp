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
#include <QScrollBar>
#include <QTextBlock>
#include "graph.h"
#include "graphicswidget.h"
#include "qjsondocument.h"
#include "XmlToJson_interface.h"
#include "error_detect.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), currentTextEdit(nullptr)
{
    ui->setupUi(this);

    // Call the function to create and connect the close button
    initializeCloseButton();
    // Install event filter on tabWidget
    ui->tabWidget->installEventFilter(this);

    connect(ui->actionNew, &QAction::triggered, this, [=](){
        createNewTab();
    });

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openNewTabHandler);
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
        QWidget* tabItem = ui->tabWidget->widget(tabIndex);
        if (tabItem) {
            QWidget* textEditWidget = ui->tabWidget->widget(tabIndex)->findChild<QTextEdit *>();
            if (textEditWidget) {
                delete textEditWidget; // Delete the text editor widget
            }

            ui->tabWidget->removeTab(tabIndex);
            delete tabItem; // Delete the tab
        }

        createNewTab();
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
    // Set flag to indicate tab creation
    isNewTabCreated = true;

    // Create a new QTextEdit for the tab content
    QTextEdit *textEdit = new QTextEdit;

    // Set properties for the new QTextEdit
    setTextEditProperties(textEdit);

    QString FileName =  "New Tab";

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

    QHBoxLayout *buttonLayout1 = new QHBoxLayout;
    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    QHBoxLayout *buttonLayout3 = new QHBoxLayout;

    QPushButton *button1 = new QPushButton("Prettify");
    QPushButton *button2 = new QPushButton("Correct");
    QPushButton *button3 = new QPushButton("XML -> JSON");
    QPushButton *button4 = new QPushButton("Compress");
    QPushButton *button5 = new QPushButton("Minify");
    QPushButton *button6 = new QPushButton("Decompress");
    QPushButton *button7 = new QPushButton("Visualize");
    QPushButton *button8 = new QPushButton("Search");
    QPushButton *button9 = new QPushButton("Network Analysis");
    buttonLayout1->addWidget(button1);
    buttonLayout1->addWidget(button5);
    buttonLayout1->addWidget(button2);
    buttonLayout1->addWidget(button3);
    buttonLayout1->addWidget(button4);
    buttonLayout1->addWidget(button6);

    buttonLayout2->addWidget(button7);
    buttonLayout2->addWidget(button8);

    buttonLayout3->addWidget(button9);


    // Create a layout for the entire tab's content
    QVBoxLayout *tabLayout = new QVBoxLayout;
    tabLayout->addLayout(textEditLayout); // Add the text edit layout to the tab layout
    tabLayout->addLayout(buttonLayout1); // Add the button layout to the tab layout
    tabLayout->addLayout(buttonLayout2); // Add the button layout to the tab layout
    tabLayout->addLayout(buttonLayout3); // Add the button layout to the tab layout

    // Create a widget to hold the layout
    QWidget *tabWidget = new QWidget;
    tabWidget->setLayout(tabLayout);

    // Set the tab widget as the content for the new tab
    int tabIndex = ui->tabWidget->addTab(tabWidget, FileName);
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
        handleFormatTheFileRequest(textEdit);
    });

    connect(button2, &QPushButton::clicked, this, [=](){
        correct(textEdit);
    });

    // Connect button3's clicked signal to displayTextEditTab and perform XML to JSON conversion
    connect(button3, &QPushButton::clicked, this, [=]() {
        // Check if the XML content is valid before proceeding with conversion
        if (!checkIfValidXML(textEdit)) {
            return; // Do not proceed if the XML is invalid
        }

        QString xmlContent = textEdit->toPlainText();
        QString jsonContent = XML_2_JSON(xmlContent);

        // Create a new QTextEdit for the converted JSON content
        QTextEdit *jsonTextEdit = new QTextEdit;
        setTextEditProperties(jsonTextEdit);
        jsonTextEdit->setText(jsonContent);

        // Display the converted JSON content in a new tab using displayTextEditTab
        displayTextEditTab(jsonTextEdit);
    });

    //Added for compress
    // Connect button4's clicked signal to compressFile
    connect(button4, &QPushButton::clicked, this, [=](){
        compressFile(FileName, textEdit);
    });

    connect(button5, &QPushButton::clicked, this, [=](){
        minify(FileName, textEdit);
    });

    connect(button7, &QPushButton::clicked, this, [=](){
        if(checkIfValidXML(textEdit)) {
            GraphWidget *widget = new GraphWidget(textEdit->toPlainText());
            widget->show();
        }
    });

    connect(ui->actionSave, &QAction::triggered, this, [=]() {
        saveAs(textEdit);
    });

    connect(button9, &QPushButton::clicked, this, [=](){
        if(checkIfValidXML(textEdit)) {
          networkAnalysisClicked(textEdit->toPlainText());
        }
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

void MainWindow::createNewTab(const QString& content, const QString& fileName) {
    // Create a new QTextEdit for the tab content and set its properties
    QTextEdit *textEdit = new QTextEdit;

    // Set properties for the new QTextEdit
    setTextEditProperties(textEdit);

    // Set the provided content to the textEdit
    textEdit->setText(content);
    QFileInfo fileInfo(fileName);
    QString extractedFileName = fileInfo.fileName();

    // Create a close button for the tab
    QPushButton *closeButton = new QPushButton("X");
    closeButton->setFixedSize(16, 16);
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

    // Create a horizontal layout to contain textEdit and lineNumberArea
    QHBoxLayout *textEditLayout = new QHBoxLayout;
    textEditLayout->addWidget(lineNumberArea);
    textEditLayout->addWidget(textEdit);

    // Create four push buttons for the tab
    QHBoxLayout *buttonLayout1 = new QHBoxLayout;
    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    QHBoxLayout *buttonLayout3 = new QHBoxLayout;

    QPushButton *button1 = new QPushButton("Prettify");
    QPushButton *button2 = new QPushButton("Correct");
    QPushButton *button3 = new QPushButton("XML -> JSON");
    QPushButton *button4 = new QPushButton("Compress");
    QPushButton *button5 = new QPushButton("Minify");
    QPushButton *button6 = new QPushButton("Decompress");
    QPushButton *button7 = new QPushButton("Visualize");
    QPushButton *button8 = new QPushButton("Search");
    QPushButton *button9 = new QPushButton("Network Analysis");
    buttonLayout1->addWidget(button1);
    buttonLayout1->addWidget(button5);
    buttonLayout1->addWidget(button2);
    buttonLayout1->addWidget(button3);
    buttonLayout1->addWidget(button4);
    buttonLayout1->addWidget(button6);

    buttonLayout2->addWidget(button7);
    buttonLayout2->addWidget(button8);

    buttonLayout3->addWidget(button9);


    // Create a layout for the entire tab's content
    QVBoxLayout *tabLayout = new QVBoxLayout;
    tabLayout->addLayout(textEditLayout); // Add the text edit layout to the tab layout
    tabLayout->addLayout(buttonLayout1); // Add the button layout to the tab layout
    tabLayout->addLayout(buttonLayout2); // Add the button layout to the tab layout
    tabLayout->addLayout(buttonLayout3);

    QWidget *tabWidget = new QWidget;
    tabWidget->setLayout(tabLayout);

    int tabIndex = ui->tabWidget->addTab(tabWidget, extractedFileName);
    ui->tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);
    ui->tabWidget->setCurrentIndex(tabIndex);

    // Connect the close button's clicked signal to close the corresponding tab
    connect(closeButton, &QPushButton::clicked, this, [=]() {
        int totalTabs = ui->tabWidget->count();
        if (totalTabs == 1) {
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
        handleFormatTheFileRequest(fileName, textEdit);
    });

    connect(button2, &QPushButton::clicked, this, [=](){
        correct(textEdit);
    });

    // Connect button3's clicked signal to displayTextEditTab and perform XML to JSON conversion
    connect(button3, &QPushButton::clicked, this, [=]() {
        // Check if the XML content is valid before proceeding with conversion
        if (!checkIfValidXML(textEdit)) {
            return; // Do not proceed if the XML is invalid
        }

        QString xmlContent = textEdit->toPlainText();
        QString jsonContent = XML_2_JSON(xmlContent);

        // Create a new QTextEdit for the converted JSON content
        QTextEdit *jsonTextEdit = new QTextEdit;
        setTextEditProperties(jsonTextEdit);
        jsonTextEdit->setText(jsonContent);

        // Display the converted JSON content in a new tab using displayTextEditTab
        displayTextEditTab(jsonTextEdit);
    });

    //Added for compress
    // Connect button4's clicked signal to compressFile
    connect(button4, &QPushButton::clicked, this, [=](){
        compressFile(fileName, textEdit);
    });

    connect(button7, &QPushButton::clicked, this, [=](){
        if(checkIfValidXML(textEdit)) {
            GraphWidget *widget = new GraphWidget(textEdit->toPlainText());
            widget->show();
        }
    });

    connect(button8, &QPushButton::clicked, this, [=](){
        //chack the extension
        std::string extension;
        int dotIndex = fileName.lastIndexOf('.');
        if(dotIndex== -1){
            //show an error.
            QMessageBox::critical(nullptr, "Defected file name.", "Please rectify the errors in the file to proceed.");
            return;
        }
        //extract the extension excluding the dot.
        extension = fileName.mid(dotIndex + 1).toStdString();
        if(extension == "xml"){
            //TODO: make it return from this function if it contains errors
            bool correct = checkIfValidXML(textEdit);
            //show search dialog
            if(correct){
            searchButtonClicked(textEdit);
            }
        } else{
            //TODO:???
        }
    });

    connect(button5, &QPushButton::clicked, this, [=](){
        minify(fileName, textEdit);
    });

    connect(button6, &QPushButton::clicked, this, [=](){
        QString decompressedFile = decompressFile(fileName);
        QString newFilePath = changeFileExtension(fileName); // Change the extension based on conditions

        createNewTab(decompressedFile, newFilePath);
    });

    connect(button9, &QPushButton::clicked, this, [=](){
        if(checkIfValidXML(textEdit)) {
            networkAnalysisClicked(textEdit->toPlainText());
        }
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

void MainWindow::openNewTabHandler()
{
    // Open a file dialog to select a file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("XML Files (*.xml);;All Files (*)"));
    setOpenNewTabProperties(fileName);
}

void MainWindow::setOpenNewTabProperties(QString fileName) {
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

        // // Extract the file Name form the file path
        // QFileInfo fileInfo(fileName);
        // QString fileName_ = fileInfo.fileName();

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

        QHBoxLayout *buttonLayout1 = new QHBoxLayout;
        QHBoxLayout *buttonLayout2 = new QHBoxLayout;
        QHBoxLayout *buttonLayout3 = new QHBoxLayout;

        QPushButton *button1 = new QPushButton("Prettify");
        QPushButton *button2 = new QPushButton("Correct");
        QPushButton *button3 = new QPushButton("XML -> JSON");
        QPushButton *button4 = new QPushButton("Compress");
        QPushButton *button5 = new QPushButton("Minify");
        QPushButton *button6 = new QPushButton("Decompress");
        QPushButton *button7 = new QPushButton("Visualize");
        QPushButton *button8 = new QPushButton("Search");
        QPushButton *button9 = new QPushButton("Network Analysis");
        buttonLayout1->addWidget(button1);
        buttonLayout1->addWidget(button5);
        buttonLayout1->addWidget(button2);
        buttonLayout1->addWidget(button3);
        buttonLayout1->addWidget(button4);
        buttonLayout1->addWidget(button6);

        buttonLayout2->addWidget(button7);
        buttonLayout2->addWidget(button8);

        buttonLayout3->addWidget(button9);


        // Main layout for the tab's content including textEdit and lineNumberArea
        QVBoxLayout *tabLayout = new QVBoxLayout;
        QHBoxLayout *textEditLayout = new QHBoxLayout;
        textEditLayout->addWidget(lineNumberArea);
        textEditLayout->addWidget(textEdit);
        tabLayout->addLayout(textEditLayout);
        tabLayout->addLayout(buttonLayout1);
        tabLayout->addLayout(buttonLayout2); // Add the button layout to the tab layout
        tabLayout->addLayout(buttonLayout3); // Add the button layout to the tab layout

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
            handleFormatTheFileRequest(fileName, textEdit);
        });

        connect(button2, &QPushButton::clicked, this, [=](){
            correct(textEdit);
        });

        // Connect button3's clicked signal to displayTextEditTab and perform XML to JSON conversion
        connect(button3, &QPushButton::clicked, this, [=]() {
            // Check if the XML content is valid before proceeding with conversion
            if (!checkIfValidXML(textEdit)) {
                return; // Do not proceed if the XML is invalid
            }

            QString xmlContent = textEdit->toPlainText();
            QString jsonContent = XML_2_JSON(xmlContent);

            // Create a new QTextEdit for the converted JSON content
            QTextEdit *jsonTextEdit = new QTextEdit;
            setTextEditProperties(jsonTextEdit);
            jsonTextEdit->setText(jsonContent);

            // Display the converted JSON content in a new tab using displayTextEditTab
            displayTextEditTab(jsonTextEdit);
        });

        //Added for compress
        // Connect button4's clicked signal to compressFile
        //TODO: add the size.
        connect(button4, &QPushButton::clicked, this, [=](){
            compressFile(fileName, textEdit);
        });

        connect(button5, &QPushButton::clicked, this, [=](){
            minify(fileName, textEdit);
        });

        connect(button6, &QPushButton::clicked, this, [=](){
            QString decompressedFile = decompressFile(fileName);
            QString newFilePath = changeFileExtension(fileName); // Change the extension based on conditions

            createNewTab(decompressedFile, newFilePath);
        });

        connect(button7, &QPushButton::clicked, this, [=](){
            if(checkIfValidXML(textEdit)) {
                GraphWidget *widget = new GraphWidget(textEdit->toPlainText());
                widget->show();
            }
        });

        connect(button8, &QPushButton::clicked, this, [=](){
            //chack the extension
            std::string extension;
            int dotIndex = fileName.lastIndexOf('.');
            if(dotIndex== -1){
                //show an error.
                QMessageBox::critical(nullptr, "Defected file name.", "Please rectify the errors in the file to proceed.");
                return;
            }
            //extract the extension excluding the dot.
            extension = fileName.mid(dotIndex + 1).toStdString();
            if(extension == "xml"){
                //TODO: make it return from this function if it contains errors
                bool correct = checkIfValidXML(textEdit);
                //show search dialog
                if(correct){
                    searchButtonClicked(textEdit);
                }
            } else{
                //TODO:???
            }
        });

        connect(button9, &QPushButton::clicked, this, [=](){
            if(checkIfValidXML(textEdit)) {
                networkAnalysisClicked(textEdit->toPlainText());
            }
        });

        connect(ui->actionSave, &QAction::triggered, this, [=]() {
            saveChangesToFile(fileName, textEdit); // Assuming filePath and textEdit are available here
        });

    }
}

void MainWindow::saveChangesToFile(const QString& filePath, QTextEdit* textEdit) {
    qDebug() << "Hello from saveChangesToFile";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    }
}

void MainWindow::saveAs(QTextEdit *textEdit) {
    QTextEdit *currentTextEdit = getTheCurrentTextEdit();

    // Check the flag to allow saveAs only if called from createNewTab
    if (!isNewTabCreated) {
        // Reset flag for future calls
        isNewTabCreated = false;
        return; // Exit the function without performing any action
    }

    if(textEdit != currentTextEdit) {
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << currentTextEdit->toPlainText();
            file.close();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "File Saved", "File saved successfully. Do you want to open it?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {

                // Check for the total number of tabs
                int totalTabs = ui->tabWidget->count();
                if (totalTabs == 1) {
                    // Do nothing when there's only one tab left
                    return;
                }

                int currentIndex = ui->tabWidget->currentIndex();
                if (currentIndex != -1) {
                    QWidget* currentTabWidget = ui->tabWidget->widget(currentIndex);
                    ui->tabWidget->removeTab(currentIndex);
                    delete currentTabWidget;
                }

                setOpenNewTabProperties(filePath);

                // Reset flag for future calls
                isNewTabCreated = false;
            }
        }
    } else {
        QMessageBox::information(this, "Save Canceled", "Save process was canceled.");
    }
}

void MainWindow::networkAnalysisClicked(QString fileString)
{
    QDialog *dialog = new QDialog();
    dialog -> setWindowModality(Qt::WindowModality::ApplicationModal);
    dialog -> setMinimumWidth(640);
    dialog -> setMinimumHeight(640);

    XMLparser *newParse = new XMLparser(fileString);
    QTextStream stream(stdout);

    if(newParse != nullptr)
    {
        const QList <User*> users = newParse->parse();
        for(int i = 0; i < users.size();i++)
        {

            qInfo()<<users.at(i)->getId();
            qInfo() << users.at(i)->getName();

            for(int j = 0; j < users.at(i)->getPosts().size();j++)
            {
                qInfo() << (users.at(i)->getPosts()).at(j)->getBody();
                for(int k= 0; k < ((users.at(i)->getPosts()).at(j))->getTopics().size();k++ )
                    qInfo() <<  ((users.at(i)->getPosts()).at(j)->getTopics()).at(k);

            }
            for(int l = 0; l< users.at(i)->getFollowersId().size();l++)
                qInfo() << (users.at(i)->getFollowersId()).at(l);
        }
        QList<QString> ids;
        for(int j = 0; j < users.size();j++){
            ids.push_back(users.at(j)->getId());
        }

        Graph graph(users.size(),ids);
        QList<QString> followers;
        for(int j = 0; j <users.size();j++){

            followers = users.at(j)->getFollowersId();
            graph.setAdjacencyListForVertex(users.at(j)->getId(),followers);

        }
        //graph.printGraph();

        /********** most active ****************************/
        QString MostActiveUser = graph.findMostActiveUser();
        QLabel *active = new QLabel();
        active-> setText("Most active user:");
        active-> setGeometry(10,10,150,50);
        active->setParent(dialog);
        active->show();

        QTextEdit *activeOP = new QTextEdit();
        activeOP-> setGeometry(160,10,150,50);
        activeOP->setParent(dialog);
        activeOP->append(MostActiveUser);
        activeOP->show();

        /********** most influence ****************************/
        QString mostInfluential = graph.findMostInfluentialUser();
        QLabel *influence = new QLabel();
        influence-> setText("Most Influential user:");
        influence-> setGeometry(10,80,150,50);
        influence->setParent(dialog);
        influence->show();

        QTextEdit *influenceOP = new QTextEdit();
        influenceOP-> setGeometry(160,80,150,50);
        influenceOP->setParent(dialog);
        influenceOP->append(mostInfluential);
        influenceOP->show();

        /************ *******************************/
        QLabel *muatualLabel = new QLabel();
        muatualLabel-> setText("Mutual Followers between:");
        muatualLabel-> setGeometry(10,160,150,50);
        muatualLabel->setParent(dialog);
        muatualLabel->show();

        QTextEdit *mutual1 = new QTextEdit();
        mutual1-> setToolTip("Enter value of first user");
        mutual1-> setGeometry(160,160,150,50);
        mutual1->setParent(dialog);
        mutual1->show();

        QTextEdit *mutual2 = new QTextEdit();
        mutual2-> setToolTip("Enter value of second user");
        mutual2-> setGeometry(320,160,150,50);
        mutual2->setParent(dialog);
        mutual2->show();

        QPushButton *Mutualbutton = new QPushButton("Get Mutual Followers");
        Mutualbutton->setGeometry(480, 160, 120, 50);
        Mutualbutton->setParent(dialog);
        Mutualbutton->show();

        QTextEdit *mutualOP = new QTextEdit();
        mutualOP->setGeometry(10, 240, 600, 50);
        mutualOP->setParent(dialog);
        mutualOP->show();
        connect(Mutualbutton, &QPushButton::clicked, [=]() {
            // Retrieve the text from mutual1 and mutual2
            QString user1 = mutual1->toPlainText();
            QString user2 = mutual2->toPlainText();
            // Call the function with the entered values
            QList<QString> MutualFollowers = graph.findMutualFollowers(user1, user2);
            // Append the result to mutualOP
            for (int j = 0; j < MutualFollowers.size(); j++)
            {
                QString output = MutualFollowers.at(j) + "  ";
                mutualOP->append(output);
            }

        });

        /*********************************************/
        QLabel *suggestlLabel = new QLabel();
        suggestlLabel-> setText("Suggest followers for:");
        suggestlLabel-> setGeometry(10,310,150,50);
        suggestlLabel->setParent(dialog);
        suggestlLabel->show();

        QTextEdit *suggest = new QTextEdit();
        suggest-> setToolTip("Enter value of user");
        suggest-> setGeometry(160,310,150,50);
        suggest->setParent(dialog);
        suggest->show();

        QPushButton *suggestbutton = new QPushButton("Get sugggestions");
        suggestbutton->setGeometry(480, 310, 120, 50);
        suggestbutton->setParent(dialog);
        suggestbutton->show();

        QTextEdit *suggestOP = new QTextEdit();
        suggestOP-> setGeometry(10,380,600,50);
        suggestOP->setParent(dialog);
        suggestOP->show();

        connect(suggestbutton, &QPushButton::clicked, [=]() {
            QString user = suggest->toPlainText();
            QList<QString> SuggestFollowers = graph.suggestUsersToFollow(user);
            for (int j = 0; j < SuggestFollowers.size(); j++)
            {
                QString output = SuggestFollowers.at(j) + "  ";
                suggestOP->append(output);
            }

        });

        QPushButton *closebutton = new QPushButton("CLOSE");
        closebutton->setGeometry(260, 450, 120, 50);
        closebutton->setParent(dialog);
        closebutton->show();

        connect(closebutton, &QPushButton::clicked, [=]() {
            dialog->close();
        });


    }
    else
    {
        delete newParse;
    }


    dialog -> show();
}
/********************************************< For Buttons Action ********************************************/
QString MainWindow::changeFileExtension(const QString& filePath) {
    QString newFilePath = filePath;

    // Extract the file extension
    QFileInfo fileInfo(filePath);
    QString currentExtension = fileInfo.suffix().toLower(); // Get the current file extension

    // Replace the extension based on conditions
    if (currentExtension == "sncxml" || currentExtension == "cxml") {
        newFilePath.replace(QRegularExpression("\\.(sncxml|cxml)$"), ".xml");
    } else if (currentExtension == "cjson") {
        newFilePath.replace(QRegularExpression("\\.cjson$"), ".json");
    } else if (currentExtension == "cfile") {
        newFilePath.replace(QRegularExpression("\\.cfile$"), ".txt");
    }

    return newFilePath;
}

void MainWindow::minify(QString fileName, QTextEdit *textEdit)
{
    std::string extension;
    int dotIndex = fileName.lastIndexOf('.');
    if(dotIndex== -1){
        //show an error.
        QMessageBox::critical(nullptr, "Defected file name.", "Please check the file extension.");
        return;
    }
    //extract the extension excluding the dot.
    extension = fileName.mid(dotIndex + 1).toStdString();

    if(extension == "xml"){
        textEdit->setText(CompressionSystem::minifyXML(textEdit->toPlainText()));
    } else if (extension == "json"){
        textEdit->setText(CompressionSystem::minifyJSON(textEdit->toPlainText()));
    } else{
        QMessageBox::critical(nullptr, "Operation terminated.", "This file can't be minified.");
    }
}

void MainWindow::displayTextEditTab(QTextEdit* textEdit) {
    // Set properties for the new QTextEdit if needed
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

    // Create layouts for textEdit and buttons
    QHBoxLayout *textEditLayout = new QHBoxLayout;
    textEditLayout->addWidget(lineNumberArea);
    textEditLayout->addWidget(textEdit);

    // Create four push buttons for the tab
    QHBoxLayout *buttonLayout1 = new QHBoxLayout;
    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    QPushButton *button1 = new QPushButton("Prettify");
    QPushButton *button2 = new QPushButton("Correct");
    QPushButton *button3 = new QPushButton("XML -> JSON");
    QPushButton *button4 = new QPushButton("Compress");
    QPushButton *button5 = new QPushButton("Minify");
    QPushButton *button6 = new QPushButton("Decompress");
    QPushButton *button7 = new QPushButton("Visualize");
    QPushButton *button8 = new QPushButton("Search");
    buttonLayout1->addWidget(button1);
    buttonLayout1->addWidget(button5);
    buttonLayout1->addWidget(button2);
    buttonLayout1->addWidget(button3);
    buttonLayout1->addWidget(button4);
    buttonLayout1->addWidget(button6);

    buttonLayout2->addWidget(button7);
    buttonLayout2->addWidget(button8);


    // Create a layout for the entire tab's content
    QVBoxLayout *tabLayout = new QVBoxLayout;
    tabLayout->addLayout(textEditLayout); // Add the text edit layout to the tab layout
    tabLayout->addLayout(buttonLayout1); // Add the button layout to the tab layout
    tabLayout->addLayout(buttonLayout2); // Add the button layout to the tab layout

    QWidget *tabWidget = new QWidget;
    tabWidget->setLayout(tabLayout);

    int tabIndex = ui->tabWidget->addTab(tabWidget, "XML->JSON.json");
    ui->tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);
    ui->tabWidget->setCurrentIndex(tabIndex);

    connect(closeButton, &QPushButton::clicked, this, [=]() {
        int totalTabs = ui->tabWidget->count();
        if (totalTabs == 1) {
            return;
        }
        int closeIndex = ui->tabWidget->indexOf(tabWidget);
        if (closeIndex != -1) {
            ui->tabWidget->removeTab(closeIndex);
            delete tabWidget;
        }
    });

    connect(button1, &QPushButton::clicked, this, [=](){
        handleFormatTheFileRequest(textEdit);
    });

    connect(button2, &QPushButton::clicked, this, [=](){
        correct(textEdit);
    });

    // Connect button3's clicked signal to check if the text is already in JSON format
    connect(button3, &QPushButton::clicked, this, [=]() {
        QString currentText = textEdit->toPlainText();

        // Check if the current text content is JSON
        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(currentText.toUtf8(), &jsonError);

        // If the document is valid JSON, inform the user and return
        if (jsonDoc.isNull() || !jsonDoc.isObject()) {
            // Perform XML to JSON conversion as before
            QString xmlContent = currentText;
            QString jsonContent = XML_2_JSON(xmlContent);
            QMessageBox::information(this, "XML to JSON", "Converted JSON:\n" + jsonContent);
        } else {
            // Display a message indicating the file is already in JSON format
            QMessageBox::information(this, "Already in JSON", "The existing file content is already in JSON format.");
        }
    });

    //Added for compress
    // Connect button4's clicked signal to compressFile
    //TODO: add the size.
    connect(button4, &QPushButton::clicked, this, [=](){
        compressFile("XML->JSON.json", textEdit);
    });

    connect(button5, &QPushButton::clicked, this, [=](){
        minify("XML->JSON.json", textEdit);
    });

    QTextBlock block = textEdit->document()->firstBlock();
    QString numbers;
    while (block.isValid()) {
        numbers += QString::number(block.blockNumber() + 1) + "\n";
        block = block.next();
    }
    lineNumberArea->setText(numbers);
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

                // Set the formatted content with HTML-like tags in QTextEdit
                QString indentedXml = formatXml(fileContent);
                textEdit->clear();
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

void MainWindow::handleFormatTheFileRequest(QTextEdit* textEdit) {
    if (ui->tabWidget->currentWidget()) {
        if (textEdit) {
            QString xmlContent = textEdit->toPlainText().trimmed(); // Get XML content and trim whitespace

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
                textEdit->clear();

                // Set the formatted content with HTML-like tags in QTextEdit
                textEdit->setHtml(indentedXml);
            } else {
                QMessageBox::warning(this, tr("File Format Error"),
                                     tr("The opened file does not appear to be an XML file."));
            }
        }
    }
}

bool MainWindow::checkIfValidXML(QTextEdit *textEdit) {
    if (!ui->tabWidget->currentWidget() || !textEdit)
        return false;

    QString xmlContent = textEdit->toPlainText().trimmed();
    if (xmlContent.isEmpty() || (!xmlContent.startsWith("<?xml") && !xmlContent.startsWith("<"))) {
        QMessageBox::warning(this, tr("File Format Error"),
                             tr("The opened file does not appear to be an XML file."));
        return false;
    }

    QDomDocument document;
    QString errorMsg;
    int errorLine, errorColumn;

    if (!document.setContent(xmlContent, true, &errorMsg, &errorLine, &errorColumn)) {
        QMessageBox::critical(this, tr("XML Error"),
                              tr("XML Syntax Error at line %1, column %2: %3")
                                  .arg(errorLine).arg(errorColumn).arg(errorMsg));
        return false;
    }

    return true;
}

void MainWindow::correct(QTextEdit *textEdit) {

    if (ui->tabWidget->currentWidget()) {
        if (textEdit) {
            QString xmlContent = textEdit->toPlainText(); // Get XML content and trim whitespace
            string input = xmlContent.toStdString();
            vector<string> tok = tokenizeFileFromTextInput(input);
            if (!bool_errorDetection(tok)){
                vector<error_detect> errors = int_errorDetection(tok,input);
                string corrected = input;
                for ( auto &error : errors) {
                    corrected = errorCorrect(error,corrected,errors);
                }
                textEdit->clear();
                QString Corrected = QString::fromStdString(corrected);
                //Corrected = "<s>somaya</s>";
                textEdit->setPlainText(Corrected);
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

/********************************************< compression Actions ********************************************/
void MainWindow::compressFile(const QString& fileName, QTextEdit* textEdit){
    std::string fileText = textEdit->toPlainText().toStdString();

    std::string extension;
    int dotIndex = fileName.lastIndexOf('.');
    if(dotIndex== -1){
        //show an error.
        QMessageBox::critical(nullptr, "Defected file name.", "Please rectify the errors in the file to proceed.");
        return;
    }
    //extract the extension excluding the dot.
    extension = fileName.mid(dotIndex + 1).toStdString();

    //to know if the process completed or not
    bool completed = false;
    //compressed file path.
    std::string newFilePath;
    //check the extention,
    if(extension == "xml"){
        //TODO: if it doesn't contain errors
        bool correctFile = checkIfValidXML(textEdit);

        if(correctFile){
            //check the data
            XMLparser parser = XMLparser(QString::fromStdString(fileText));
            QList<User*> users = parser.parse();
            bool parsableFile = !users.empty();
            if(parsableFile){
                //social network data.
                //open a dialog box with the sncxml extension, and get the path.
                newFilePath = saveDialogBox(QString("sncxml")).toStdString();

                if(newFilePath == "-1"){
                    qDebug() << "Here iam from xml_1";
                    return;
                }

                //compress and save the file.
                completed = CompressionSystem::compress_SocialNetworkXML(fileText, newFilePath);
            } else{
                //any correct xml file.
                //open a dialog box with the cxml extension, and get the path.
                newFilePath = saveDialogBox(QString("cxml")).toStdString();

                if(newFilePath == "-1"){
                    qDebug() << "Here iam";
                    return;
                }

                //compress and save the file.
                completed = CompressionSystem::compress_XML(fileText, newFilePath);
            }
        } else{
            return;
        }
    } else if (extension == "json"){
        //open a dialog box with the cjson extension, and get the path.
        newFilePath = saveDialogBox(QString("cjson")).toStdString();

        if(newFilePath == "-1"){
            return;
        }

        //compress and save the file.
        completed = CompressionSystem::compress_JSON(fileText, newFilePath);
    } else {
        //open a dialog box with the cfile extension, and get the path.
        newFilePath = saveDialogBox(QString("cfile")).toStdString();

        if(newFilePath == "-1"){
            return;
        }

        //compress and save the file.
        completed = CompressionSystem::compress_File(fileText, newFilePath);
    }

    if(completed){
        qint64 originalSize = QFileInfo(fileName).size();
        qint64 compressedSize = QFileInfo(QString::fromStdString(newFilePath)).size();

        double compressionPercentage = 100.0 * (1.0 - (static_cast<double>(compressedSize) / static_cast<double>(originalSize)));

        QString message = QString("Compression completed.\n\n"
                                  "Original file size: %1 bytes\n"
                                  "Compressed file size: %2 bytes\n"
                                  "Compression percentage: %3%\n"
                                  "New file path: %4\n\n"
                                  "Do you want to open the file in a new tab?")
                              .arg(originalSize)
                              .arg(compressedSize)
                              .arg(QString::number(compressionPercentage, 'f', 2)) // Limit to 2 decimal places
                              .arg(QString::fromStdString(newFilePath));

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Compression Completed", message, QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            //open the file in a new tab for the compressed file using the newFilePath.
            setOpenNewTabProperties(QString::fromStdString(newFilePath));

        }
    } else{
        //show an error message that the proccess wasn't comleted.
        QMessageBox::critical(nullptr, "Error", "The operation was aborted due to an unexpected error.");
    }
}

QString MainWindow::saveDialogBox(const std::vector<QString>& expectedExtensions){
    if(expectedExtensions.size() == 0){
        std::runtime_error("Empty vector of extensions.");
    }

    QString formats;
    for(QString expectedExtension : expectedExtensions){
        formats += extensionLabel(expectedExtension) + ";;";
    }
    formats.chop(2); // Removes the last two characters (";;")

    //open a dialog box with the sncxml extension, and get the path.
    QString newFilePath =QFileDialog::getSaveFileName(nullptr, "Save File", QDir::homePath(), formats);

    //if the file path was empty, show an error message
    if(newFilePath.isEmpty()){
        QMessageBox::critical(nullptr, "Operation terminated.", "Please provide a file name to proceed.");
        return "-1";
    }

    return newFilePath;
}

QString MainWindow::saveDialogBox(const QString& expectedExtension){
    // call the overloaded function
    std::vector<QString> expectedExtensions;
    expectedExtensions.push_back(expectedExtension);
    QString newFilePath = saveDialogBox(expectedExtensions);

    if(newFilePath == "-1") {
        return newFilePath;
    }

    // Ensure the chosen file has the specified extension.
    QString chosenExtension = QFileInfo(newFilePath).suffix();
    if (chosenExtension.isEmpty()) {
        newFilePath += "." + expectedExtension;
    }
    return newFilePath;
}

QString MainWindow::extensionLabel(const QString& expectedExtension){
    if(expectedExtension == "sncxml"){
        return QString("Social Network Compressed XML (*.sncxml)");
    } else if (expectedExtension == "cxml"){
        return QString("Compressed XML (*.cxml)");
    } else if (expectedExtension == "cjson"){
        return QString("Compressed JSON (*.cjson)");
    } else if (expectedExtension == "cfile"){
        return QString("Compressed Txt (*.cfile)");
    } else if (expectedExtension == "xml"){
        return QString("XML (*.xml)");
    } else if (expectedExtension == "json"){
        return QString("JSON (*.json)");
    } else if (expectedExtension == "txt"){
        return QString("Txt File (*.txt)");
    } else{
        return QString("All Files (*)");
    }
}

/********************************************< decompression Actions ********************************************/
QString MainWindow::decompressFile(const QString& filePath){
    //Check the extension
    std::string extension;
    int dotIndex = filePath.lastIndexOf('.');
    if(dotIndex== -1){
        //show an error.
        QMessageBox::critical(nullptr, "Invalid File Path", "Please correct the errors within the file before proceeding.");
        return QString();
    }
    //extract the extension excluding the dot.
    extension = filePath.mid(dotIndex + 1).toStdString();

    //store the result of decompression
    QString result;
    //compress the file according to its extension
    try{
        if(extension == "sncxml"){
            //compressed social network data.
            std::string* r = DecompressSystem::decompress_SocialNetworkXML(filePath.toStdString());
            result = QString::fromStdString(*r);
            delete r;
            r = nullptr;

        } else if(extension == "cxml"){
            //compressed xml file.
            std::string* r = DecompressSystem::decompress_XML(filePath.toStdString());
            result = QString::fromStdString(*r);
            delete r;
            r = nullptr;

        } else if(extension == "cjson"){
            //compressed json
            std::string* r = DecompressSystem::decompress_JSON(filePath.toStdString());
            result = QString::fromStdString(*r);
            delete r;
            r = nullptr;

        } else if(extension == "cfile"){
            //compressed file.
            std::string* r = DecompressSystem::decompress_File(filePath.toStdString());
            result = QString::fromStdString(*r);
            delete r;
            r = nullptr;

        } else {
            //show an error, that file can't be decompressed.
            QMessageBox::critical(nullptr, "Operation terminated.", "The file format is not recognized as a standard compressed format and cannot be decompressed.");
            return QString();
        }
    }
    catch(const std::exception& e){
        QMessageBox::critical(nullptr, "Operation terminated.", "The file is corrupt and cannot be decompressed.");
        return QString();
    }
    return result;
}

void MainWindow::searchButtonClicked(QTextEdit *textEdit)
{
    checkIfValidXML(textEdit);
    XMLparser *newParse = new XMLparser(textEdit->toPlainText());

        const QList <User*> users = newParse->parse();
        //new window for search
        SearchTopicWindow s;
        s.setUsers(users);
        s.exec();
        for(User* u : users){
            delete u;
        }

}

/********************************************< tabBar Actions ********************************************/
void MainWindow::on_actionExit_triggered()
{
    statusBar()->showMessage("App will be Exit in 3 seconds...", 3000);
    QTimer::singleShot(3000, this , SLOT(quitApp()));
}

// In the implementation file (mainwindow.cpp), define the quitApp slot
void MainWindow::quitApp() {
    QApplication::quit(); // Terminates the application
}

void MainWindow::on_actionCopy_triggered() {
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex != -1) {
        QWidget* currentTabWidget = ui->tabWidget->widget(currentIndex);
        if (currentTabWidget) {
            QVBoxLayout* tabLayout = qobject_cast<QVBoxLayout*>(currentTabWidget->layout());
            if (tabLayout && tabLayout->count() > 0) {
                QHBoxLayout* textEditLayout = qobject_cast<QHBoxLayout*>(tabLayout->itemAt(0)->layout());
                if (textEditLayout && textEditLayout->count() > 1) {
                    QTextEdit* currentTextEdit = qobject_cast<QTextEdit*>(textEditLayout->itemAt(1)->widget());
                    if (currentTextEdit) {
                        QClipboard *clipboard = QGuiApplication::clipboard();
                        clipboard->setText(currentTextEdit->textCursor().selectedText());
                    }
                }
            }
        }
    }
}

void MainWindow::on_actionCut_triggered() {
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex != -1) {
        QWidget* currentTabWidget = ui->tabWidget->widget(currentIndex);
        if (currentTabWidget) {
            QVBoxLayout* tabLayout = qobject_cast<QVBoxLayout*>(currentTabWidget->layout());
            if (tabLayout && tabLayout->count() > 0) {
                QHBoxLayout* textEditLayout = qobject_cast<QHBoxLayout*>(tabLayout->itemAt(0)->layout());
                if (textEditLayout && textEditLayout->count() > 1) {
                    QTextEdit* currentTextEdit = qobject_cast<QTextEdit*>(textEditLayout->itemAt(1)->widget());
                    if (currentTextEdit) {
                        QClipboard *clipboard = QGuiApplication::clipboard();
                        clipboard->setText(currentTextEdit->textCursor().selectedText());
                        currentTextEdit->textCursor().removeSelectedText();
                    }
                }
            }
        }
    }
}

void MainWindow::on_actionPast_triggered() {
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex != -1) {
        QWidget* currentTabWidget = ui->tabWidget->widget(currentIndex);
        if (currentTabWidget) {
            QVBoxLayout* tabLayout = qobject_cast<QVBoxLayout*>(currentTabWidget->layout());
            if (tabLayout && tabLayout->count() > 0) {
                QHBoxLayout* textEditLayout = qobject_cast<QHBoxLayout*>(tabLayout->itemAt(0)->layout());
                if (textEditLayout && textEditLayout->count() > 1) {
                    QTextEdit* textEdit = qobject_cast<QTextEdit*>(textEditLayout->itemAt(1)->widget());
                    if (textEdit) {
                        qDebug() << "Paste clicked";
                        QClipboard* clipboard = QGuiApplication::clipboard();
                        textEdit->insertPlainText(clipboard->text());
                    }
                }
            }
        }
    }
}

void MainWindow::on_actionUndo_triggered() {
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex != -1) {
        QWidget* currentTabWidget = ui->tabWidget->widget(currentIndex);
        if (currentTabWidget) {
            QVBoxLayout* tabLayout = qobject_cast<QVBoxLayout*>(currentTabWidget->layout());
            if (tabLayout && tabLayout->count() > 0) {
                QHBoxLayout* textEditLayout = qobject_cast<QHBoxLayout*>(tabLayout->itemAt(0)->layout());
                if (textEditLayout && textEditLayout->count() > 1) {
                    QTextEdit* currentTextEdit = qobject_cast<QTextEdit*>(textEditLayout->itemAt(1)->widget());
                    if (currentTextEdit) {
                        currentTextEdit->undo();
                    }
                }
            }
        }
    }
}

void MainWindow::on_actionRedo_triggered() {
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex != -1) {
        QWidget* currentTabWidget = ui->tabWidget->widget(currentIndex);
        if (currentTabWidget) {
            QVBoxLayout* tabLayout = qobject_cast<QVBoxLayout*>(currentTabWidget->layout());
            if (tabLayout && tabLayout->count() > 0) {
                QHBoxLayout* textEditLayout = qobject_cast<QHBoxLayout*>(tabLayout->itemAt(0)->layout());
                if (textEditLayout && textEditLayout->count() > 1) {
                    QTextEdit* currentTextEdit = qobject_cast<QTextEdit*>(textEditLayout->itemAt(1)->widget());
                    if (currentTextEdit) {
                        currentTextEdit->redo();
                    }
                }
            }
        }
    }
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

QTextEdit *MainWindow::getTheCurrentTextEdit(){
    QTextEdit * textEdit = nullptr;
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex != -1) {
        QWidget* currentTabWidget = ui->tabWidget->widget(currentIndex);
        if (currentTabWidget) {
            QVBoxLayout* tabLayout = qobject_cast<QVBoxLayout*>(currentTabWidget->layout());
            if (tabLayout && tabLayout->count() > 0) {
                QHBoxLayout* textEditLayout = qobject_cast<QHBoxLayout*>(tabLayout->itemAt(0)->layout());
                if (textEditLayout && textEditLayout->count() > 1) {
                    QTextEdit* currentTextEdit = qobject_cast<QTextEdit*>(textEditLayout->itemAt(1)->widget());
                    if (currentTextEdit) {
                        textEdit = currentTextEdit;
                    }
                }
            }
        }
    }

    return textEdit;
}
/********************************************< End of tabBar Actions ********************************************/


