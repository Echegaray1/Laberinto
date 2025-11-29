#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>

using namespace std;

template <typename T>
class Matriz {
private:

    T** datos;
    int filas, cols;

public:

    Matriz(int f, int c) {
        filas = f;
        cols = c;
        
        datos = new T*[filas];
        
        for(int i=0; i<filas; i++) {
            datos[i] = new T[cols];
        }
    }

    void set(int f, int c, T valor) {

        if(f >= 0 && f < filas && c >= 0 && c < cols) {
            datos[f][c] = valor;
        }
    }

    T get(int f, int c) {

        if(f >= 0 && f < filas && c >= 0 && c < cols) {
            return datos[f][c];
        }
        return T(); 
    }

    bool esValido(int f, int c) {
        return (f >= 0 && f < filas && c >= 0 && c < cols);
    }
};

#endif 
