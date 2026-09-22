#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <Arduino.h>
#include "Config.h"
#include "MedidorADS.h"
#include "MedidorINA219.h"
#include "CalibStorage.h"
#include "DS3231.h"

enum MenuState {
    MSTATE_CONFIG_SELECCION_MODULOS,
    MSTATE_CONFIG_ADS_MODERNO,
    MSTATE_CONFIG_ADS_CLASICO,
    MSTATE_IDLE,
    MSTATE_MENU_CALIBRACION,
    MSTATE_CONFIRMAR_CALIBRACION_CERO,
    MSTATE_INGRESAR_FACTOR_K,
    MSTATE_MENU_PLOTTER,
    MSTATE_INGRESAR_COTA_INF,
    MSTATE_INGRESAR_COTA_SUP
};

enum CalibAccion {
    CALIB_NINGUNA = 0,
    // ADS Moderno Zero Calibrations
    CALIB_ZERO_ADS_MOD_D1_DIR,
    CALIB_ZERO_ADS_MOD_D2_DIR,
    CALIB_ZERO_ADS_MOD_D1_EJ,
    CALIB_ZERO_ADS_MOD_D2_EJ,
    // ADS Clásico Zero Calibrations
    CALIB_ZERO_ADS_CLAS_D1_DIR,
    CALIB_ZERO_ADS_CLAS_D2_DIR,
    CALIB_ZERO_ADS_CLAS_D1_EJ,
    CALIB_ZERO_ADS_CLAS_D2_EJ,
    // INA219 Zero Calibrations
    CALIB_ZERO_INA1_CORRIENTE,
    CALIB_ZERO_INA1_VBUS,
    CALIB_ZERO_INA2_CORRIENTE,
    CALIB_ZERO_INA2_VBUS,
    // Scale Factors (K)
    CALIB_FACTOR_K_MOD_D1,
    CALIB_FACTOR_K_MOD_D2,
    CALIB_FACTOR_K_CLAS_D1,
    CALIB_FACTOR_K_CLAS_D2,
    CALIB_FACTOR_K_INA1_I,
    CALIB_FACTOR_K_INA2_I
};

class MenuController {
private:
    MenuState estadoActual;
    CalibAccion accionPendiente;
    char bufferEntrada[32];
    uint8_t bufferIdx;

    void escanearHardware(SystemConfig &cfg, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);
    void imprimirMenuSeleccionModulos(SystemConfig &cfg);
    void imprimirMenuADSModerno(SystemConfig &cfg);
    void imprimirMenuADSClasico(SystemConfig &cfg);
    void imprimirMenuPrincipal(SystemConfig &cfg);
    void imprimirMenuCalibracion();
    void imprimirMenuPlotter(SystemConfig &cfg);

    void mostrarInstruccionesCero(CalibAccion accion);
    void mostrarInstruccionesFactorK(CalibAccion accion, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);
    void ejecutarCalibracionCero(CalibAccion accion, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);
    void aplicarFactorK(CalibAccion accion, float valor, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);

    bool validarHardware(SystemConfig &cfg, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);

public:
    MenuController();
    void iniciarConfiguracion(SystemConfig &cfg, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);
    void procesarMenu(SystemConfig &cfg, bool &midiendo, unsigned long &tiempoInicio, 
                      DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);
};

#endif