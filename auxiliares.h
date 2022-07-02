#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"
#include "string"

double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
celda crearCelda(gps esq1, gps esq2, int n, int m);
double distanciaEntreCeldas(nombre a, nombre b);
nombre puntoANombreCelda(gps x, grilla g);
double velocidadEnKPH(tuple<tiempo, gps> p0, tuple<tiempo, gps> p1);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);
bool valorCercano(double x, double y, double delta);
bool grillaIgual(grilla& grilla1, grilla& grilla2);

void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo);

#endif //TRANSPORTEURBANO_AUXILIARES_H
