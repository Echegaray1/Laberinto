#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <string>

#include "ListaEnlazada.h" 

using namespace std;

struct Vertice {
    string nombre; 
    ListaEnlazada<Vertice*> vecinos;
    Vertice(string n) {
        nombre = n;
    }
};

class Grafo {
private:

    ListaEnlazada<Vertice*> vertices;

public:
    Grafo() {}

    Vertice* agregarNodo(string nombre) {

        Vertice* nuevo = new Vertice(nombre);
        
        vertices.agregar(nuevo);
        return nuevo;
    }

    void conectar(string n1, string n2) {
    }
};

#endif
