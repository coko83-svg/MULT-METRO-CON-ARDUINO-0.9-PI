#include "EjercitoResistivo.h"

EjercitoResistivo::EjercitoResistivo(float rSup, float rInf) {
    resSuperior = rSup;
    resInferior = rInf;
    // Nominal theoretical multiplication factor: (R1 + R2) / R2
    if (resInferior > 0.0f) {
        factorNominal = (resSuperior + resInferior) / resInferior;
    } else {
        factorNominal = 1.0f;
    }
    factorMultiplicador = factorNominal;
}

float EjercitoResistivo::getFactor() const {
    return factorMultiplicador;
}

void EjercitoResistivo::setFactor(float nuevoFactor) {
    if (nuevoFactor > 0.0001f) {
        factorMultiplicador = nuevoFactor;
    }
}

void EjercitoResistivo::resetFactorNominal() {
    factorMultiplicador = factorNominal;
}

float EjercitoResistivo::aplicarDivisor(float voltajeMedido) const {
    return voltajeMedido * factorMultiplicador;
}