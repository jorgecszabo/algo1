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
        if (obtenerTiempo(v[i]) > tiempoMaximo) { //3
            tiempoMaximo = obtenerTiempo(v[i]);
        } else {//3
            if (obtenerTiempo(v[i]) < tiempoMinimo) //3
                tiempoMinimo = obtenerTiempo(v[i]);
        }//3
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
    bool hayExceso = false;
    insertionSort(v);
    for (int i = 1; i < v.size(); ++i) {
        if(velocidadEnKPH(v[i-1], v[i]) > 80.0) hayExceso = true;
    }

    return hayExceso;
}

/************************************ EJERCICIO recorridoNoCubierto *******************************/
// n -> Longitud del viaje | m -> longitud del recorrido
bool cubierto(gps p, viaje &v, distancia &u) {
    bool estaCubierto = false;
    for (int i = 0; i < v.size(); i++) {
        if (distEnKM(obtenerPosicion(v[i]), p) < u)
            estaCubierto = true;
    }
    return estaCubierto;
}

vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    for (int i = 0; i < r.size(); i++) { //2 + 3 + m(3 + 1)
        if(!cubierto(r[i], v, u)) //c1 * n
            resp.push_back(r[i]); //2
    }
    return resp; //1
} //t(n,m) = 6 + m(6 + c1 * n) = 6 + 6m + c1*m + m*n -> O(n*m)

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    for (int i = 0; i < f.size(); i++) {
        for (int j = 0; j < f[i].size(); j++) {
            tiempo tiempoActual = obtenerTiempo(f[i][j]);
            if (tiempoActual <= tf && tiempoActual >= t0) {
                resp++;
                break;
            }
        }
    }
    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/
/*
 * En este ejercicio usamos el tipo de dato long double porque de caso contrario el test fallaba a la hora
 * de comparar la grilla computada con un resultado conocido debido a lo que suponemos es un error de
 * redondeo. Para esta aplicación es un desperdicio de memoria.
 */

grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    long double altoCelda = (obtenerLatitud(esq1) - obtenerLatitud(esq2)) / n;
    long double anchoCelda = (obtenerLongitud(esq2) - obtenerLongitud(esq1)) / m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            long double latEsq1Celda = obtenerLatitud(esq1) - (altoCelda * (i-1));
            long double lonEsq1Celda = obtenerLongitud(esq1) + (anchoCelda * (j-1));
            long double latEsq2Celda = latEsq1Celda - altoCelda;
            long double lonEsq2Celda = lonEsq1Celda + anchoCelda;

            celda celdaActual = crearCelda(
                    puntoGps(latEsq1Celda, lonEsq1Celda),
                    puntoGps(latEsq2Celda, lonEsq2Celda),
                    i, j
                    );
            resp.push_back(celdaActual);

        }
    }
    //guardarGrillaEnArchivo(resp, "grilla.csv");
    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp = 0;
    insertionSort(v);

    for (int i = 1; i < v.size(); ++i) {

        nombre celdaPrimerPunto = puntoANombreCelda(obtenerPosicion(v[i - 1]), g);
        nombre celdaSegundoPunto = puntoANombreCelda(obtenerPosicion(v[i]), g);

        double distancia = distanciaEntreCeldas(celdaPrimerPunto, celdaSegundoPunto);

        if (distancia > 1) resp++;
    }

    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/
bool esPuntoErroneo(vector<tiempo> &errores, tiempo t) {
    for (int i = 0; i < errores.size(); i++) {
        if (errores[i] == t)
            return true;
    }
    return false;
}

int maximo(vector<double> v) {
    int max = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > v[max])
            max = i;
    }
    return max;
}

tuple<int, int, int> losDosPuntosMasCercanos(viaje &v,vector<tiempo> &errores,  tiempo t) { //Devuelve los índices de viaje con los dos puntos más cercanos
    vector<distancia> dist(v.size());
    int indice_viaje = -1;
    for (int i = 0; i < v.size(); i++) {
         if (obtenerTiempo(v[i]) == t) {
             indice_viaje = i;
             break;
         }
    }
    vector<tiempo> tiempos(v.size());

    for (int i = 0; i < v.size(); i++) {
        if (!esPuntoErroneo(errores, obtenerTiempo(v[i]))) {
            tiempos[i] = abs(obtenerTiempo(v[i]) - t);
        } else {
            tiempos[i] = 0;
        }
    }

    int min1 = maximo(tiempos); //Esto hay que hacerlo por si el primer elemento de viaje es un punto erróneo
    int min2 = min1;

    for (int i = 0; i < tiempos.size() ; i++) {
        if (tiempos[i] <= tiempos[min1] && tiempos[i] != 0) {
            min2 = min1;
            min1 = i;
        } else if (tiempos[i] <= tiempos[min2] && tiempos[i] != tiempos[min1] && tiempos[i] != 0)
            min2 = i;
    }
    return {indice_viaje ,min1, min2};
}

gps corregirPunto(viaje &v, int indice_p, int indice_q, tiempo t) {
    gps p = obtenerPosicion(v[indice_p]);
    gps q = obtenerPosicion(v[indice_q]);

    if (obtenerLatitud(p) > obtenerLatitud(q)) { //para mantener la misma relación entre los puntos de entrada
        swap(p,q);
        swap(indice_p, indice_q);
    }

    tiempo tiempo_p = obtenerTiempo(v[indice_p]);
    tiempo tiempo_q = obtenerTiempo(v[indice_q]);

    //el punto corregido debe estar en una recta de la forma y = mx + c (y -> long punto corregido, x -> lat punto corregido)
    if (obtenerLatitud(p) != obtenerLatitud(q)) {
        double m = (obtenerLongitud(p) - obtenerLongitud(q))/(obtenerLatitud(p) - obtenerLatitud(q));
        double c = (obtenerLongitud(q) * obtenerLatitud(p) - obtenerLongitud(p) * obtenerLatitud(q))/(obtenerLatitud(p) - obtenerLatitud(q));
        double latPorSegundo = (obtenerLatitud(p) - obtenerLatitud(q))/(tiempo_p - tiempo_q);
        double latAprox = obtenerLatitud(p) + latPorSegundo * abs(tiempo_p - t);
        double longAprox = m * latAprox + c;
        return {latAprox, longAprox};

    } else { //caso latitudes iguales para evitar dividir por cero
            double longPorSegundo = (obtenerLongitud(p) - obtenerLongitud(q))/abs(tiempo_p - tiempo_q);
            double longAprox = obtenerLongitud(p) - longPorSegundo * abs(tiempo_p - t);
            return {obtenerLatitud(p), longAprox};
    }
}

void corregirViaje(viaje& v, vector<tiempo> errores){
    for (int i = 0; i < errores.size(); i++) {
        tuple<int, int, int> puntosCercanos = losDosPuntosMasCercanos(v, errores, errores[i]);
        int indice_viaje = get<0>(puntosCercanos);
        int indice_p = get<1>(puntosCercanos);
        int indice_q = get<2>(puntosCercanos);

        //cout << indice_viaje << indice_p << indice_q << endl;
        gps punto = corregirPunto(v, indice_p, indice_q, errores[i]);
        //cout << obtenerLatitud(punto) << " - " << obtenerLongitud(punto) << endl;
        v[indice_viaje] = {errores[i], punto};
    }
}
