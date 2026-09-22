#ifndef MEDIDORADS_H
#define MEDIDORADS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include "EjercitoResistivo.h"

class MedidorADS {
private:
    Adafruit_ADS1115 ads;
    uint8_t direccion;
    
    // Dedicated resistive dividers for independent channels D1 and D2
    EjercitoResistivo* ejercitoD1;
    EjercitoResistivo* ejercitoD2;
    bool usarEjercito;

    // Fully decoupled zero offsets
    float offset_D1_directo;
    float offset_D2_directo;
    float offset_D1_ejercito;
    float offset_D2_ejercito;

    float realizarConversionDiferencial(uint8_t canalDiferencial, float &escalaUsada);

public:
    MedidorADS(uint8_t addr, EjercitoResistivo* divD1, EjercitoResistivo* divD2);
    
    void init();
    bool checkConnection();
    
    void setModoEjercito(bool activo);
    bool getModoEjercito() const;
    
    float leerDiferencialAutorrango(uint8_t canalDiferencial, float &escalaUsada);
    
    // Decoupled zero calibration per channel
    void calibrarCeroDirectoD1(uint8_t muestras = 32);
    void calibrarCeroDirectoD2(uint8_t muestras = 32);
    void calibrarCeroEjercitoD1(uint8_t muestras = 32);
    void calibrarCeroEjercitoD2(uint8_t muestras = 32);
    void resetOffsets();

    // EEPROM persistence and factor management
    void setOffsets(float d1_dir, float d2_dir, float d1_ej, float d2_ej);
    void setFactoresK(float k_d1, float k_d2);

    float getOffsetD1Directo() const { return offset_D1_directo; }
    float getOffsetD2Directo() const { return offset_D2_directo; }
    float getOffsetD1Ejercito() const { return offset_D1_ejercito; }
    float getOffsetD2Ejercito() const { return offset_D2_ejercito; }
    
    float getFactorK_D1() const;
    float getFactorK_D2() const;
};

#endif