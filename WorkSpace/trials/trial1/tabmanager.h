#ifndef TABMANAGER_H
#define TABMANAGER_H

#include "texteditmanager.h"
#include <QWidget>
#include <QTabWidget>

class TabManager : public QWidget {
    Q_OBJECT

public:
    explicit TabManager(QTabWidget *tabWidget, QWidget *parent = nullptr);
    ~TabManager();

    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void closeTab(int index);
    void createNewTab();

private:
    QTabWidget *tabWidget;
    TextEditManager *textEdit;
    void initializeCloseButton();
};

#endif // TABMANAGER_H
