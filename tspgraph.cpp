#include "tspgraph.h"
#include <QHash>
#include "edge.h"

// CONSTRUCTOR
TSPGraph::TSPGraph(unsigned int n, QVector<Vertex*> V) {

    // Inicia cantidad de nodos
    N = n;

    // Inicia matriz de distancias
    // Solo pide memoria para la mitad de la matriz
    Distancias = new unsigned int* [n-1];
    for (unsigned int i = 0; i<(n-1) ; i++) {

        Distancias[i] = new unsigned int[i+1];
        for (unsigned int j = 0 ; j<(i+1) ; j++)

            foreach(Edge *e, V.at(i+1)->getEdges())

                if(QString::compare(e->destVertex()->getID(),V.at(j)->getID())==0) {
                    Distancias[i][j] = e->getLenght();
                    break;
                }
    }


    // Se carga CicloHamiltoniano
    if (n<=1)
        CicloHamiltoniano.costo = 0;
    else
        CalcularCiclo();
}


// DESTRUCTOR
TSPGraph::~TSPGraph() {
    for (unsigned int i = 0 ; i < (N-1) ; i++) {
        delete [] Distancias[i];
    }
    delete [] Distancias;
}


// MÉTODOS OBSERVADORES
unsigned int TSPGraph::costoCiclo() const {
    return CicloHamiltoniano.costo;
}

QVector<unsigned int> TSPGraph::recorrido() const {
    return CicloHamiltoniano.camino;
}

unsigned int TSPGraph::distancia(unsigned int i, unsigned int j) const {

    if (i==j)
        return 0;
    else if (i<j)
        return Distancias[j-1][i];
    else
        return Distancias[i-1][j];

    // La primer coordenada de la matriz Distancias menos uno, representa al vertice en cuestión
    // Es decir, para el vertice "i", la coordenada sería "i-1"
}


// FUNCIONES PRIVADAS
void TSPGraph::Keys(unsigned int s, QString key, unsigned int posI, QList<QString> &lista) {
// Funcion auxiliar que completa el funcionamiento de "TSPGraph::KeysDeCardinal(s)"
    if (s==0)
        lista.append(key);
    else
        for (unsigned int i = posI ; i <= N-s ; i++)
            Keys(s-1,key+QString::number(i),i+1,lista);
}

QList<QString> TSPGraph::KeysDeCardinal(unsigned int s) {
// Devuelve una lista con todas las posibles keys de longitud s-1
// que toma valores en {1,...,N-1} y están ordenadas ascendentemente
// No hay repeticion y no importa el orden (es decir la key = "1234" sería equivalente
// a "4231" sin embargo se retornan las keys ordenadas ascendentemente)

    QList<QString> lista;

    if (s==N) {
        QString key = "";
        for (unsigned int i = 1 ; i < N ; i++)
            key = key + QString::number(i);
        lista.append(key);
    }

    else
        Keys(s-1,"",1,lista);

    return lista;
}

void TSPGraph::CalcularCiclo() {

    QHash<QString,Ciclo> tabla;
    // La key del tipo QString posee los nodos por los que ya pasó ese "Ciclo" => Describe el conjunto S
    // La key se encuentra siempre en orden creciente (no describe el recorrido) y no incluye el 0 (el nodo 0 está siempre incluido implicitamente)
    // El valor Ciclo, llevará el "recorrido", y el "costo" de hacer dicho recorrido en ese orden


    // Calculo los caminos para |S| = 2
    for (unsigned int k = 1; k < N ; k++) {
        QString key = QString::number(k);
        Ciclo ciclo;
        ciclo.costo = distancia(0,k);
        ciclo.camino.append(k);
        tabla.insert(key,ciclo);
    }

    // Calculo los caminos para |S| > 2
    for (unsigned int s = 3; s <= N ; s++) {

        // Genero una lista de las keys que representan a cada uno de los subconjuntos incluidos en {0,..,N-1} de cardinal s
        QList<QString> Claves = KeysDeCardinal(s);
        // Para todo S includio en {0,1,...,N-1} y |S| == s
        foreach (QString key, Claves) {

            // Busco el camino mínimo para la key, probando finalizar el recorrido en cada uno de los nodos de key

            // Cargo tabla[key] finalizando el camino en el nodo key[0]
            QString key2 = key;
            key2.remove(0,1); // remove( posicion_inicial, cantidad_de_char_a_remover_desde_la_posicion_inicial)
            Ciclo ciclo;
            ciclo.costo = tabla[key2].costo + distancia((unsigned int)key[0].digitValue(),tabla[key2].camino.last());
            ciclo.camino = tabla[key2].camino;
            ciclo.camino.append((unsigned int)key[0].digitValue());
            tabla.insert(key,ciclo);

            // Por cada vertice que pertenece a S (es decir, cada vertice que aparece en la key)
            for (int i = 1 ; i < key.length() ; i++ ) {
                QString key2 = key;
                key2.remove(i,1);
                Ciclo ciclo;
                ciclo.costo = tabla[key2].costo + distancia((unsigned int)key[i].digitValue(), tabla[key2].camino.last());

                // Si el costo nuevo calculado que pasa por los mismos vertices es menor, lo guardo..
                if (ciclo.costo < tabla[key].costo){
                    ciclo.camino = tabla[key2].camino;
                    ciclo.camino.append((unsigned int)key[i].digitValue());
                    tabla.insert(key,ciclo);
                }
            }
        }
    }

    // Genero la key que representa al conjunto de vertices completo S == V
    QString keyV = "";
    for (unsigned int i = 1 ; i < N ; i++)
        keyV = keyV + QString::number(i);

    // Cierro el ciclo y guardo el resultado
    CicloHamiltoniano.costo = tabla[keyV].costo + distancia(tabla[keyV].camino.last(),0);
    CicloHamiltoniano.camino = tabla[keyV].camino;
}
