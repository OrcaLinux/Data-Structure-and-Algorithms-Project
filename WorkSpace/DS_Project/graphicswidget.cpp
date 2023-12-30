#include "graphicswidget.h"
#include "edge.h"
#include "node.h"
#include "graph.h"
#include "xmlparser.h"

#include <math.h>
#include<vector>

#include <QKeyEvent>
#include <QRandomGenerator>

Node* getNodeByID(QList<Node*> graphNodes, int id){
    for(Node* node : graphNodes){
        if(node->getUniqueID() == id)
            return node;
    }
    return nullptr;
}

void drawNodes(Graph graph, QList<User*> nodes, GraphWidget *graphWidget, QGraphicsScene* scene){
    QList<Node*> graphNodes; // store all vertices
    QList<Edge*> graphEdges;
    // Store Vertices in list
    for(User* node : nodes){
        Node* v = new Node(graphWidget, node->getName(), node->getId().toInt());
        graphNodes.push_back(v);
    }
    // Store Edges in list
    int i = 0;
    for(Node* node : graphNodes){
        QList<QString> nodeFollowersList = graph.getAdjacencyList().at(i);
        // Connect nodes in graphNodes list
        for(QString id : nodeFollowersList){
            Node* adjacentNode = getNodeByID(graphNodes,id.toInt());
            graphEdges.push_back(new Edge(node, adjacentNode));
        }
        i++;
    }

    // Start Drawing
    int radius  = 400; // node radius = 20
    int graphNodesSize = graphNodes.size();
    for (int i = 0; i < graphNodesSize; ++i) {
        qreal angle = 2 * M_PI * i / graphNodesSize;
        qreal x = static_cast<int>(radius * std::cos(angle));
        qreal y = static_cast<int>(radius * std::sin(angle));

        Node* currentNode = graphNodes.first();
        scene->addItem(currentNode);
        graphNodes.pop_front();

        currentNode->setPos(x,y);
    }
    int graphEdgesSize = graphEdges.size();
    for(int i = 0; i < graphEdgesSize; ++i){
        scene->addItem(graphEdges.first());
        graphEdges.pop_front();
    }
}

//! [0]
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-400, -400, 800, 800);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(800, 800);
    setWindowTitle(tr("Elastic Nodes"));
    //! [0]

    //! [1]


    // Initialize Graph
    QString filePath = "C:\\Users\\User\\UniLabs\\Qt_DSA\\GraphVisualisation\\sample.xml";
    XMLparser *newParse = new XMLparser(filePath);
    if(newParse->isValidFile())
    {
        const QList <User*> users = newParse->parse();
        for(int i = 0; i < users.size();i++)
        {

            qInfo()<<users.at(i)->getId();
            qInfo() << users.at(i)->getName();

            for(int j = 0; j < users.at(i)->getPosts().size();j++)
            {
                qInfo() << (users.at(i)->getPosts()).at(j)->getBody();
                for(int k= 0; k < ((users.at(i)->getPosts()).at(j))->getTopics().size();k++ )
                    qInfo() <<  ((users.at(i)->getPosts()).at(j)->getTopics()).at(k);

            }
            for(int l = 0; l< users.at(i)->getFollowersId().size();l++)
                qInfo() << (users.at(i)->getFollowersId()).at(l);
        }
        QList<QString> ids;
        for(int j = 0; j < users.size();j++){
            ids.push_back(users.at(j)->getId());
        }
/////////////////
        Graph graph(users.size(),ids);
        QList<QString> followers;
        for(int j = 0; j <users.size();j++){

            followers = users.at(j)->getFollowersId();
            graph.setAdjacencyListForVertex(users.at(j)->getId(),followers);

        }
        drawNodes(graph, users, this, scene);
////////////////

        std::cout<<std::endl;
        graph.printGraph();
        QString mostInfluential = graph.findMostInfluentialUser();
        std::cout<<std::endl<< "Most Influential User "<< mostInfluential.toStdString();
        QString MostActiveUser = graph.findMostActiveUser();
        std::cout<<std::endl<< "Most Active User "<< MostActiveUser.toStdString();
        QList<QString> MutualFollowers;
        MutualFollowers = graph.findMutualFollowers("3","2");
        for(int j = 0; j <MutualFollowers.size();j++){
            std::cout<<std::endl<< "MutualFollowers: "<< MutualFollowers.at(j).toStdString()<<" "<<std::endl;
        }
        QList<QString> SuggestFollowers;
        SuggestFollowers = graph.suggestUsersToFollow("2");
        for(int j = 0; j <SuggestFollowers.size();j++){
            std::cout<<std::endl<< "SuggestFollowers: "<< SuggestFollowers.at(j).toStdString()<<" "<<std::endl;
        }

    }
    else
    {
        delete newParse;
    }

}
//! [1]

//! [2]
void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}
//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    for (Node *node : std::as_const(nodes))
        node->calculateForces();

    bool itemsMoved = false;
    for (Node *node : std::as_const(nodes)) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

#if QT_CONFIG(wheelevent)
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., -event->angleDelta().y() / 240.0));
}
//! [5]
#endif

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void GraphWidget::shuffle()
{
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}



