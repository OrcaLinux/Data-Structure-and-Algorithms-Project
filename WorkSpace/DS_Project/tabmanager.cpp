#include "TabManager.h"
#include <QApplication>
#include <QTabBar>
#include <QTimer>

TabManager::TabManager(QTabWidget* tabWidget)
    : QObject(tabWidget), m_tabWidget(tabWidget), m_tabCounter(2) {
    initializeTabBar();
}

TabManager::~TabManager() {
    // Clean up if necessary
}

void TabManager::initializeTabBar() {
    m_tabWidget->tabBar()->installEventFilter(this);
    connect(m_tabWidget, &QTabWidget::tabCloseRequested, this, &TabManager::closeTab);

    // Double-clicking on a tab to create another tab
    connect(m_tabWidget->tabBar(), &QTabBar::tabBarDoubleClicked, this,[=](int index){
        // Create a new tab
        createNewTab();
    });
}

bool TabManager::eventFilter(QObject *obj, QEvent *event) {
    if (obj == m_tabWidget->tabBar() && event->type() == QEvent::MouseButtonDblClick) {
        createNewTab();
        return true; // Event handled
    }
    return QObject::eventFilter(obj, event);
}
void TabManager::createNewTab() {
    QTextEdit *textEdit = m_textEditSettings.createTextEdit();

    QPushButton *closeButton = new QPushButton("X");
    setupCloseButton(closeButton);

    int tabIndex = m_tabWidget->addTab(textEdit, "new " + QString::number(m_tabCounter++));
    m_tabWidget->tabBar()->setTabButton(tabIndex, QTabBar::RightSide, closeButton);
    m_tabWidget->setCurrentIndex(tabIndex);
}

void TabManager::closeTab(int index) {
    int totalTabs = m_tabWidget->count();
    if (totalTabs == 1) {
        return;
    }

    QWidget* tabItem = m_tabWidget->widget(index);
    if (tabItem) {
        QWidget* textEditWidget = m_tabWidget->widget(index)->findChild<QTextEdit *>();
        if (textEditWidget) {
            delete textEditWidget;
        }

        m_tabWidget->removeTab(index);
        delete tabItem;

        if (m_tabWidget->count() == 1) {
            m_tabCounter = 2;
        }
    }
}

void TabManager::exitApplication() {
    QApplication::quit();
}

void TabManager::setupCloseButton(QPushButton* closeButton) {
    QString buttonColor = QApplication::palette().color(QPalette::Button).name();
    closeButton->setFixedSize(16, 16);
    closeButton->setStyleSheet("background-color: " + buttonColor + ";");
    connect(closeButton, &QPushButton::clicked, this,[=]() {
        QWidget* senderButton = qobject_cast<QWidget*>(sender());
        if (senderButton) {
            int tabIndex = m_tabWidget->indexOf(senderButton->parentWidget());
            if (tabIndex != -1) {
                closeTab(tabIndex);
            }
        }
    });
}

void TabManager::setTextEditSettings(const QTextEditSettings &settings) {
    m_textEditSettings = settings;
}
