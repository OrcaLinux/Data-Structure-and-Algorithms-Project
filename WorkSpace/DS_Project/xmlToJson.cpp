#include "xmlToJson.h"

/********************************************< Function Implementation ********************************************/

// Function to convert XML text to a pretty-formatted JSON string
QString XML_2_JSON(QString xmlText) {
    // Check if the input XML text is empty
    if (xmlText.isEmpty()) {
        return "";
    }

    QString temp; // Temporary QString to store JSON data
    QTextStream jsonStream(&temp); // Create a QTextStream that writes to the QString temp
    QDomDocument doc;
    doc.setContent(xmlText); // Set the XML content for the QDomDocument

    QDomElement rootElement = doc.documentElement(); // Get the root element of the XML document
    jsonStream << "{\n\"" << rootElement.nodeName() << "\": {\n"; // Start building the JSON string with the root element name

    // Call the WriteJSON function to convert XML to JSON recursively
    WriteJSON(rootElement, jsonStream);

    jsonStream << "}\n}"; // Close the JSON object
    QString jsonText = jsonStream.readAll(); // Read the JSON text from the stream

    // Apply a function to format the JSON string for readability
    return prettyJSON(jsonText);
}


// Function to convert XML text to a minified JSON string
QString XML_2_JSON_Minified(QString xmlText) {
    // Check if the input XML text is empty
    if (xmlText.isEmpty()) {
        return "";
    }

    QString temp; // Temporary QString to store JSON data
    QTextStream jsonStream(&temp); // Create a QTextStream that writes to the QString temp
    QDomDocument doc;
    doc.setContent(xmlText); // Set the XML content for the QDomDocument

    QDomElement rootElement = doc.documentElement(); // Get the root element of the XML document
    jsonStream << "{\"" << rootElement.nodeName() << "\":{"; // Start building the JSON string with the root element name

    // Call the WriteJSON_Minified function to convert XML to minified JSON recursively
    WriteJSON_Minified(rootElement, jsonStream);

    jsonStream << "}}"; // Close the JSON object
    QString jsonText = jsonStream.readAll(); // Read the minified JSON text from the stream

    return jsonText;
}

void WriteJSON(QDomNode& root, QTextStream& json) {
    static std::stack<QDomElement> stack; // Stack to keep track of opened XML elements
    QDomNode currentNode = root.firstChild();
    QDomElement currentElement;

    while (!currentNode.isNull()) {
        if (currentNode.isElement()) {
            currentElement = currentNode.toElement();

            // Check if the current element has child nodes and the first child is not text
            if (currentElement.hasChildNodes() && !currentElement.childNodes().at(0).isText()) {
                // more than one same element type
                if (!stack.empty() && currentElement.nodeName() == stack.top().nodeName()) {
                    json << "{\n";
                }
                // multiple child elements with the same name
                else if (currentElement.nodeName() == currentElement.nextSibling().nodeName()) {
                    json << "\"" << currentElement.tagName() << "\": [\n{\n";
                }
                // single child element
                else {
                    json << "\"" << currentElement.tagName() << "\": {\n";
                }
            }
            // Handle text content nodes
            else if (currentElement.hasChildNodes() && currentElement.childNodes().at(0).isText()) {
                // Check if the current element matches the top of the stack
                if (currentElement.nodeName() == stack.top().nodeName()) {
                    // Check for multiple text content children with the same name
                    if (currentElement.nodeName() == currentElement.nextSibling().nodeName()) {
                        json << "\"" << currentElement.text() << "\",\n";
                    } else {
                        json << "\"" << currentElement.text().trimmed() << "\"\n";
                    }
                }
                // Multiple text content children with the same name
                else if (currentElement.nodeName() == currentElement.nextSibling().nodeName()) {
                    json << "\"" << currentElement.tagName() << "\": [\n";
                    json << "\"" << currentElement.text().trimmed() << "\",\n";
                }
                // No array, single text content child
                else {
                    QString tagName = currentElement.tagName();
                    QString innerData = currentElement.text().trimmed();
                    if (!currentElement.nextSibling().isNull()) {
                        json << "\"" << tagName << "\": \"" << innerData << "\",\n";
                    } else {
                        json << "\"" << tagName << "\": \"" << innerData << "\"\n";
                    }
                }
            }
            // Push the current element onto the stack
            stack.push(currentElement);
        }

        // Recursive call to process child nodes
        WriteJSON(currentNode, json);

        // Handle closing brackets
        closingBracketHandler(currentElement,stack,json);

        currentNode = currentNode.nextSibling();
    }
}

// Function to write XML data in a minified JSON format
void WriteJSON_Minified(QDomNode& root, QTextStream& json) {
    static std::stack<QDomElement> stack; // Stack to keep track of opened XML elements
    QDomNode currentNode = root.firstChild();
    QDomElement currentElement;

    while (!currentNode.isNull()) {
        if (currentNode.isElement()) {
            currentElement = currentNode.toElement();

            // Check if the current element has child nodes and the first child is not text
            if (currentElement.hasChildNodes() && !currentElement.childNodes().at(0).isText()) {
                // More than one element of the same type
                if (!stack.empty() && currentElement.nodeName() == stack.top().nodeName()) {
                    json << "{";
                }
                // Multiple child elements with the same name
                else if (currentElement.nodeName() == currentElement.nextSibling().nodeName()) {
                    json << "\"" << currentElement.tagName() << "\":[{";
                }
                // Single child element
                else {
                    json << "\"" << currentElement.tagName() << "\":{";
                }
            }
            // Handle text content nodes
            else if (currentElement.hasChildNodes() && currentElement.childNodes().at(0).isText()) {
                // Check if the current element matches the top of the stack
                if (currentElement.nodeName() == stack.top().nodeName()) {
                    // Check for multiple text content children with the same name
                    if (currentElement.nodeName() == currentElement.nextSibling().nodeName()) {
                        json << "\"" << currentElement.text() << "\",";
                    } else {
                        json << "\"" << currentElement.text().trimmed() << "\"";
                    }
                }
                // Multiple text content children with the same name
                else if (currentElement.nodeName() == currentElement.nextSibling().nodeName()) {
                    json << "\"" << currentElement.tagName() << "\":[";
                    json << "\"" << currentElement.text().trimmed() << "\",";
                }
                // No array, single text content child
                else {
                    QString tagName = currentElement.tagName();
                    QString innerData = currentElement.text().trimmed();
                    if (!currentElement.nextSibling().isNull()) {
                        json << "\"" << tagName << "\":\"" << innerData << "\",";
                    } else {
                        json << "\"" << tagName << "\":\"" << innerData << "\"";
                    }
                }
            }
            stack.push(currentElement);
        }

        // Recursive call to process child nodes
        WriteJSON_Minified(currentNode, json);

        // Handle closing brackets
        closingBracketHandler_Minified(currentElement, stack, json);

        currentNode = currentNode.nextSibling();
    }
}


// Function to format JSON text for readability
QString prettyJSON(QString jsonText) {
    QTextStream inStream(&jsonText); // Create a QTextStream to read from the input JSON text
    QString temp; // Temporary QString to store the formatted JSON data
    QTextStream outStream(&temp); // Create a QTextStream to write to the QString temp

    static int spaceCount = 0; // Static variable to keep track of the current indentation level
    const static QString space(" "); // String representing a space character
    QRegularExpression openBracketRule("[{\[]$"); // Regular expression to match an open bracket at the end of a line
    QRegularExpression closedBracketRule("(},|]|})$"); // Regular expression to match a closed bracket at the end of a line

    while (!inStream.atEnd()) {
        QString line = inStream.readLine(); // Read a line from the input JSON text

        if (line.contains(openBracketRule)) {
            outStream << space.repeated(spaceCount) << line << "\n"; // Add indentation for an open bracket
            spaceCount += 4; // Increase the indentation level
        }
        else if (line.contains(closedBracketRule)) {
            spaceCount -= 4; // Decrease the indentation level before a closed bracket
            outStream << space.repeated(spaceCount) << line << "\n"; // Add indentation for a closed bracket
        }
        else {
            outStream << space.repeated(spaceCount) << line << "\n"; // Add indentation for other lines
        }
    }

    QString prettyJSONText = outStream.readAll(); // Read the formatted JSON text from the stream
    prettyJSONText.chop(1); // Remove the extra new line at the end
    return prettyJSONText; // Return the formatted JSON text
}


// Function to handle closing brackets in the JSON output
void closingBracketHandler(QDomElement& currentElement, std::stack<QDomElement>& stack, QTextStream& json) {
    int cnt = 0;

    // Check if the next sibling has a different name
    if (currentElement.nextSibling().nodeName() != currentElement.nodeName()) {
        // Pop elements from the stack until the top element has a different name
        while (!stack.empty() && stack.top().nodeName() == currentElement.nodeName()) {
            stack.pop();
            ++cnt;
        }
    }

    // Handle closing bracket logic
    if ((!currentElement.isNull() && currentElement.nodeName() != "#text" && !currentElement.childNodes().at(0).isText()) || cnt > 1) {
        if (!currentElement.nextSibling().isNull()) {
            if (cnt <= 1) {
                json << "},\n"; // Close the object or array
            } else {
                if (currentElement.childNodes().at(0).isText()) {
                    json << "],\n"; // Close the array
                } else {
                    json << "}\n],\n"; // Close the object inside an array
                }
            }
        } else {
            if (cnt <= 1) {
                json << "}\n"; // Close the object or array
            } else {
                if (currentElement.childNodes().at(0).isText()) {
                    json << "]\n"; // Close the array
                } else {
                    json << "}\n]\n"; // Close the object inside an array
                }
            }
        }
    }
}

// Function to handle closing brackets in the minified JSON output
void closingBracketHandler_Minified(QDomElement& currentElement, std::stack<QDomElement>& stack, QTextStream& json) {
    int cnt = 0;

    // Check if the next sibling has a different name
    if (currentElement.nextSibling().nodeName() != currentElement.nodeName()) {
        // Pop elements from the stack until the top element has a different name
        while (!stack.empty() && stack.top().nodeName() == currentElement.nodeName()) {
            stack.pop();
            ++cnt;
        }
    }

    // Handle closing bracket logic in the minified JSON output
    if ((!currentElement.isNull() && currentElement.nodeName() != "#text" && !currentElement.childNodes().at(0).isText()) || cnt > 1) {
        if (!currentElement.nextSibling().isNull()) {
            if (cnt <= 1) {
                json << "},"; // Close the object or array
            } else {
                if (currentElement.childNodes().at(0).isText()) {
                    json << "],"; // Close the array
                } else {
                    json << "}],"; // Close the object inside an array
                }
            }
        } else {
            if (cnt <= 1) {
                json << "}"; // Close the object or array
            } else {
                if (currentElement.childNodes().at(0).isText()) {
                    json << "]"; // Close the array
                } else {
                    json << "}]"; // Close the object inside an array
                }
            }
        }
    }
}
