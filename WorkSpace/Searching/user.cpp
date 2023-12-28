#include "user.h"


User::User(QString _id,QString _name,QList<post*>&_posts,QList<QString>&_followers_id): id(_id),name(_name),posts(_posts),followers_id(_followers_id)
{

}
const QList<QString>& User::getFollowersId() const {
    return followers_id;
}



const QString& User::getId() const {
    return id;
}
const QString& User::getName() const {
    return name;
}



const QList<post*>& User::getPosts() const {
    return posts;
}
User::~User(){

    for(post *Post:posts)
    {
        delete Post;
        Post= nullptr;
    }
}

