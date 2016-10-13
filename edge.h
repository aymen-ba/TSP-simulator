#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Vertex;

class Edge : public QGraphicsItem {

    private:

        Vertex *source, *dest;
        QPointF sourcePoint;
        QPointF destPoint;
        unsigned int lenght;
        QString color;

        // funciones privadas
        QRectF boundingRect() const;                                    // define los limites de donde se dibujara el arco
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // dibuja el arco

    public:

        // Constructor al que se le pasa el vertice de origen y destino, ademas asignando un color al arco
        Edge(Vertex *sourceVertex, Vertex *destVertex, QString color);
        ~Edge();                                                        // Destructor
        Vertex *sourceVertex() const;                                   // Retorna el vertice de origen
        Vertex *destVertex() const;                                     // Retorna el vertice de destino
        void adjust();                                                  // ajusta la longitud del arco cuando un vértice es arrastrado
        unsigned int getLenght() const { return lenght; }               // retorna la longitud del arco


};

#endif // EDGE_H
