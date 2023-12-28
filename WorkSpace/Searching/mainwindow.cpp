#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "xmlparser.h"
#include "searchtopicwindow.h"
#include<qdebug.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filePath = "D:\\Engineering\\Senior 1\\Fall\\Data structure\\Project\\My tasks\\Search\\SearchTask\\sample.xml";
    XMLparser *newParse = new XMLparser(filePath);
    if(newParse->isValidFile())
    {
        const QList <User*> users = newParse->parse();
        //new window for search
        SearchTopicWindow s;
        s.setUsers(users);
        s.exec();
        for(User* u : users){
            delete u;
        }
    }
    else
    {
        delete newParse;
    }
}




