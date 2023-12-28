#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <QList>
#include <QString>

class Graph {
private:
    int numVertices;
    QList<QList<QString>> adjacencyList;
    QList<QString> vertexIds;

public:
    Graph(int vertices, const QList<QString>& ids);

    void addEdge(QString source, QString destination);

    void setAdjacencyListForVertex(QString vertexId, const QList<QString>& adjacency);

    void printGraph();
};

#endif // GRAPH_H
