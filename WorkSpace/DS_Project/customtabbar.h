#ifndef CUSTOMTABBAR_H
#define CUSTOMTABBAR_H

#include <QTabBar>
#include <QPushButton>

class MainWindow; // Forward declare MainWindow

class CustomTabBar : public QTabBar {
    Q_OBJECT

public:
    CustomTabBar(QWidget *parent = nullptr);

protected:
    void tabLayoutChange() override;

private slots:
    void closeTab();

private:
    QList<QPushButton *> closeButtons;
};

#endif // CUSTOMTABBAR_H
