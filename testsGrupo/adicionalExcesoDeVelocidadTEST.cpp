#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33, -34);
const double unaHora = 3600;

TEST(excesoDeVelocidadTEST, justo80){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 80*1000, 0))};
               //medicion(unaHora*2, desviarPunto(P, 2*1.5*80*1000, 0))};

    EXPECT_FALSE(excesoDeVelocidad(v));
}