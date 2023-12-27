#ifndef XML_TO_JSON
#define XML_TO_JSON


#include <QtXml>
#include <stack>
#include <QRegularExpression>

//  Function Declaration
void closingBracketHandler(QDomElement& currentElement, std::stack<QDomElement>& stack, QTextStream& json);
void closingBracketHandler_Minified(QDomElement& currentElement, std::stack<QDomElement>& stack, QTextStream& json);
void WriteJSON(QDomNode& root, QTextStream& json);
void WriteJSON_Minified(QDomNode& root, QTextStream& json);
QString XML_2_JSON(QString xmlText);
QString XML_2_JSON_Minified(QString xmlText);
QString prettyJSON(QString jsonText);


#endif // XML_TO_JSON
