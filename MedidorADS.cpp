#include "MedidorADS.h"

MedidorADS::MedidorADS(uint8_t addr, EjercitoResistivo* divD1, EjercitoResistivo* divD2) {
    direccion = addr;
    ejercitoD1 = divD1;
    ejercitoD2 = divD2;
    usarEjercito = false;
    offset_D1_directo = 0.0f;
    offset_D2_directo = 0.0f;
    offset_D1_ejercito = 0.0f;
    offset_D2_ejercito = 0.0f;
}

void MedidorADS::init() {
    ads.begin(direccion);
}

bool MedidorADS::checkConnection() {
    Wire.beginTransmission(direccion);
    return (Wire.endTransmission() == 0);
}

void MedidorADS::setModoEjercito(bool activo) {
    usarEjercito = activo;
}

bool MedidorADS::getModoEjercito() const {
    return usarEjercito;
}

float MedidorADS::realizarConversionDiferencial(uint8_t canalDiferencial, float &escalaUsada) {
    ads.setGain(GAIN_TWOTHIRDS); 
    escalaUsada = 6.144f;
    int16_t adc = (canalDiferencial == 0) ? ads.readADC_Differential_0_1() : ads.readADC_Differential_2_3();
    float volts = ads.computeVolts(adc);

    // Autoranging downwards for maximum resolution
    if (abs(volts) < 4.090f) {
        ads.setGain(GAIN_ONE);
        escalaUsada = 4.096f;
        delay(2); // FIX I2C: Pequeño respiro al ADS
        adc = (canalDiferencial == 0) ? ads.readADC_Differential_0_1() : ads.readADC_Differential_2_3();
        volts = ads.computeVolts(adc);
        
        if (abs(volts) < 2.040f) {
            ads.setGain(GAIN_TWO);
            escalaUsada = 2.048f;
            delay(2); // FIX I2C: Pequeño respiro al ADS
            adc = (canalDiferencial == 0) ? ads.readADC_Differential_0_1() : ads.readADC_Differential_2_3();
            volts = ads.computeVolts(adc);
        }
    }

    return volts;
}

float MedidorADS::leerDiferencialAutorrango(uint8_t canalDiferencial, float &escalaUsada) {
    float volts = realizarConversionDiferencial(canalDiferencial, escalaUsada);

    if (usarEjercito) {
        if (canalDiferencial == 0) {
            float vEscalado = (ejercitoD1 != nullptr) ? ejercitoD1->aplicarDivisor(volts) : volts;
            return vEscalado - offset_D1_ejercito;
        } else {
            float vEscalado = (ejercitoD2 != nullptr) ? ejercitoD2->aplicarDivisor(volts) : volts;
            return vEscalado - offset_D2_ejercito;
        }
    } else {
        float offset = (canalDiferencial == 0) ? offset_D1_directo : offset_D2_directo;
        return volts - offset;
    }
}

void MedidorADS::calibrarCeroDirectoD1(uint8_t muestras) {
    float sum = 0.0f;
    float dummyEsc = 0.0f;
    for (uint8_t i = 0; i < muestras; i++) {
        sum += realizarConversionDiferencial(0, dummyEsc);
        delay(8);
    }
    offset_D1_directo = sum / (float)muestras;
}

void MedidorADS::calibrarCeroDirectoD2(uint8_t muestras) {
    float sum = 0.0f;
    float dummyEsc = 0.0f;
    for (uint8_t i = 0; i < muestras; i++) {
        sum += realizarConversionDiferencial(1, dummyEsc);
        delay(8);
    }
    offset_D2_directo = sum / (float)muestras;
}

void MedidorADS::calibrarCeroEjercitoD1(uint8_t muestras) {
    float sum = 0.0f;
    float dummyEsc = 0.0f;
    for (uint8_t i = 0; i < muestras; i++) {
        float v = realizarConversionDiferencial(0, dummyEsc);
        if (ejercitoD1 != nullptr) {
            v = ejercitoD1->aplicarDivisor(v);
        }
        sum += v;
        delay(8);
    }
    offset_D1_ejercito = sum / (float)muestras;
}

void MedidorADS::calibrarCeroEjercitoD2(uint8_t muestras) {
    float sum = 0.0f;
    float dummyEsc = 0.0f;
    for (uint8_t i = 0; i < muestras; i++) {
        float v = realizarConversionDiferencial(1, dummyEsc);
        if (ejercitoD2 != nullptr) {
            v = ejercitoD2->aplicarDivisor(v);
        }
        sum += v;
        delay(8);
    }
    offset_D2_ejercito = sum / (float)muestras;
}

void MedidorADS::resetOffsets() {
    offset_D1_directo = 0.0f;
    offset_D2_directo = 0.0f;
    offset_D1_ejercito = 0.0f;
    offset_D2_ejercito = 0.0f;
}

void MedidorADS::setOffsets(float d1_dir, float d2_dir, float d1_ej, float d2_ej) {
    offset_D1_directo = d1_dir;
    offset_D2_directo = d2_dir;
    offset_D1_ejercito = d1_ej;
    offset_D2_ejercito = d2_ej;
}

void MedidorADS::setFactoresK(float k_d1, float k_d2) {
    if (ejercitoD1 != nullptr) ejercitoD1->setFactor(k_d1);
    if (ejercitoD2 != nullptr) ejercitoD2->setFactor(k_d2);
}

float MedidorADS::getFactorK_D1() const {
    return (ejercitoD1 != nullptr) ? ejercitoD1->getFactor() : 1.0f;
}

float MedidorADS::getFactorK_D2() const {
    return (ejercitoD2 != nullptr) ? ejercitoD2->getFactor() : 1.0f;
}