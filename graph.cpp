#include "graph.h"
#include "vertex.h"
#include <QtGui>

Graph::Graph(QGraphicsScene *scene, int n)
{
    this->Scene=scene;
    this->nVertex=n;
}

Graph::~Graph()
{

}

QRectF Graph::boundingRect() const
{
    return QRectF(0,0,100,100);
}

unsigned int Graph::getNVertex() const
{
    return nVertex;
}

void Graph::addVertex(QGraphicsScene *scene)
{
    for(unsigned int i=0; i<nVertex; i++)
    {
        QString id = QString::number(i);
        Vertex * v=new Vertex(id);
        V.append(v);
        V.at(i)->setPos(qrand()%300,qrand()%300);
        scene->addItem(v);
    }
}

void Graph::allocateEdges()
{
    for(unsigned int i=0; i<nVertex; i++)
    {
        for(unsigned int j=0; j<nVertex; j++)
        {
            if(j!=i)
                addEdge(V.at(i), V.at(j));
        }
    }
}

void Graph::drawPath(QVector<unsigned int> array)
{
    foreach (Edge* a, EdgesPainted)
        Scene->removeItem(a);

    EdgesPainted.clear();

    QString color = "blue";

    Edge * a = new Edge(V.at(0),V.at(array.at(0)),color);
    Scene->addItem(a);
    EdgesPainted.append(a);
    for(int i=1 ; i<array.size(); i++) {
        Edge* e = new Edge(V.at(array.at(i-1)),V.at(array.at(i)),color);
        Scene->addItem(e);
        EdgesPainted.append(e);
    }
    a = new Edge(V.at(array.last()),V.at(0),color);
    Scene->addItem(a);
    EdgesPainted.append(a);
}

void Graph::addEdge(Vertex *source, Vertex *dest)
{
    QString color= "black";
    Scene->addItem(new Edge(source, dest,color));
}
