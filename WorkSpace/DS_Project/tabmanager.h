#ifndef TABMANAGER_H
#define TABMANAGER_H

#include "qtexteditsetting.h"
#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QTabWidget>

class TabManager : public QObject {
    Q_OBJECT

public:
    TabManager(QTabWidget* tabWidget);
    ~TabManager();

    void initializeTabBar();
    void setTextEditSettings(const QTextEditSettings &settings);

public slots:
    void exitApplication();

private slots:
    void createNewTab();
    void closeTab(int index);


private:
    QTabWidget* m_tabWidget;
    QTextEditSettings m_textEditSettings;
    int m_tabCounter;

    void setupCloseButton(QPushButton* closeButton);
};

#endif // TABMANAGER_H
