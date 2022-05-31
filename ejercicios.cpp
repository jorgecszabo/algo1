#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo tiempoMinimo = obtenerTiempo(v[0]);  //3
    tiempo tiempoMaximo = obtenerTiempo(v[0]);  //3
    for (int i = 0; i < v.size(); i++) {    //1 + n(2 + 1)
        if (obtenerTiempo(v[i]) > tiempoMaximo) //3
            tiempoMaximo = obtenerTiempo(v[i]); //3
        if (obtenerTiempo(v[i]) < tiempoMinimo) //3
            tiempoMinimo = obtenerTiempo(v[i]); //3
    } //t_ciclo(n) = 1 + 2 + n(3*5) = 15n + 3
    tiempo t = tiempoMaximo - tiempoMinimo; //2
    return t;
} //t(n) = 15n + 3 + 3 + 3 + 2 = 15n + 11 --> O(n)

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
//insertionSort implementado en base a la teórica 9.
void insert (viaje &v, int i) {
    while (i > 0 && obtenerTiempo(v[i]) < obtenerTiempo(v[i-1])) { //2 + 2 + 1 + 2 = 7
        swap(v[i], v[i-1]); //3
        i--; //1
    } //t(n) = 7 + n(7 + 3 + 1) = 11n + 7
} //t_insert(n) = 11n + 7

void insertionSort(viaje &v) {
    for (int i = 0; i < v.size(); i++) { //1 + 3 + 1
        insert(v, i); //11n + 7 + 2
    } //t(n) = 1 + 3 + n(3 + 1 + 11n + 9) = 4 + 11n^2 + 13 n --> O(n^2)
}

distancia distanciaTotal(viaje v) {
    distancia d = 0; //1
    insertionSort(v); //1 + c1 * n^2
    for (int i = 1; i < v.size(); i++) { // 1 + 4 + 1
        d += distEnKM(obtenerPosicion(v[i - 1]), obtenerPosicion(v[i])); // 2 + 2 + 2
    } //t(n) = 1 + 4 + n(4 + 1 + 6) = 5 + 11n

    return d; //1
} //t_distanciaTotal(n) = 1 + 1 + c1*n^2 + 5 + 11n + 1 = 8 + c1 * n^2 + 11n --> O(n^2), n = v.size()

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    // codigo

    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    // codigo

    return resp;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp;
    // codigo

    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    // codigo

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp;
    // codigo

    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig

    return;
}