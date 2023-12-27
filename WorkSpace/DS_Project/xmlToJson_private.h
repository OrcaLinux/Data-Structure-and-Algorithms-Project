#ifndef XMLTOJSON_PRIVATE_H
#define XMLTOJSON_PRIVATE_H

#include <QtXml>
#include <stack>
#include <QRegularExpression>

//  Function Declaration
static void closingBracketHandler(QDomElement& currentElement, std::stack<QDomElement>& stack, QTextStream& json);
static void closingBracketHandler_Minified(QDomElement& currentElement, std::stack<QDomElement>& stack, QTextStream& json);
static void WriteJSON(QDomNode& root, QTextStream& json);
static void WriteJSON_Minified(QDomNode& root, QTextStream& json);
static QString prettyJSON(QString jsonText);

#endif // XMLTOJSON_PRIVATE_H
