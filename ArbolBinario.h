#ifndef ARBOLBINARIO_H 
#define ARBOLBINARIO_H

#include <iostream>

using namespace std;

template <typename T>
struct NodoArbol {
    T dato;            
    NodoArbol* izq;     
    NodoArbol* der;     
    NodoArbol(T d) {
        dato = d;
        izq = NULL;
        der = NULL;
    }
};

template <typename T>
class ArbolBinario {
public:
	
    NodoArbol<T>* raiz; 
    ArbolBinario() {
        raiz = NULL;
    }

    bool vacio() {
        return raiz == NULL; 
    }
};

#endif
