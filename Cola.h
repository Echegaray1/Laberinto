#ifndef COLA_H
#define COLA_H
#include <iostream>

using namespace std;

template <typename T>
struct NodoCola {
    T dato;
    NodoCola* sig;
    
    NodoCola(T d) {
        dato = d;
        sig = NULL;
    }
};

template <typename T>
class Cola {
private:
    NodoCola<T>* frente; 
    NodoCola<T>* final;  

public:
    Cola() {
        frente = NULL;
        final = NULL;
    }

    void encolar(T dato) {
        NodoCola<T>* nuevo = new NodoCola<T>(dato);

        if(frente == NULL) {
            frente = nuevo;
            final = nuevo; 
        } else {
            
            final->sig = nuevo;
            final = nuevo;      
        }
    }

    T desencolar() {
        if(frente == NULL) return T(); 

        NodoCola<T>* aux = frente;
        T valor = aux->dato;

        frente = frente->sig;

        if(frente == NULL) final = NULL;

        delete aux; 
        
        return valor;
    }

    bool vacia() {
        return frente == NULL;
    }
};

#endif
