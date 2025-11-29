#ifndef PILA_H
#define PILA_H
#include <iostream>

using namespace std;

template <typename T>
struct NodoPila {
    T dato;
    NodoPila* abajo; 
    
    NodoPila(T d) {
        dato = d;
        abajo = NULL;
    }
};

template <typename T>
class Pila {
private:
    NodoPila<T>* tope; 

public:
    Pila() {
        tope = NULL;
    }

    void push(T dato) {

        NodoPila<T>* nuevo = new NodoPila<T>(dato);

        nuevo->abajo = tope;

        tope = nuevo;
    }

    T pop() {
        if(tope == NULL) return T(); 
        
        NodoPila<T>* aux = tope;
        T valor = aux->dato;
        
        tope = tope->abajo;
        
        delete aux;
        
        return valor;
    }

    bool vacia() {
        return tope == NULL;
    }
};

#endif
