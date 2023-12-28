#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "xmlparser.h"
#include<qdebug.h>
#include "graph.h"
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
    QString filePath = "D:\\workspace\\QT_workspace\\xmlparse\\sample.xml";
    XMLparser *newParse = new XMLparser(filePath);
    if(newParse->isValidFile())
    {
        const QList <User*> users = newParse->parse();
        for(int i = 0; i < users.size();i++)
        {

            qInfo()<<users.at(i)->getId();
            qInfo() << users.at(i)->getName();

            for(int j = 0; j < users.at(i)->getPosts().size();j++)
            {
                qInfo() << (users.at(i)->getPosts()).at(j)->getBody();
                for(int k= 0; k < ((users.at(i)->getPosts()).at(j))->getTopics().size();k++ )
                    qInfo() <<  ((users.at(i)->getPosts()).at(j)->getTopics()).at(k);

            }
            for(int l = 0; l< users.at(i)->getFollowersId().size();l++)
                qInfo() << (users.at(i)->getFollowersId()).at(l);
        }
        QList<QString> ids;
        for(int j = 0; j < users.size();j++){
            ids.push_back(users.at(j)->getId());
        }

        Graph graph(users.size(),ids);
        QList<QString> followers;
        for(int j = 0; j <users.size();j++){

            followers = users.at(j)->getFollowersId();
            graph.setAdjacencyListForVertex(users.at(j)->getId(),followers);

        }
        graph.printGraph();


    }
    else
    {
        delete newParse;
    }


}

