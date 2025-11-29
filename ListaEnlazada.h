#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <iostream>

using namespace std;

template <typename T>
struct NodoLista {
    T dato;         
    NodoLista* sig;  
    NodoLista(T d) {
        dato = d;
        sig = NULL; 
    }
};

template <typename T>
class ListaEnlazada {
public:
    NodoLista<T>* inicio; 
    int tamano;          

    ListaEnlazada() {
        inicio = NULL;
        tamano = 0;
    }

    void agregar(T dato) {

        NodoLista<T>* nuevo = new NodoLista<T>(dato);

        nuevo->sig = inicio;

        inicio = nuevo;
        
        tamano++;
    }

    bool vacia() {
        return inicio == NULL;
    }
    
    NodoLista<T>* getInicio() {
        return inicio;
    }
};

#endif
