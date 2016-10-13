#ifndef TSPGRAPH_H
#define TSPGRAPH_H

#include <QVector>
#include <QString>
#include <QList>
#include "vertex.h"

// Esta clase representa a un Grafo el cual es siempre completamente conexo y no dirigido.
class TSPGraph {

    private:

        struct Ciclo {
            unsigned int costo; // costo total (incluyendo conexion al nodo 0)
            QVector<unsigned int> camino; // Comienza y termina en el nodo 0 (implícito)
        };

        // Datos miembro
        unsigned int N; // Cantidad de nodos en el grafo
        unsigned int** Distancias; // Representa la matriz de distancias
        Ciclo CicloHamiltoniano;

        // Funciones privadas
        void CalcularCiclo();
        QList<QString> KeysDeCardinal(unsigned int s);
        void Keys(unsigned int s, QString key, unsigned int posI, QList<QString> & lista);


    public:

        // Constructor
        TSPGraph(unsigned int n, QVector<Vertex *> V);

        // Destructor
        ~TSPGraph();

        // Métodos observadores
        unsigned int distancia(unsigned int i, unsigned int j) const;
        unsigned int costoCiclo() const;
        QVector<unsigned int> recorrido() const;

};

#endif // TSPGRAPH_H
