#include "searchtopicwindow.h"
#include "ui_searchtopicwindow.h"


SearchTopicWindow::SearchTopicWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchTopicWindow),
    topicCompleter(nullptr),
    postCompleter(nullptr),
    topicsAndPostsComplete(nullptr) {
    ui->setupUi(this);
}

SearchTopicWindow::~SearchTopicWindow() {
    delete ui; // Deletes the UI, assuming it owns the UI instance

    //delete topicCompleter;
    //delete postCompleter;
    //delete topicsAndPostsComplete;

    // Ensure the cleanup of dynamically allocated objects in topicList and postList
    for (auto& topic : topicList) {
        delete topic.originalTopics; // Delete the QList<QString>* pointer
        for (auto& post : topic.posts) {
            delete post; // Delete each QString* pointer in the posts list
        }
    }
    //delete ui->SearchField->completer();
}

void SearchTopicWindow::setUsers(const QList<User*>& users){
    this->users = users;
    //init the posts and topics lists.
    getUniqueTopicsWithDetails();
    getUniquePostsDetails();
    QStringList completeList;
    for(TopicDetails t : this->topicList){
        completeList<< t.topic;
    }
    topicCompleter = new QCompleter(completeList, this);
    topicCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->SearchField->setCompleter(topicCompleter);
    //search
    UpdateTextField(ui->SearchField->displayText());
    //reset the scrollbar
    QScrollBar *vScrollBar = ui->textEdit->verticalScrollBar();
    if (vScrollBar) {
        vScrollBar->setValue(vScrollBar->minimum());
    }
}

void SearchTopicWindow::getUniqueTopicsWithDetails(){
    this->topicList = QList<TopicDetails>();

    for (User* user : users) {
        QList<post*> userPosts = user->getPosts(); // Get user's posts

        for (post* userPost : userPosts) {
            QList<QString> postTopics = userPost->getTopics(); // Get post's topics
            QString postBody = userPost->getBody(); // Get post's body

            for (const QString &topic : postTopics) {
                bool topicExists = false;
                for (TopicDetails& topicDetails : topicList) {
                    if (topicDetails.topic == topic) {
                        topicDetails.posts.append(new QString(postBody)); // Store a copy of post body
                        topicDetails.users.append(user); // Store user pointer
                        topicDetails.originalTopics = new QList<QString>(postTopics);
                        topicExists = true;
                        break;
                    }
                }

                if (!topicExists) {
                    TopicDetails newTopic;
                    newTopic.topic = topic;
                    newTopic.posts.append(new QString(postBody)); // Store a copy of post body
                    newTopic.users.append(user); // Store user pointer
                    newTopic.originalTopics = new QList<QString>(postTopics);
                    topicList.append(newTopic);
                }
            }
        }
    }
}

void SearchTopicWindow::getUniquePostsDetails() {
    for (User* user : users) {
        QList<post*> userPosts = user->getPosts(); // Get user's posts

        for (post* userPost : userPosts) {
            PostDetails newPostDetail; // Create a new PostDetails object
            newPostDetail.topics  = userPost->getTopics(); // Get post's topics
            newPostDetail.postBody = userPost->getBody(); // Get post's body
            newPostDetail.user = user;

            this->postList.append(newPostDetail); // Store the PostDetails object
        }
    }
}


void SearchTopicWindow::UpdateTextField(const QString &arg1)
{
    QString searchText = arg1;
    int postsCounter = 0;

    ui->textEdit->clear(); // Clear previous text

    //search using topics
    if(ui->topicsCheckBox->isChecked()){
        QList<TopicDetails*> selectedTopics;
        for (TopicDetails &topic : topicList) {
            if (topic.topic.contains(searchText, Qt::CaseInsensitive)) {
                selectedTopics << &topic;
            }
        }

        for(TopicDetails* selectedTopic : selectedTopics) {
            QTextCursor cursor(ui->textEdit->textCursor());

            for (int i = 0; i < selectedTopic->posts.size(); ++i) {
                //update posts counter
                postsCounter++;
                //add the post
                QString formattedPost = "<b><font size='5' color='DimGrey'>Post Number: " + QString::number(postsCounter) + "</font></b><br>";
                formattedPost += "<b><font color='SlateGrey' size='4'>Topics: " + (selectedTopic->originalTopics->at(0)) + "</font></b>";

                for (int i = 1; i < selectedTopic->originalTopics->size(); ++i) {
                    formattedPost += "<b><font color='SlateGrey' size='4'> - " + (selectedTopic->originalTopics->at(i)) + "</font></b><br>";
                }                formattedPost += "<b><font color='SlateGrey' size='4'>Post body:</font></b><br>" + *(selectedTopic->posts[i]) + "<br>";
                formattedPost += "<font color='LightSlateGrey' size='2'><i>Author:</i></font><font color='LightSlateGrey' size='2'><i>" + selectedTopic->users[i]->getName() + " (" + selectedTopic->users[i]->getId() + ")</i></font><br>";
                formattedPost += "------------------------<br>";
                cursor.insertHtml(formattedPost);
            }
            ui->textEdit->setTextCursor(cursor);
        }
        //reset the scrollbar
        QScrollBar *vScrollBar = ui->textEdit->verticalScrollBar();
        if (vScrollBar) {
            vScrollBar->setValue(vScrollBar->minimum());
        }
    }
    //search using posts
    if(ui->postsCheckBox->isChecked()){
        QList<PostDetails*> selectedPosts;
        for (PostDetails &post : postList) {
            if (post.postBody.contains(searchText, Qt::CaseInsensitive)) {
                selectedPosts << &post;
            }
        }

        for(PostDetails* selectedPost : selectedPosts) {
            QTextCursor cursor(ui->textEdit->textCursor());
            //update posts counter
            postsCounter++;
            //add the post
            QString formattedPost = "<b><font size='5' color='DimGrey'>Post Number: " + QString::number(postsCounter) + "</font></b><br>";
            formattedPost += "<b><font color='SlateGrey' size='4'>Topics: " + (selectedPost->topics[0]) + "</font></b>";

            for (int i = 1; i < selectedPost->topics.size(); ++i) {
                formattedPost += "<b><font color='SlateGrey' size='4'> - " + (selectedPost->topics[i]) + "</font></b><br>";
            }
            formattedPost += "<b><font color='SlateGrey' size='4'>Post body:</font></b><br>" + (selectedPost->postBody) + "<br>";
            formattedPost += "<font color='LightSlateGrey' size='2'><i>Author:</i></font><font color='LightSlateGrey' size='2'><i>" + selectedPost->user->getName() + " (" + selectedPost->user->getId() + ")</i></font><br>";
            formattedPost += "------------------------<br>";
            cursor.insertHtml(formattedPost);
            ui->textEdit->setTextCursor(cursor);
        }
        //reset the scrollbar
        QScrollBar *vScrollBar = ui->textEdit->verticalScrollBar();
        if (vScrollBar) {
            vScrollBar->setValue(vScrollBar->minimum());
        }
    }
    //update the posts number
    ui->postsNoLabel->setText(QString::number(postsCounter));
}

void SearchTopicWindow::on_SearchField_textChanged(const QString &arg1)
{
    // Get the current text from the QLineEdit
    UpdateTextField(arg1);
}


void SearchTopicWindow::on_topicsCheckBox_toggled(bool checked)
{
    if (!checked && !ui->postsCheckBox->isChecked()) {
        ui->topicsCheckBox->setChecked(true); // Prevent unchecking when both are unchecked
    } else if (checked && ui->postsCheckBox->isChecked()) {
        ui->postsCheckBox->setChecked(false); // Prevent unchecking when both are unchecked
        //update completer
        delete ui->SearchField->completer();
        QStringList completeList;
        for(TopicDetails t : this->topicList){
            completeList<< t.topic;
        }
        topicCompleter = new QCompleter(completeList, this);
        topicCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->SearchField->setCompleter(topicCompleter);
    }
    UpdateTextField(ui->SearchField->displayText());
}


void SearchTopicWindow::on_postsCheckBox_toggled(bool checked)
{
    if (!checked && !ui->topicsCheckBox->isChecked()) {
        ui->postsCheckBox->setChecked(true); // Prevent unchecking when both are unchecked
    } else if (checked && ui->topicsCheckBox->isChecked()) {
        ui->topicsCheckBox->setChecked(false); // Prevent both being checked
        //update completer
        delete ui->SearchField->completer();
        QStringList completeList;
        for(PostDetails p : this->postList){
            completeList<< p.postBody.left(100);
        }
        postCompleter = new QCompleter(completeList, this);
        postCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->SearchField->setCompleter(postCompleter);
    }
    UpdateTextField(ui->SearchField->displayText());

}

