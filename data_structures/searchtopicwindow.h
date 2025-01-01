#ifndef SEARCHTOPICWINDOW_H
#define SEARCHTOPICWINDOW_H

#include <QDialog>
#include <QCompleter>
#include "xmlparser.h"
#include <QTimer>
#include <QScrollBar>
#include <QTextEdit>

class TopicDetails;
class PostDetails;

namespace Ui {
class SearchTopicWindow;
}

class SearchTopicWindow : public QDialog {
    Q_OBJECT

public:
    explicit SearchTopicWindow(QWidget *parent = nullptr);
    ~SearchTopicWindow();
    void setUsers(const QList<User*>& users);
    void getUniqueTopicsWithDetails();
    void getUniquePostsDetails();
    void UpdateTextField(const QString &arg1);

private slots:
    void on_SearchField_textChanged(const QString &arg1);
    void on_topicsCheckBox_toggled(bool checked);
    void on_postsCheckBox_toggled(bool checked);

private:
    Ui::SearchTopicWindow *ui;
    QCompleter *topicCompleter;
    QCompleter *postCompleter;
    QCompleter *topicsAndPostsComplete;
    QList<User*> users;
    QList<TopicDetails> topicList;
    QList<PostDetails> postList;

    void clearData();
    void resetScrollBar();
    void updateTopicsCompleter();
    void updatePostsCompleter();
};

class TopicDetails {
    friend class SearchTopicWindow;
private:
    QString topic;
    QList<QString>* originalTopics;
    QList<QString*> posts;
    QList<User*> users;
};

class PostDetails {
    friend class SearchTopicWindow;
private:
    QStringList topics;
    User* user;
    QString postBody;
};

#endif // SEARCHTOPICWINDOW_H
