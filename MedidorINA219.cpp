#include "MedidorINA219.h"

MedidorINA219::MedidorINA219(uint8_t addr) : ina(addr) {
    direccion = addr;
    offset_corriente = 0.0f;
    offset_vbus = 0.0f;
    offset_vshunt = 0.0f;
    factor_escala_corriente = 1.0000f;
}

void MedidorINA219::init() {
    ina.begin();
}

bool MedidorINA219::checkConnection() {
    Wire.beginTransmission(direccion);
    return (Wire.endTransmission() == 0);
}

float MedidorINA219::leerVoltajeBus() {
    float v = ina.getBusVoltage_V() - offset_vbus;
    return (v < 0.0f && v > -0.0005f) ? 0.0f : v;
}

float MedidorINA219::leerVoltajeShunt() {
    return ina.getShuntVoltage_mV() - offset_vshunt;
}

float MedidorINA219::leerCorriente() {
    float i = (ina.getCurrent_mA() - offset_corriente) * factor_escala_corriente;
    return (abs(i) < 0.0005f) ? 0.0f : i;
}

float MedidorINA219::leerPotencia() {
    float v = leerVoltajeBus();
    float i = abs(leerCorriente());
    return v * i;
}

void MedidorINA219::calibrarCeroCorriente(uint8_t muestras) {
    float sumI = 0.0f;
    float sumVshunt = 0.0f;
    for (uint8_t k = 0; k < muestras; k++) {
        sumI += ina.getCurrent_mA();
        sumVshunt += ina.getShuntVoltage_mV();
        delay(8);
    }
    offset_corriente = sumI / (float)muestras;
    offset_vshunt = sumVshunt / (float)muestras;
}

void MedidorINA219::calibrarCeroVBus(uint8_t muestras) {
    float sumVbus = 0.0f;
    for (uint8_t k = 0; k < muestras; k++) {
        sumVbus += ina.getBusVoltage_V();
        delay(8);
    }
    offset_vbus = sumVbus / (float)muestras;
}

void MedidorINA219::resetOffsets() {
    offset_corriente = 0.0f;
    offset_vbus = 0.0f;
    offset_vshunt = 0.0f;
    factor_escala_corriente = 1.0000f;
}

void MedidorINA219::setOffsets(float i, float vbus, float vshunt) {
    offset_corriente = i;
    offset_vbus = vbus;
    offset_vshunt = vshunt;
}

void MedidorINA219::setFactorK_I(float k) {
    if (k > 0.0001f) {
        factor_escala_corriente = k;
    }
}