#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>


#include "ListaEnlazada.h"
#include "Pila.h"
#include "Cola.h"
#include "TablaHash.h"
#include "ArbolBinario.h"
#include "Matriz.h"
#include "Grafo.h"

using namespace std;

const int FILAS = 20;
const int COLS = 25;

/* LEYENDA:
   # = Pared      M = Monstruo
   . = Camino     K = Llave
   E = Entrada    D = Puerta
   S = Salida     P = Pocion
*/

char nivel[FILAS][COLS] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'E','.','.','.','#','.','.','.','.','#','.','#','P','#','.','.','.','.','.','#','.','.','.','.','#'},
    {'#','#','#','.','#','.','#','.','#','.','#','M','.','.','#','#','#','.','#','.','#','#','#','.','#'},
    {'#','.','M','.','.','.','#','.','.','.','#','.','.','.','#','K','#','.','.','.','#','.','#','.','#'},
    {'#','.','#','#','#','#','#','#','#','.','#','#','.','#','#','M','#','#','#','#','#','.','#','.','#'},
    {'#','.','.','.','#','.','.','.','.','.','.','.','M','.','.','.','.','.','.','.','.','.','#','.','#'},
    {'#','#','#','.','#','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','#','.','#'},
    {'#','P','#','.','M','.','#','.','.','.','.','.','.','M','.','.','.','.','.','.','#','.','#','.','#'},
    {'#','.','#','#','#','#','#','.','#','#','#','#','#','#','#','#','#','#','#','.','#','.','#','.','#'},
    {'#','.','.','.','M','.','.','.','#','.','.','.','.','.','.','.','.','.','#','.','#','.','#','.','#'},
    {'#','#','#','#','#','#','#','.','#','.','#','#','#','#','#','#','#','.','#','.','#','.','#','.','#'},
    {'#','.','.','.','.','.','#','.','#','.','#','P','#','.','.','.','.','.','#','.','.','.','#','.','#'},
    {'#','.','#','#','#','.','#','.','#','.','#','M','#','.','#','#','#','#','#','#','#','#','#','.','#'},
    {'#','.','#','.','.','.','#','.','#','.','.','.','#','.','.','.','M','.','.','.','.','.','.','.','#'},
    {'#','.','#','.','#','#','#','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','#'},
    {'#','.','#','.','#','M','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','.','#'},
    {'#','.','#','.','#','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','#','.','#'},
    {'#','.','.','.','#','.','.','.','M','.','.','M','.','.','.','#','M','.','.','.','.','.','D','S','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};

struct Coord {
    int x, y;
};

struct Jugador {
    int x, y;
    int vida;
    TablaHash mochila; 
};



void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//Logica del juego 

void dibujar(Matriz<char>& m) {
    for(int i=0; i<FILAS; i++) {
        for(int j=0; j<COLS; j++) {
            gotoxy(j*2 + 2, i+2);
            char c = m.get(i, j); // Uso de la estructura Matriz
            
            // Colores según el elemento
            if(c == '#') color(8);      // Gris oscuro
            else if(c == '.') color(7); // Gris claro
            else if(c == 'M') color(12);// Rojo
            else if(c == 'P') color(13);// Magenta
            else if(c == 'K') color(14);// Amarillo
            else if(c == 'S') color(10);// Verde
            else if(c == 'E') color(10);// Verde
            else if(c == 'D') color(4); // Rojo oscuro (Puerta)
            
            cout << c;
        }
    }
}

void hud(Jugador& p, string msg) {
    int posX = COLS*2 + 5; 
    
    color(14);
    gotoxy(posX, 5); cout << "Vida: " << p.vida << "   ";
    gotoxy(posX, 6); cout << "Pos: " << p.x << "," << p.y << "   ";
    
    color(11);
    gotoxy(posX, 8); cout << "Ultimo evento:";
    gotoxy(posX, 9); cout << "                                    "; 
    gotoxy(posX, 9); cout << msg;
}

void mostrarInventario(Jugador& p) {
    system("cls");
    color(15);
    cout << "=== MOCHILA (Tabla Hash) ===\n\n";
    p.mochila.mostrar(); 
    cout << "\nPresiona tecla para volver...";
    getch();
    system("cls");
    
    int posX = COLS*2 + 5;
    gotoxy(posX, 2); cout << "CONTROLES: W A S D";
    gotoxy(posX, 3); cout << "Z: Deshacer | I: Mochila";
}


void combate(Jugador& p, Cola<string>& turnos) {
    hud(p, "¡MONSTRUO SALVAJE!");

    turnos.encolar("Jugador");
    turnos.encolar("Monstruo");
    
    int posX = COLS*2 + 5;

    while(!turnos.vacia() && p.vida > 0) {
        string actual = turnos.desencolar();
        gotoxy(posX, 11); cout << "Turno: " << actual << "      ";
        
        if(actual == "Jugador") {
            gotoxy(posX, 12); cout << "Atacas! (Enter)      ";
            getch();
        } else {
            gotoxy(posX, 12); cout << "Te atacan! (Enter)   ";
            getch();
            
            p.vida -= 40; 
            
            hud(p, "¡GOLPE FUERTE! -40 HP");
            if(p.vida > 0) turnos.encolar("Jugador");
        }
    }

    gotoxy(posX, 11); cout << "                     ";
    gotoxy(posX, 12); cout << "                     ";
}

int main() {

    Matriz<char> mapa(FILAS, COLS); 
    Pila<Coord> historia;           
    Cola<string> colaPelea;         
    Grafo grafoSalas;               
    
    Jugador p1;
    p1.vida = 100;

    for(int i=0; i<FILAS; i++) {
        for(int j=0; j<COLS; j++) {
            mapa.set(i, j, nivel[i][j]);
            if(nivel[i][j] == 'E') {
                p1.x = j;
                p1.y = i;
            }
            grafoSalas.agregarNodo("Sala"); 
        }
    }

    system("cls");
    color(15);
    gotoxy(2, 0); cout << "AVENTURA EN EL LABERINTO - ZONA DE GUERRA";
    
    int posX = COLS*2 + 5;
    gotoxy(posX, 2); cout << "CONTROLES: W A S D";
    gotoxy(posX, 3); cout << "Z: Deshacer | I: Mochila";

    dibujar(mapa);
    hud(p1, "¡Sobrevive a la horda!");

    char tecla;
    bool jugando = true;

    while(jugando && p1.vida > 0) {
        gotoxy(p1.x*2 + 2, p1.y + 2);
        color(15); cout << "@";
        gotoxy(0, FILAS + 3); 

        tecla = getch();
        
        Coord ant; ant.x = p1.x; ant.y = p1.y;
        
        int dx = 0, dy = 0;
        if(tecla=='w' || tecla=='W') dy = -1;
        if(tecla=='s' || tecla=='S') dy = 1;
        if(tecla=='a' || tecla=='A') dx = -1;
        if(tecla=='d' || tecla=='D') dx = 1;
        
        if(tecla=='i' || tecla=='I') {
            mostrarInventario(p1);
            dibujar(mapa); 
            hud(p1, "Mochila cerrada");
        }

        if(tecla=='z' || tecla=='Z') {
            if(!historia.vacia()) {
                gotoxy(p1.x*2 + 2, p1.y + 2);
                char piso = mapa.get(p1.y, p1.x);
                if(piso=='#') color(8); else color(7);
                cout << piso;

                Coord reg = historia.pop();
                p1.x = reg.x;
                p1.y = reg.y;
                hud(p1, "Deshacer movimiento");
            }
        }
        
        if(tecla=='q') jugando = false;

        if(dx != 0 || dy != 0) {
            int nx = p1.x + dx;
            int ny = p1.y + dy;

            if(mapa.esValido(ny, nx)) {
                char celda = mapa.get(ny, nx);
                
                if(celda == '#') {
                    hud(p1, "Pared");
                }
                else if(celda == 'D') {
                    Item key = p1.mochila.buscar("LLAVE");
                    if(key.nombre != "NULO") {
                        historia.push(ant);
                        
                        // Visual
                        gotoxy(p1.x*2 + 2, p1.y + 2); cout << '.';
                        p1.x = nx; p1.y = ny;
                        mapa.set(ny, nx, '.');
                        hud(p1, "¡Puerta abierta!");
                        dibujar(mapa);
                    } else {
                        hud(p1, "Necesitas la LLAVE (K)");
                    }
                }
                else {
                    historia.push(ant); 
                    
                    // Visual
                    gotoxy(p1.x*2 + 2, p1.y + 2);
                    color(7); cout << ".";
                    p1.x = nx; p1.y = ny;
                    
                    if(celda == 'S') {
                        hud(p1, "¡ESCAPASTE CON VIDA!");
                        Sleep(2000);
                        jugando = false;
                    }
                    else if(celda == 'M') {
                        combate(p1, colaPelea);
                        if(p1.vida > 0) {
                            mapa.set(ny, nx, '.'); 
                            dibujar(mapa);
                        }
                    }
                    else if(celda == 'P') {
                        p1.vida += 50; 
                        if(p1.vida > 100) p1.vida = 100;
                        mapa.set(ny, nx, '.');
                        p1.mochila.guardar("POCION", Item("Pocion", "Cura", 50));
                        hud(p1, "Pocion: +50 Vida");
                    }
                    else if(celda == 'K') {
                        p1.mochila.guardar("LLAVE", Item("Llave", "Abre puerta", 0));
                        mapa.set(ny, nx, '.');
                        hud(p1, "¡TIENES LA LLAVE!");
                    }
                    else {
                        hud(p1, "...");
                    }
                }
            }
        }
    }
    
    system("cls");
    gotoxy(10, 10);
    if(p1.vida <= 0) {
        color(12); cout << "GAME OVER - Fuiste devorado.";
    } else {
        color(10); cout << "¡VICTORIA! Eres una leyenda.";
    }
    cout << "\n\n";
    system("pause");
    return 0;
}
