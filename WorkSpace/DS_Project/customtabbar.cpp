#include "customtabbar.h"

CustomTabBar::CustomTabBar(QWidget *parent)
    : QTabBar(parent)
{
}

void CustomTabBar::tabLayoutChange()
{
    for (int i = 0; i < count(); ++i) {
        if (closeButtons.count() <= i) {
            QPushButton *closeButton = new QPushButton("x", this);
            closeButton->setProperty("index", i);
            closeButton->setStyleSheet("background-color: transparent; border: none; color: red;");
            closeButton->setCursor(Qt::PointingHandCursor);
            closeButton->resize(16, 16);
            closeButton->move(tabRect(i).right() - closeButton->width(), 4);
            closeButtons.append(closeButton);

            connect(closeButton, &QPushButton::clicked, this, &CustomTabBar::closeTab);
        }
    }

    QTabBar::tabLayoutChange();
}

void CustomTabBar::closeTab()
{
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        int index = senderButton->property("index").toInt();
        emit tabCloseRequested(index);
    }
}
