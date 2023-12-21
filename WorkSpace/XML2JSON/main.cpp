#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>  // include xml lib in .pro file like so     [QT += core gui xml]


// Function to convert XML text to JSON text
QString XML_2_JSON(QString xmlText) {
    QString temp; // Create a temporary QString to store the JSON data
    QTextStream jsonStream(&temp); // Create a QTextStream that writes to the QString temp
    QDomDocument doc;
    doc.setContent(xmlText); // Set the XML content for the QDomDocument

    QDomElement rootElement = doc.documentElement(); // Get the root element of the XML document
    jsonStream << "{\n\"" << rootElement.nodeName() << "\"\n"; // Start building the JSON string with the root element name

    // Call the WriteJSON function to convert XML to JSON recursively
    WriteJSON(rootElement, jsonStream);

    QString jsonText = jsonStream.readAll(); // Read the JSON text from the stream

    return jsonText; 
}


// Function to write XML data represented by a QDomNode to a JSON-like format
void WriteJSON(QDomNode& root, QTextStream& json) {
    QDomNode currentNode = root.firstChild(); // Start with the first child of the root node
    QDomElement currentElement;

    // Traverse through the XML nodes
    while (!currentNode.isNull()) {
        if (currentNode.isElement()) { // Check if the current node is an XML element
            currentElement = currentNode.toElement();

            // Check if the current element has child nodes and the first child is not text
            if (currentElement.hasChildNodes() && !currentElement.childNodes().at(0).isText()) {
                // Handle the case where there are multiple elements with the same name
                if (currentElement.nodeName() == currentElement.nextSibling().nodeName()) {
                    json << "\"" << currentElement.tagName() << "\": [\n{\n";
                } else { // Handle the case where there is a single child element
                    json << "\"" << currentElement.tagName() << "\": {\n";
                }
            } else if (currentElement.hasChildNodes() && currentElement.childNodes().at(0).isText() &&
                       currentElement.nodeName() != "corrupt") {
                // Handle the case where the element has text content (e.g., <node1>value</node1>)
                // or multiple text content children (e.g., <node1>value1</node1><node1>value2</node1>)
                if (currentElement.nodeName() == currentElement.nextSibling().nodeName()) {
                    json << "\"" << currentElement.nodeName() << "\": [\n";
                    QDomElement tempElement = currentElement;

                    // Print the text content of the current element and its siblings
                    json << "\"" << tempElement.text().trimmed() << "\"";
                    tempElement = tempElement.nextSiblingElement();
                    while (!tempElement.isNull()) {
                        json << ",\n\"" << tempElement.text().trimmed() << "\"";
                        tempElement.setTagName("corrupt"); // Mark it so when the reader reaches it -> skip it
                        tempElement = tempElement.nextSiblingElement();
                    }
                    json << "\n";
                } else { // Handle the case where there is a single text content child
                    QString tagName = currentElement.tagName();
                    QString innerData = currentElement.text().trimmed();
                    json << "\"" << tagName << "\": \"" << innerData << "\",\n";
                }
            }
        }

        // Recursively call the function for the child nodes
        WriteJSON(currentNode, json);
        currentNode = currentNode.nextSibling(); // Move to the next sibling node
    }
}
