#ifndef XMLTOJSON_PRIVATE_H
#define XMLTOJSON_PRIVATE_H

#include <QtXml>
#include <stack>
#include <QRegularExpression>

//  Function Declaration
/**
 * @brief Handles the closing bracket logic for converting XML elements to JSON.
 *
 * This function manages the proper closing of JSON brackets based on the current XML element,
 * the stack of elements encountered, and the QTextStream used for generating JSON.
 *
 * @param currentElement The current XML element being processed.
 * @param stack The stack of XML elements encountered while parsing.
 * @param json The QTextStream used for generating the JSON output.
 */
static void closingBracketHandler(QDomElement& currentElement, std::stack<QDomElement>& stack, QTextStream& json);

/**
 * @brief Handles the closing bracket logic for converting XML elements to minified JSON.
 *
 * Manages the proper closing of JSON brackets based on the current XML element,
 * the stack of elements encountered, and the QTextStream used for generating minified JSON.
 *
 * @param currentElement The current XML element being processed.
 * @param stack The stack of XML elements encountered while parsing.
 * @param json The QTextStream used for generating the minified JSON output.
 */
static void closingBracketHandler_Minified(QDomElement& currentElement, std::stack<QDomElement>& stack, QTextStream& json);

/**
 * @brief Recursively converts XML nodes to a JSON representation using QTextStream.
 *
 * This function traverses the XML node structure and generates corresponding JSON output
 * via QTextStream, maintaining the hierarchy and structure of the XML elements in the JSON format.
 *
 * @param root The root QDomNode of the XML structure to be converted to JSON.
 * @param json The QTextStream used for generating the JSON output.
 */
static void WriteJSON(QDomNode& root, QTextStream& json);

/**
 * @brief Recursively converts XML nodes to a minified JSON representation using QTextStream.
 *
 * This function traverses the XML node structure and generates minified JSON output
 * via QTextStream, maintaining the hierarchy and structure of the XML elements in the JSON format.
 * The minified JSON output omits unnecessary whitespace and line breaks for compactness.
 *
 * @param root The root QDomNode of the XML structure to be converted to minified JSON.
 * @param json The QTextStream used for generating the minified JSON output.
 */
static void WriteJSON_Minified(QDomNode& root, QTextStream& json);

/**
 * @brief Formats a JSON string for readability by adding indentation.
 *
 * This function takes an input JSON string and applies indentation to enhance readability.
 * It adds appropriate spaces and line breaks to the JSON text to represent a structured format.
 * The indentation is applied based on the opening and closing brackets in the JSON structure.
 *
 * @param jsonText The input JSON text to be formatted for readability.
 * @return A formatted JSON string with improved readability through indentation.
 */
static QString prettyJSON(QString jsonText);

#endif // XMLTOJSON_PRIVATE_H
