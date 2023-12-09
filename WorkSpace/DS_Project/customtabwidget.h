#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QTabWidget>

class QPushButton;

class CustomTabWidget : public QTabWidget {
    Q_OBJECT

public:
    CustomTabWidget(QWidget *parent = nullptr);

public slots: // Make the closeTab function public
    void closeTab(int index);

protected:
    void tabInserted(int index) override;

private:
    QList<QPushButton *> closeButtons;
};

#endif // CUSTOMTABWIDGET_H
