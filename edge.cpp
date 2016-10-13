#include <QPainter>

 #include "edge.h"
 #include "vertex.h"
 #include <math.h>

 Edge::Edge(Vertex *sourceVertex, Vertex *destVertex, QString color)
 {
     this->color=color;
     setAcceptedMouseButtons(0);
     source = sourceVertex;
     dest = destVertex;
     source->addEdge(this);
     dest->addEdge(this);
     adjust();
 }

 Edge::~Edge()
 {

 }

 Vertex *Edge::sourceVertex() const
 {
     return source;
 }

 Vertex *Edge::destVertex() const
 {
     return dest;
 }

 void Edge::adjust()
 {
     if (!source || !dest)
         return;

     QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
     qreal length = line.length();

     prepareGeometryChange();

     if (length > qreal(20.)) {
         QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
         sourcePoint = line.p1() + edgeOffset;
         destPoint = line.p2() - edgeOffset;
     } else {
         sourcePoint = destPoint = line.p1();
     }
 }

 QRectF Edge::boundingRect() const
 {
     if (!source || !dest)
         return QRectF();

     qreal penWidth = 1;
     qreal extra = penWidth/ 2.0;
     return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),destPoint.y() - sourcePoint.y()))
         .normalized()
         .adjusted(-extra, -extra, extra, extra);
 }

 void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
 {
     if (!source || !dest)
         return;

     QLineF line(sourcePoint, destPoint);
     if (qFuzzyCompare(line.length(), qreal(0.)))
         return;
    this->lenght=line.length();
    QColor color;
    color.setNamedColor(this->color);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawLine(line);
    qreal x1 = (sourcePoint.x()+destPoint.x())/2;
    qreal y1 = (sourcePoint.y()+destPoint.y())/2;
    painter->setFont(QFont("Arial", 14, QFont::Bold));
    painter->drawText(QPointF(x1,y1), QString::number(lenght));     // Escribe en el su distancia
 }
