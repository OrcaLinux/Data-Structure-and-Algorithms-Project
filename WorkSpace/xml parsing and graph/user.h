#ifndef USER_H
#define USER_H

#include<QString>
#include<QList>
#include "post.h"
class User
{
private:
    QString id;
    QString name;
    QList<post*> posts;
    QList<QString> followers_id;
public:
    User(QString _id,QString _name,QList<post*>&_posts,QList<QString>&_followers_id);

    const QList<QString>& getFollowersId() const;

    const QString& getId() const;
    const QString& getName() const;
    const QList<post*>& getPosts() const;
    ~User();
};

#endif // USER_H
