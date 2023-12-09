#include "customtabwidget.h"
#include <QPushButton>
#include <QTabBar>

CustomTabWidget::CustomTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
}

void CustomTabWidget::tabInserted(int index)
{
    QTabWidget::tabInserted(index);

    QPushButton *closeButton = new QPushButton("x", this);
    closeButton->setProperty("index", index);
    closeButton->setStyleSheet("background-color: transparent; border: none; color: red;");
    closeButton->setCursor(Qt::PointingHandCursor);
    closeButton->resize(16, 16);
    closeButton->move(tabBar()->tabRect(index).right() - closeButton->width(), 4);

    closeButtons.insert(index, closeButton);
    connect(closeButton, &QPushButton::clicked, [this, index](){ closeTab(index); });
}

void CustomTabWidget::closeTab(int index)
{
    removeTab(index);
    delete closeButtons.takeAt(index);
}
