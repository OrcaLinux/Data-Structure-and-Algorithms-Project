#include "Graph.h"

Graph::Graph(int vertices, const QList<QString>& ids)
    : numVertices(vertices), vertexIds(ids) {
    // Initialize the adjacency list with empty QLists
    adjacencyList.resize(numVertices);
}

void Graph::addEdge(QString source, QString destination) {
    // Find the index of source and destination vertices
    auto sourceIndex = vertexIds.indexOf(source);
    auto destIndex = vertexIds.indexOf(destination);

    // Check if both source and destination vertices exist
    if (sourceIndex != -1 && destIndex != -1) {
        // Add an edge from source to destination
        adjacencyList[sourceIndex].append(destination);
    } else {
        std::cerr << "Error: Source or destination vertex not found." << std::endl;
    }
}

void Graph::setAdjacencyListForVertex(QString vertexId, const QList<QString>& adjacency) {
    auto vertexIndex = vertexIds.indexOf(vertexId);

    // Check if the vertex exists
    if (vertexIndex != -1) {
        // Set the adjacency list for the specific vertex
        adjacencyList[vertexIndex] = adjacency;
    } else {
        std::cerr << "Error: Vertex not found." << std::endl;
    }
}

void Graph::printGraph() {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Vertex " << vertexIds[i].toStdString() << " --> ";
        for (const auto& neighbor : adjacencyList[i]) {
            std::cout << neighbor.toStdString() << " ";
        }
        std::cout << std::endl;
    }
}
