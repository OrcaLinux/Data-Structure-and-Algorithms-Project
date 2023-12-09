#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include "customtabbar.h"

class TabWidget : public QTabWidget {
    Q_OBJECT
public:
    TabWidget(QWidget *parent = nullptr);

private:
    CustomTabBar *customTabBar;
};

#endif // TABWIDGET_H
