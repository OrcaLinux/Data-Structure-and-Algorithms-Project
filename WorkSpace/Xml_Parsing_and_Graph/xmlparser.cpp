#include "xmlparser.h"
#include <QFile>
#include<QXmlStreamReader>
#include<qdebug.h>
#include<QLabel>
#include"user.h"

/* a constructor that assigns the path of the file to a string called file*/
XMLparser::XMLparser(QString _file) :file(_file) {}
/*a function parses the given file and stores the data*/
const QList <User*> XMLparser::parse(){


    /*creating an object from a QFile class and passing the file as a parameter*/
    QFile newFile(file);
    /*the file is opened in a read only mode */
    newFile.open(QIODevice::ReadOnly);
    /*passing the file to a xml stream reader object*/
    QXmlStreamReader stream(&newFile);
    QString currentId, currentName,currentBody;
    QList <post*> currentPost;
    QList<QString> currentFollowers;
    QList<QString> currentTopics;
    /*traversing the file*/
    while(!stream.isEndDocument() &&!stream.hasError())
    {
        /*creating a token to read tags*/
        QXmlStreamReader ::TokenType token = stream.readNext();
        /*checking if the token equals the start element in the stream reader*/

        if(token==QXmlStreamReader::StartElement)
        {
            /*storing the tag in a string*/
            QString tagName = stream.name().toString();
            if(tagName=="user")
            {

                while (!stream.atEnd() && !stream.hasError())
                {
                    /*forcing the stream to read the start of the line*/
                    stream.readNextStartElement();
                    if (stream.name().toString() == "id")
                    {
                        currentId = stream.readElementText().simplified();

                        break;
                    }
                }
            }
            else if(tagName=="name")
            {
                currentName = stream.readElementText().simplified();

            }

            else if(tagName=="body")
            {
                currentBody = stream.readElementText().simplified();

            }
            else if(tagName == "topic")
            {
                currentTopics.append(stream.readElementText().simplified());
            }
            else if(tagName =="follower" )
            {


                /*forcing the stream to read the start of the line*/
                while (!stream.atEnd() && !stream.hasError())
                {
                    stream.readNextStartElement();
                    if (stream.name().toString() == "id")
                    {
                        currentFollowers.append(stream.readElementText().simplified());
                        break;
                    }
                }


            }
            else
            {
                continue;
            }

        }
        else if(token == QXmlStreamReader::EndElement)
        {

            QString closedTagName = stream.name().toString();
            if(closedTagName=="user")
            {
                users.append(new User(currentId,currentName,currentPost,currentFollowers));
                currentPost.clear();
                currentFollowers.clear();
            }
            else if(closedTagName=="post")
            {
                currentPost.append( new post(currentBody,currentTopics));

                currentTopics.clear();
            }
            else
            {
                continue;
            }

        }

    }
    return users;

}
XMLparser::~XMLparser()
{

    for(User *user: users)
    {
        delete user;
        user = nullptr;
    }
}
bool XMLparser::isValidFile()
{
    return file.endsWith(".txt") ||file.endsWith(".xml");
}
