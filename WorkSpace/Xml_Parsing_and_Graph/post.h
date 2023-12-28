#ifndef POST_H
#define POST_H

#include<QList>
#include<QString>
class post
{
private:
    QString body;
    QList<QString> topics;
public:
    post(QString _body, QList<QString> &_topics);

    const QString& getBody() const;


    const QList<QString>& getTopics() const;
};
#endif // POST_H
