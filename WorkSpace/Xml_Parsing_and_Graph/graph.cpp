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

QString Graph::findMostInfluentialUser() const {
    std::unordered_map<QString, int> followerCount;

    for (const auto& neighbors : adjacencyList) {
        for (const auto& follower : neighbors) {
            ++followerCount[follower];
        }
    }

    QString mostInfluentialUser;
    int maxFollowers = 0;

    for (const auto& entry : followerCount) {
        if (entry.second > maxFollowers) {
            mostInfluentialUser = entry.first;
            maxFollowers = entry.second;
        }
    }

    return mostInfluentialUser;
}

QString Graph::findMostActiveUser() const {
    QString mostActiveUser;
    int maxConnections = 0;

    for (int i = 0; i < numVertices; ++i) {
        if (adjacencyList[i].size() > maxConnections) {
            mostActiveUser = vertexIds[i];
            maxConnections = adjacencyList[i].size();
        }
    }

    return mostActiveUser;
}

QList<QString> Graph::findMutualFollowers(QString user1, QString user2) const {
    auto index1 = vertexIds.indexOf(user1);
    auto index2 = vertexIds.indexOf(user2);

    if (index1 != -1 && index2 != -1) {
        const QList<QString>& followers1 = adjacencyList[index1];
        const QList<QString>& followers2 = adjacencyList[index2];

        QList<QString> mutualFollowers;
        for (const auto& follower : followers1) {
            if (followers2.contains(follower)) {
                mutualFollowers.append(follower);
            }
        }

        return mutualFollowers;
    } else {
        std::cerr << "Error: One or both users not found." << std::endl;
        return QList<QString>();
    }
}

QList<QString> Graph::suggestUsersToFollow(QString userId) const {
    auto userIndex = vertexIds.indexOf(userId);

    if (userIndex != -1) {
        const QList<QString>& followers = adjacencyList[userIndex];
        QList<QString> suggestedUsers;

        for (const auto& follower : followers) {
            auto followerIndex = vertexIds.indexOf(follower);
            if (followerIndex != -1) {
                const QList<QString>& followersOfFollower = adjacencyList[followerIndex];
                for (const auto& suggestedUser : followersOfFollower) {
                    if (!followers.contains(suggestedUser) && suggestedUser != userId) {
                        suggestedUsers.append(suggestedUser);
                    }
                }
            }
        }

        return suggestedUsers;
    } else {
        std::cerr << "Error: User not found." << std::endl;
        return QList<QString>();
    }
}
