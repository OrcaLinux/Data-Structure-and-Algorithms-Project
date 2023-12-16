#include "qwidget.h"
#include "tabwidget.h"

QWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    customTabBar = new CustomTabBar(this);
    setTabBar(customTabBar); // Set CustomTabBar as the tab bar
}
