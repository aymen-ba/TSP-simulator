#ifndef GRAPH_H
#define GRAPH_H

#include <QtGui>
#include <QGraphicsView>
#include "edge.h"
class Vertex;

class Graph : public QGraphicsView
{
    // Q_OBJECT

private:

    void addEdge(Vertex *source, Vertex *dest);         // agrega un arco entre dos vertices
    QGraphicsScene *Scene;
    unsigned int nVertex;
    QVector <Vertex*> V;
    QList<Edge*> EdgesPainted;

public:

    // Construsctor del grafo al que se le pasa la escena a la que pertenece y la cantidad de vertices
    Graph(QGraphicsScene *scene,int n);
    ~Graph();                                           // Destructor
    QRectF boundingRect() const;                        // limites del grafo
    unsigned int getNVertex() const;                    // retorna la cantidad de vertices
    void addVertex(QGraphicsScene *scene);              // agrega los vertices a la escena en posiciones aleatorias
    void allocateEdges();                               // partiendo de los vertices  asigna los arcos
    QVector <Vertex*> getVector() const {return V;}     // retorna el vector que contiene todos los vertices
    void drawPath(QVector<unsigned int> array);         // dibuja el camino camino de menor costo dado el vector con dicho camino


};

#endif // GRAPH_H
