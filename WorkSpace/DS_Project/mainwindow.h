#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *event);

    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPast_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionAbout_Qt_triggered();

    void quitApp();

    void createNewTab();

    void CloseTabRequested(int index);

private:
    Ui::MainWindow *ui;

    int tabCounter; // Counter to keep track of the tabs
};
#endif // MAINWINDOW_H
