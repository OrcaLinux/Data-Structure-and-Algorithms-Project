/********************************************************************************
** Form generated from reading UI file 'searchtopicwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHTOPICWINDOW_H
#define UI_SEARCHTOPICWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_SearchTopicWindow
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *SearchField;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *topicsCheckBox;
    QCheckBox *postsCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *postsNoLabel;
    QSpacerItem *horizontalSpacer;
    QTextEdit *textEdit;

    void setupUi(QDialog *SearchTopicWindow)
    {
        if (SearchTopicWindow->objectName().isEmpty())
            SearchTopicWindow->setObjectName("SearchTopicWindow");
        SearchTopicWindow->resize(800, 600);
        gridLayout = new QGridLayout(SearchTopicWindow);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        label = new QLabel(SearchTopicWindow);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setCursor(QCursor(Qt::IBeamCursor));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Raised);
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout->addWidget(label);

        SearchField = new QLineEdit(SearchTopicWindow);
        SearchField->setObjectName("SearchField");
        SearchField->setFont(font);

        horizontalLayout->addWidget(SearchField);

        horizontalSpacer_2 = new QSpacerItem(9, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        topicsCheckBox = new QCheckBox(SearchTopicWindow);
        topicsCheckBox->setObjectName("topicsCheckBox");
        QFont font1;
        font1.setPointSize(10);
        topicsCheckBox->setFont(font1);
        topicsCheckBox->setChecked(true);

        horizontalLayout->addWidget(topicsCheckBox);

        postsCheckBox = new QCheckBox(SearchTopicWindow);
        postsCheckBox->setObjectName("postsCheckBox");
        QFont font2;
        font2.setPointSize(9);
        postsCheckBox->setFont(font2);
        postsCheckBox->setChecked(false);

        horizontalLayout->addWidget(postsCheckBox);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        label_2 = new QLabel(SearchTopicWindow);
        label_2->setObjectName("label_2");
        label_2->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        horizontalLayout_2->addWidget(label_2);

        postsNoLabel = new QLabel(SearchTopicWindow);
        postsNoLabel->setObjectName("postsNoLabel");
        postsNoLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_2->addWidget(postsNoLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        textEdit = new QTextEdit(SearchTopicWindow);
        textEdit->setObjectName("textEdit");
        textEdit->setFont(font1);
        textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textEdit->setInputMethodHints(Qt::ImhMultiLine);
        textEdit->setReadOnly(true);
        textEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(textEdit, 1, 0, 1, 1);


        retranslateUi(SearchTopicWindow);

        QMetaObject::connectSlotsByName(SearchTopicWindow);
    } // setupUi

    void retranslateUi(QDialog *SearchTopicWindow)
    {
        SearchTopicWindow->setWindowTitle(QCoreApplication::translate("SearchTopicWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SearchTopicWindow", "Search:", nullptr));
        topicsCheckBox->setText(QCoreApplication::translate("SearchTopicWindow", "Topics", nullptr));
        postsCheckBox->setText(QCoreApplication::translate("SearchTopicWindow", "Posts", nullptr));
        label_2->setText(QCoreApplication::translate("SearchTopicWindow", "Found Posts:", nullptr));
        postsNoLabel->setText(QCoreApplication::translate("SearchTopicWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchTopicWindow: public Ui_SearchTopicWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHTOPICWINDOW_H
