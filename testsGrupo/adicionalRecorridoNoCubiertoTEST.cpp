#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

template<typename T>
bool included(T elem, vector<T> container){
    for (int i = 0; i < container.size(); ++i) {
        if (container[i] == elem){return true;}
    }
    return false;
}

template<typename T>
void ASSERT_ELEMENTS(vector<T> container, vector<T> elems) {
    for(int i = 0; i < elems.size(); i++ ) {
        ASSERT_TRUE(included(elems[i], container));
    }

}

using namespace std;

const gps P = puntoGps(0, 0);
const recorrido R = {P,
                     desviarPunto(P, 1000, 0),
                     desviarPunto(P, 2000, 0),
                     desviarPunto(P, 3000, 0),
                     desviarPunto(P, 4000, 0),
                     desviarPunto(P, 5000, 0),
                     desviarPunto(P, 6000, 0),
                     desviarPunto(P, 7000, 0),
                     desviarPunto(P, 8000, 0),
                     desviarPunto(P, 9000, 0),
};

TEST(recorridoNoCubiertoTEST, viajeDesvioMenorUmbral){
    viaje v = {};
    vector<int> desvios(R.size(), 0);
    desvios[0] = 5;
    desvios[1] = 1;
    desvios[2] = -2;
    desvios[3] = -3;

    for(int i = 0; i < R.size(); i++){
        v.push_back(medicion(i, desviarPunto(R[i], 0, desvios[i])));
    }

    vector<gps> res = recorridoNoCubierto(v, R, 0.1);
    EXPECT_EQ(res.size(), 0);
    //ASSERT_ELEMENTS(res, {});

}

TEST(recorridoNoCubiertoTEST, viajeDesvioMayorIgualUmbral){
    viaje v = {};
    vector<int> desvios(R.size(), 0);
    desvios[0] = 100;
    desvios[1] = 99;
    desvios[2] = -210;
    desvios[3] = -387;

    for(int i = 0; i < R.size(); i++){
        v.push_back(medicion(i, desviarPunto(R[i], 0, desvios[i])));
    }

    vector<gps> res = recorridoNoCubierto(v, R, 0.1);
    EXPECT_EQ(res.size(), 3);
    ASSERT_ELEMENTS(res, {R[3], R[0], R[2]});

}
