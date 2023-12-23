/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPast;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionFind;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionSaveACopy;
    QAction *actionSaveAll;
    QAction *actionRename;
    QAction *actionClose;
    QAction *actionCloseAll;
    QAction *actionAuto_Save;
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableWidget *tableWidget;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuSearch;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(912, 617);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/aboutIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/aboutQtIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_Qt->setIcon(icon1);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/copyIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon2);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/cutIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon3);
        actionPast = new QAction(MainWindow);
        actionPast->setObjectName(QString::fromUtf8("actionPast"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/pasteIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPast->setIcon(icon4);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/undoIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon5);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/redoIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon6);
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/findIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionFind->setIcon(icon7);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/newIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon8);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/openIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon9);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/saveIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon10);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/saveAsIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon11);
        actionSaveACopy = new QAction(MainWindow);
        actionSaveACopy->setObjectName(QString::fromUtf8("actionSaveACopy"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/saveACopyAsIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveACopy->setIcon(icon12);
        actionSaveAll = new QAction(MainWindow);
        actionSaveAll->setObjectName(QString::fromUtf8("actionSaveAll"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/saveAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAll->setIcon(icon13);
        actionRename = new QAction(MainWindow);
        actionRename->setObjectName(QString::fromUtf8("actionRename"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/renameIconpng.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRename->setIcon(icon14);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/closeFileIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon15);
        actionCloseAll = new QAction(MainWindow);
        actionCloseAll->setObjectName(QString::fromUtf8("actionCloseAll"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/closeAllIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionCloseAll->setIcon(icon16);
        actionAuto_Save = new QAction(MainWindow);
        actionAuto_Save->setObjectName(QString::fromUtf8("actionAuto_Save"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/autoSaveIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAuto_Save->setIcon(icon17);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/exitIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon18);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setCursor(QCursor(Qt::ArrowCursor));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QFont font2;
        font2.setPointSize(12);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font2);
        tableWidget->setItem(0, 0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font2);
        tableWidget->setItem(1, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font2);
        tableWidget->setItem(2, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font2);
        tableWidget->setItem(3, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font2);
        tableWidget->setItem(4, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font2);
        tableWidget->setItem(5, 0, __qtablewidgetitem7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(false);
        tableWidget->setFont(font3);
        tableWidget->setTabletTracking(false);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(227);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->horizontalHeader()->setStretchLastSection(false);

        verticalLayout_2->addWidget(tableWidget);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 140, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 912, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuSearch = new QMenu(menubar);
        menuSearch->setObjectName(QString::fromUtf8("menuSearch"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuSearch->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveAs);
        menuFile->addAction(actionSaveACopy);
        menuFile->addAction(actionSaveAll);
        menuFile->addAction(actionRename);
        menuFile->addAction(actionClose);
        menuFile->addAction(actionCloseAll);
        menuFile->addSeparator();
        menuFile->addAction(actionAuto_Save);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPast);
        menuEdit->addSeparator();
        menuEdit->addSeparator();
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAbout_Qt);
        menuSearch->addAction(actionFind);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSaveAs);
        toolBar->addAction(actionSaveAll);
        toolBar->addSeparator();
        toolBar->addAction(actionUndo);
        toolBar->addAction(actionRedo);
        toolBar->addSeparator();
        toolBar->addAction(actionCut);
        toolBar->addAction(actionCopy);
        toolBar->addAction(actionPast);
        toolBar->addSeparator();
        toolBar->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionAbout_Qt->setText(QCoreApplication::translate("MainWindow", "About Qt", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
        actionPast->setText(QCoreApplication::translate("MainWindow", "Past", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        actionFind->setText(QCoreApplication::translate("MainWindow", "Find...", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSaveAs->setText(QCoreApplication::translate("MainWindow", "Save As...", nullptr));
        actionSaveACopy->setText(QCoreApplication::translate("MainWindow", "Save a Copy As...", nullptr));
        actionSaveAll->setText(QCoreApplication::translate("MainWindow", "Save All", nullptr));
        actionRename->setText(QCoreApplication::translate("MainWindow", "Rename...", nullptr));
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        actionCloseAll->setText(QCoreApplication::translate("MainWindow", "Close All", nullptr));
        actionAuto_Save->setText(QCoreApplication::translate("MainWindow", "Auto Save", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Team Info.", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Team Members' Names", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Team's ID", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->item(0, 0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Abdelrahman Elsayed", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(1, 0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Eslam Mohamed", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(2, 0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Mennatallah Amr", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(3, 0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Mahmoud Abdelraouf", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(4, 0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Maya Sharaf", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(5, 0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Somay Ayman", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Welcome Tab", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuSearch->setTitle(QCoreApplication::translate("MainWindow", "Search", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
