#ifndef SERIALLOGGER_H
#define SERIALLOGGER_H

#include <Arduino.h>
#include "Config.h"

class SerialLogger {
public:
    void chequearEImprimirEncabezado(SystemConfig &cfg);
    void loggearDatos(SystemConfig &cfg, float tiempo, 
                      float v_d1_m1, float v_d2_m1, float esc1_m1, float esc2_m1,
                      float v_d1_m2, float v_d2_m2, float esc1_m2, float esc2_m2,
                      float v_bus1, float i_ma1, float v_load1, float p_mw1,
                      float v_bus2, float i_ma2, float v_load2, float p_mw2,
                      float temp_rtc);
};

#endif