#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(corregirViajeTEST, igualLatitud){
    viaje v = {medicion(T0+0, puntoGps(-64.21297, -31.46503)),
               medicion(T0+120, puntoGps(-12, 12)),
               medicion(T0+240, puntoGps(-64.21297, -31.44705)),
               medicion(T0+310, puntoGps(-64.21297, -31.43705)),
               medicion(T0+390, puntoGps(-64.21297, -31.42705)),
               medicion(T0+444, puntoGps(-64.21297, -31.41705)),
    };

    viaje res = {medicion(T0+0, puntoGps(-64.21297, -31.46503)),
                 medicion(T0+120, puntoGps(-64.21297, -31.45604)),
                 medicion(T0+240, puntoGps(-64.21297, -31.44705)),
                 medicion(T0+310, puntoGps(-64.21297, -31.43705)),
                 medicion(T0+390, puntoGps(-64.21297, -31.42705)),
                 medicion(T0+444, puntoGps(-64.21297, -31.41705)),
    };

    vector<tiempo> errores = {T0+120};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, igualLatitudInv){
    viaje v = {medicion(T0+240, puntoGps(-64.21297, -31.46503)),
               medicion(T0+120, puntoGps(-12, 12)),
               medicion(T0+0, puntoGps(-64.21297, -31.44705)),
               medicion(T0+310, puntoGps(-64.21297, -31.43705)),
               medicion(T0+390, puntoGps(-64.21297, -31.42705)),
               medicion(T0+444, puntoGps(-64.21297, -31.41705)),
    };

    viaje res = {medicion(T0+240, puntoGps(-64.21297, -31.46503)),
                 medicion(T0+120, puntoGps(-64.21297, -31.45604)),
                 medicion(T0+0, puntoGps(-64.21297, -31.44705)),
                 medicion(T0+310, puntoGps(-64.21297, -31.43705)),
                 medicion(T0+390, puntoGps(-64.21297, -31.42705)),
                 medicion(T0+444, puntoGps(-64.21297, -31.41705)),
    };

    vector<tiempo> errores = {T0+120};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, faltaElUltimoOtraParteDelMundo){
    viaje v = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
               medicion(T0+30, puntoGps(-34.591586, -58.401064)),
               medicion(T0+494, puntoGps(-34.563746, -58.436637)),
               medicion(T0+999, puntoGps(-34.549657, -58.437327)),
               medicion(T0+92, puntoGps(-34.594553, -58.402426)),
               medicion(T0+65, puntoGps(-34.590787, -58.402222)),
               medicion(T0+230, puntoGps(-34.584572, -58.416942)),
               medicion(T0+873, puntoGps(-34.559236, -58.427499)),
               medicion(T0+675, puntoGps(-34.578941, -58.424878)),
               medicion(T0+1051, puntoGps(0, 0))};

    viaje res = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
                 medicion(T0+30, puntoGps(-34.591586, -58.401064)),
                 medicion(T0+494, puntoGps(-34.563746, -58.436637)),
                 medicion(T0+999, puntoGps(-34.549657, -58.437327)),
                 medicion(T0+92, puntoGps(-34.594553, -58.402426)),
                 medicion(T0+65, puntoGps(-34.590787, -58.402222)),
                 medicion(T0+230, puntoGps(-34.584572, -58.416942)),
                 medicion(T0+873, puntoGps(-34.559236, -58.427499)),
                 medicion(T0+675, puntoGps(-34.578941, -58.424878)),
                 medicion(T0+1051, puntoGps(-34.545704, -58.441383))};
    vector<tiempo> errores = {T0+1051};

    //nos mudamos al otro hemisferio!

    for (int i = 0; i < v.size(); i++) {
        v[i] = {get<0>(v[i]), {-1 * get<0>(get<1>(v[i])), -1 * get<1>(get<1>(v[i]))}};
        res[i] = {get<0>(res[i]), {-1 * get<0>(get<1>(res[i])), -1 * get<1>(get<1>(res[i]))}};
    }

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, igualLatitudInvOtraParteDelMundo){
    viaje v = {medicion(T0+240, puntoGps(-64.21297, -31.46503)),
               medicion(T0+120, puntoGps(-12, 12)),
               medicion(T0+0, puntoGps(-64.21297, -31.44705)),
               medicion(T0+310, puntoGps(-64.21297, -31.43705)),
               medicion(T0+390, puntoGps(-64.21297, -31.42705)),
               medicion(T0+444, puntoGps(-64.21297, -31.41705)),
    };

    viaje res = {medicion(T0+240, puntoGps(-64.21297, -31.46503)),
                 medicion(T0+120, puntoGps(-64.21297, -31.45604)),
                 medicion(T0+0, puntoGps(-64.21297, -31.44705)),
                 medicion(T0+310, puntoGps(-64.21297, -31.43705)),
                 medicion(T0+390, puntoGps(-64.21297, -31.42705)),
                 medicion(T0+444, puntoGps(-64.21297, -31.41705)),
    };

    vector<tiempo> errores = {T0+120};

    //nos mudamos al otro hemisferio!

    for (int i = 0; i < v.size(); i++) {
        v[i] = {get<0>(v[i]), {-1 * get<0>(get<1>(v[i])), -1 * get<1>(get<1>(v[i]))}};
        res[i] = {get<0>(res[i]), {-1 * get<0>(get<1>(res[i])), -1 * get<1>(get<1>(res[i]))}};
    }

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, igualLatitudOtraParteDelMundo){
    viaje v = {medicion(T0+0, puntoGps(-64.21297, -31.46503)),
               medicion(T0+120, puntoGps(-12, 12)),
               medicion(T0+240, puntoGps(-64.21297, -31.44705)),
               medicion(T0+310, puntoGps(-64.21297, -31.43705)),
               medicion(T0+390, puntoGps(-64.21297, -31.42705)),
               medicion(T0+444, puntoGps(-64.21297, -31.41705)),
    };

    viaje res = {medicion(T0+0, puntoGps(-64.21297, -31.46503)),
                 medicion(T0+120, puntoGps(-64.21297, -31.45604)),
                 medicion(T0+240, puntoGps(-64.21297, -31.44705)),
                 medicion(T0+310, puntoGps(-64.21297, -31.43705)),
                 medicion(T0+390, puntoGps(-64.21297, -31.42705)),
                 medicion(T0+444, puntoGps(-64.21297, -31.41705)),
    };

    vector<tiempo> errores = {T0+120};

    //nos mudamos al otro hemisferio!

    for (int i = 0; i < v.size(); i++) {
        v[i] = {get<0>(v[i]), {-1 * get<0>(get<1>(v[i])), -1 * get<1>(get<1>(v[i]))}};
        res[i] = {get<0>(res[i]), {-1 * get<0>(get<1>(res[i])), -1 * get<1>(get<1>(res[i]))}};
    }

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}