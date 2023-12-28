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

#endif // XML_TO_JSON
