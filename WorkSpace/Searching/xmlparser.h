#ifndef XMLPARSER_H
#define XMLPARSER_H
#include<QXmlStreamReader>
#include<QFile>
#include <QString>
#include "user.h"
class XMLparser
{
private:
    QString file;
    QList<User*> users;
public:

    XMLparser(QString _file);
    const QList<User*> parse();
    ~XMLparser();
    bool isValidFile();
};

#endif // XMLPARSER_H
