#ifndef XML_TO_JSON
#define XML_TO_JSON

#include <QString>

/**
 * @brief Converts XML text to JSON format.
 *
 * @param xmlText Input XML text to be converted to JSON.
 * @return QString containing the JSON representation of the XML text.
 *         Empty QString if input XML is empty or invalid.
 */
QString XML_2_JSON(QString xmlText);

/**
 * @brief Converts XML text to minified JSON format.
 *
 * @param xmlText Input XML text to be converted to minified JSON.
 * @return QString containing the minified JSON representation of the XML text.
 *         Empty QString if input XML is empty or invalid.
 */
QString XML_2_JSON_Minified(QString xmlText);

/**
 * @brief Formats a JSON string into a single line.
 *
 * This function takes a JSON string as input and formats it into a single line,
 * removing unnecessary whitespaces and newlines between JSON elements while preserving spaces inside values.
 *
 * @param jsonString The input JSON string to be formatted.
 * @return A QString containing the formatted JSON string in a single line.
 */
QString formatJSONToSingleLine(const QString &jsonString);

#endif // XML_TO_JSON
