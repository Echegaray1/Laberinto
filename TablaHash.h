#ifndef TABLAHASH_H
#define TABLAHASH_H
#include <iostream>
#include <string>

using namespace std;

 
struct Item {
    string nombre;
    string desc;
    int valor; 

    Item(string n="", string d="", int v=0) {
        nombre = n;
        desc = d;
        valor = v;
    }
};

struct NodoHash {
    string clave;     
    Item item;        
    NodoHash* sig;   

    NodoHash(string k, Item i) {
        clave = k;
        item = i;
        sig = NULL;
    }
};

class TablaHash {
private:
    NodoHash** tabla; 
    int capacidad;  

    int hash(string clave) {
        int suma = 0;
        for(int i=0; i<clave.length(); i++) {
            suma += clave[i]; 
        }
        return suma % capacidad; 
    }

public:

    TablaHash(int cap=10) {
        capacidad = cap;
        tabla = new NodoHash*[capacidad]; 
        for(int i=0; i<capacidad; i++) tabla[i] = NULL;
    }


    void guardar(string clave, Item item) {
 
        int indice = hash(clave);
        
        NodoHash* nuevo = new NodoHash(clave, item);
        
        if(tabla[indice] == NULL) {
            tabla[indice] = nuevo;
        } else {
            nuevo->sig = tabla[indice];
            tabla[indice] = nuevo;
        }
    }

    Item buscar(string clave) {

        int indice = hash(clave);

        NodoHash* actual = tabla[indice];
        
        while(actual != NULL) {
            if(actual->clave == clave) {
                return actual->item; 
            }
            actual = actual->sig; 
        }
        
        return Item("NULO", "", 0);
    }
    
    void mostrar() {
        for(int i=0; i<capacidad; i++) {
            NodoHash* aux = tabla[i];
            if(aux != NULL) {
                cout << " [" << i << "]: ";
                while(aux != NULL) {
                    cout << aux->item.nombre << " | ";
                    aux = aux->sig;
                }
                cout << endl;
            }
        }
    }
};

#endif
