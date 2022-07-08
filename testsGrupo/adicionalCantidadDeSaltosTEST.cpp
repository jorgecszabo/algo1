#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(cantidadDeSaltosTEST, dosSaltosLatitud){
    grilla g = construirGrilla(puntoGps(0.0,0.0),desviarPunto(puntoGps(0,0), -3000, 3000), 6, 6);

    //guardarGrillaEnArchivo(g,"grilla1.csv");
    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, -1100, 250);
    gps p3 = desviarPunto(p2, -100, 2000);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

TEST(cantidadDeSaltosTEST, saltoLongitud){
    grilla g = construirGrilla(puntoGps(0.0,0.0),desviarPunto(puntoGps(0,0), -3000, 3000), 6, 6);

    //guardarGrillaEnArchivo(g,"grilla.csv");
    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, -100, 250);
    gps p3 = desviarPunto(p2, -100, 1250);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),1);
}

TEST(cantidadDeSaltosTEST, saltoEnDiagonal){
    grilla g = construirGrilla(puntoGps(0.0,0.0),desviarPunto(puntoGps(0,0), -3000, 3000), 6, 6);

    //guardarGrillaEnArchivo(g,"grilla.csv");
    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, -1100, 2500);
    gps p3 = desviarPunto(p2, -100, 100);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),1);
}

TEST(cantidadDeSaltosTEST, saltoEnDiagonalDesordenado){
    grilla g = construirGrilla(puntoGps(0.0,0.0),desviarPunto(puntoGps(0,0), -3000, 3000), 6, 6);

    //guardarGrillaEnArchivo(g,"grilla.csv");
    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, -1100, 2500);
    gps p3 = desviarPunto(p2, -100, 100);

    viaje v = {medicion(1.7, p3),
               medicion(1.6, p2),
               medicion(1.5, p1)};

    EXPECT_EQ(cantidadDeSaltos(g,v),1);
}

TEST(cantidadDeSaltosTEST, noHaySaltos){
    grilla g = construirGrilla(puntoGps(0.0,0.0),desviarPunto(puntoGps(0,0), -3000, 3000), 6, 6);

    //guardarGrillaEnArchivo(g,"grilla.csv");
    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, -150, 250);
    gps p3 = desviarPunto(p2, -100, 200);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),0);
}