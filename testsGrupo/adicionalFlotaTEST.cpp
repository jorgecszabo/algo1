#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;



viaje v = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
             medicion(T0+30, puntoGps(-34.591586, -58.401064)),
             medicion(T0+494, puntoGps(-34.563746, -58.436637)),
             medicion(T0+999, puntoGps(-34.549657, -58.437327)),
             medicion(T0+92, puntoGps(-34.594553, -58.402426)),
             medicion(T0+65, puntoGps(-34.590787, -58.402222)),
             medicion(T0+230, puntoGps(-34.584572, -58.416942)),
             medicion(T0+873, puntoGps(-34.559236, -58.427499)),
             medicion(T0+675, puntoGps(-34.578941, -58.424878)),
             medicion(T0+1051, puntoGps(-34.545704, -58.441383))};


vector<viaje> viajes = {v};
TEST(flotaTotalTEST, todosEnTiempo){
    EXPECT_EQ(flota(viajes,T0,T0+1051),1);
}

TEST(flotaTotalTEST, algunosFueraDeRango){
    EXPECT_EQ(flota(viajes, T0-50,T0-1),0);
}
