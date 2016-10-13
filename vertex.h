#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class Graph;
class QGraphicsSceneMouseEvent;

class Vertex : public QGraphicsItem
{

private:

    QList<Edge *> edgeList;
    QString id;

    // funciones privadas
    QRectF boundingRect() const;                                // define los limites de dibujo del vertice
    QVariant itemChange(GraphicsItemChange change, const QVariant &value); // mantiene actualizado el cambio de posicion del vertice
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      // cuando se clickea un vertice cambia de color
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);    // cuando se suelta el click en un vertice cambia de color
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // dibuja al vertice

public:

    Vertex(QString id);                                         // Constructor al que se le pasa un ID para identificar el vertice
    ~Vertex();                                                  // Destructor
    void addEdge(Edge *edge);                                   // Agrega un arco al vertice
    QString getID() const;                                      // retorna el ID del vertice
    QList <Edge*> getEdges() const {return edgeList;}           // Mantiene una lista de los arcos a los que esta asociado el vertice
};
#endif // VERTEX_H
