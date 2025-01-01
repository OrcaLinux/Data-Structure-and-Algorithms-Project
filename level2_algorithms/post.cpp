#include "post.h"

post::post(QString _body, QList<QString> &_topics): body(_body),topics(_topics){

}

const QString& post::getBody() const {
    return body;
}


const QList<QString>& post::getTopics() const {
    return topics;
}

QList<post*> searchPosts(const QString &word, const QString &topic, const QList<post*> &allPosts) {
    QList<post*> matchingPosts;

    for (post *p : allPosts) {
        if ((!word.isEmpty() && p->getBody().contains(word, Qt::CaseInsensitive)) ||
            (!word.isEmpty() && p->getTopics().contains(word, Qt::CaseInsensitive)) ||
            (!topic.isEmpty() && p->getTopics().contains(topic, Qt::CaseInsensitive))) {
            matchingPosts.append(p);
        }
    }

    return matchingPosts;
}

