#ifndef MEDIDORINA219_H
#define MEDIDORINA219_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

class MedidorINA219 {
private:
    Adafruit_INA219 ina;
    uint8_t direccion;

    // Independent zero offsets
    float offset_corriente;
    float offset_vbus;
    float offset_vshunt;

    // Current measurement gain correction factor (nominal 1.0000)
    float factor_escala_corriente;

public:
    MedidorINA219(uint8_t addr);
    
    void init();
    bool checkConnection();
    
    float leerVoltajeBus();
    float leerVoltajeShunt();
    float leerCorriente();
    float leerPotencia();

    void calibrarCeroCorriente(uint8_t muestras = 32);
    void calibrarCeroVBus(uint8_t muestras = 32);
    void resetOffsets();

    void setOffsets(float i, float vbus, float vshunt);
    void setFactorK_I(float k);

    float getOffsetCorriente() const { return offset_corriente; }
    float getOffsetVBus() const { return offset_vbus; }
    float getOffsetVShunt() const { return offset_vshunt; }
    float getFactorK_I() const { return factor_escala_corriente; }
};

#endif