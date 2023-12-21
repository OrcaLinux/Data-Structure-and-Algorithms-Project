#include "post.h"

post::post(QString _body, QList<QString> &_topics): body(_body),topics(_topics){

}

const QString& post::getBody() const {
    return body;
}



const QList<QString>& post::getTopics() const {
    return topics;
}
