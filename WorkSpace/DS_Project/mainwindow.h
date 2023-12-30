#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qdom.h"
#include <QFileSystemWatcher>
#include "qtextedit.h"
#include "tabmanager.h"
#include <QMainWindow>

#include <QDebug>
#include "searchtopicwindow.h"
#include "CompressionSystem.h"
#include "DecompressSystem.h"
#include "xmlparser.h"

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
    ~MainWindow();


    void setTextEditProperties(QTextEdit *textEdit);

signals:
    void closePreviousTab();

private slots:
    void openNewTabHandler();
    void on_actionCut_triggered();
    void on_actionExit_triggered();
    void on_actionCopy_triggered();
    void PastTriggered(QTextEdit *textEdit);
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionAbout_Qt_triggered();

    void quitApp();
    void createNewTab();
    void closeTab(int index);
    void handleFormatTheFileRequest(QTextEdit *textEdit);
    bool eventFilter(QObject *obj, QEvent *event);
    /********************************************< Save dialog box ********************************************/

    //pass the extention name without the leading dot '.'
    QString extensionLabel(const QString& expectedExtension);
    //pass the extention name without the leading dot '.'
    QString saveDialogBox(const QString& expectedExtension);
    //pass the extention names without the leading dot '.'
    QString saveDialogBox(const std::vector<QString>& expectedExtensions);
    /********************************************< Button Actions ********************************************/
    void handleFormatTheFileRequest(const QString& fileName, QTextEdit* textEdit);
    void compressFile(const QString& fileName, QTextEdit* textEdit);
    QString decompressFile(const QString& filePath);
    void searchButtonClicked(QTextEdit *textEdit);
    /********************************************< save the chnages in the opened file ********************************************/
    void saveChangesToFile(const QString &path, QTextEdit *textEdit);
    void saveAs(QTextEdit *textEdit);




private:
    Ui::MainWindow *ui;
    TabManager *tabManager; // Manages the tabs
    TextEditManager *textEditManager; // Manages the text edit properties
    QTextEdit *currentTextEdit; // Declare a member variable to keep track of the current QTextEdit
    QFileSystemWatcher *fileWatcher;
    bool isNewTabCreated = false;

    void initializeCloseButton();
    void connectTextEditActions(QTextEdit *textEdit);
    void setLineNumberAreaProperties(QTextEdit *textEdit);
    QString formatXml(const QString &xmlContent);
    void colorizeXml(QTextEdit *textEdit);
    void formatNode(const QDomNode &node, QTextStream &stream, int indentation);
    void createLineNumberArea(QTextEdit* textEdit);
    void updateLineNumbers(QTextEdit *textEdit, QTextEdit *lineNumberArea);
    bool checkIfValidXML(QTextEdit *textEdit);
    void displayTextEditTab(QTextEdit *textEdit);
    void setOpenNewTabProperties(QString fileName);
    void minify(QString fileName, QTextEdit* textEdit);
    QString changeFileExtension(const QString& filePath);
    void createNewTab(const QString &content, const QString &filename);
    void correct(QTextEdit *textEdit);

};
#endif // MAINWINDOW_H
