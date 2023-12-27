#include "tabmanager.h"
#include "qapplication.h"
#include <QTextEdit>
#include <QPushButton>
#include <QTabBar>

TabManager::TabManager(QTabWidget *tabWidget, QWidget *parent) : QWidget(parent), tabWidget(tabWidget) {
    // Call the function to create and connect the close button
    initializeCloseButton();

    tabWidget->installEventFilter(this);
}

TabManager::~TabManager() {
    // Clean up if needed
}

bool TabManager::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == tabWidget && event->type() == QEvent::MouseButtonDblClick) {
        createNewTab(); // Create a new tab on double-click event
        return true; // Event handled
    }
    return false; // Event not handled
}

void TabManager::createNewTab() {
    textEdit = new TextEditManager(this);
    // Set properties for the new QTextEdit using TextEditManager
    textEdit->setTextEditProperties();

    QPushButton *closeButton = new QPushButton("X");
    closeButton->setFixedSize(16, 16);

    int tabIndex = tabWidget->addTab(textEdit, "New Tab");
    tabWidget->setCurrentIndex(tabIndex);

    tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);

    connect(closeButton, &QPushButton::clicked, this, [=]() {
        closeTab(tabIndex);
    });
}

void TabManager::closeTab(int index) {
    // Handle closing tabs
    if (tabWidget->count() == 1) {
        // Do nothing when there's only one tab left
        return;
    }

    QWidget *tabItem = tabWidget->widget(index);
    if (tabItem) {
        QWidget *textEditWidget = tabWidget->widget(index)->findChild<QTextEdit *>();
        if (textEditWidget) {
            delete textEditWidget;
        }

        tabWidget->removeTab(index);
        delete tabItem;
    }
}

void TabManager::initializeCloseButton() {
    // Create a close button for the default tab
    QPushButton *closeButton = new QPushButton("X");
    closeButton->setFixedSize(16, 16); // Set a fixed size for the close button

    // Set the background color of the close button to a red color from the Qt palette
    QString redColor = QApplication::palette().color(QPalette::Button).name();
    closeButton->setStyleSheet("background-color: " + redColor + ";");

    // Set the close button within the default tab's title area
    tabWidget->tabBar()->setTabButton(tabWidget->currentIndex(), QTabBar::RightSide, closeButton);

    // Connect the close button's clicked signal to close the default tab
    connect(closeButton, &QPushButton::clicked, this, &TabManager::closeTab);
}
