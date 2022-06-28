#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

celda crearCelda(gps esq1, gps esq2, int n, int m) {
    nombre nombre = make_tuple(n, m);

    return make_tuple(
            esq1, esq2, nombre
    );
}

gps obtenerPosicion(tuple <tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple <tiempo, gps> medicion) {
    return get<0>(medicion);
}

double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

// devuelve la velocidad en km/h entre dos puntos de un viaje
double velocidadEnKPH(tuple <tiempo, gps> p0, tuple <tiempo, gps> p1) {
    double dist = distEnKM(obtenerPosicion(p0), obtenerPosicion(p1));
    double tiempoH = (
                             obtenerTiempo(p0) - obtenerTiempo(p1)
                     ) / 3600;

    return abs(dist / tiempoH);
}

double distanciaEntreCeldas(nombre a, nombre b) {
    return sqrt(
            pow((get<0>(a) - get<0>(b)), 2) +
            pow((get<1>(a) - get<1>(b)), 2)
    );
}

nombre puntoANombreCelda(gps x, grilla g) {
    nombre res;
    for (int i = 0; i < g.size(); ++i) {
        gps esq1 = get<0>(g[i]);
        gps esq2 = get<1>(g[i]);

        // ESTO:
        bool enRangoLatitud = obtenerLatitud(esq1) <= obtenerLatitud(x) && obtenerLatitud(x) < obtenerLatitud(esq2);
        bool enRangoLongitud =
                obtenerLongitud(esq1) < obtenerLongitud(x) && obtenerLongitud(x) <= obtenerLongitud(esq2);

        bool dentroCuadrante = enRangoLatitud && enRangoLongitud;

        if (dentroCuadrante) res = get<2>(g[i]);
    }
    return res;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud) {
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}


gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple <tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

void guardarGrillaEnArchivo(grilla g, string nombreArchivo) {
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for (int i = 0; i < g.size(); i++) {
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t"
               << esq1_lng << "\t"
               << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")"
               << endl;

    }
    myfile.close();

}

void guardarRecorridosEnArchivo(vector <recorrido> recorridos, string nombreArchivo) {
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for (int i = 0; i < recorridos.size(); i++) {
        for (int k = 0; k < recorridos[i].size(); k++) {
            lat = get<0>(recorridos[i][k]);
            lng = get<1>(recorridos[i][k]);

            myfile << i << "\t"
                   << lat << "\t"
                   << lng << endl;
        }
    }
    myfile.close();

}
