#ifndef EJERCITORESISTIVO_H
#define EJERCITORESISTIVO_H

#include <Arduino.h>

class EjercitoResistivo {
private:
    float resSuperior;
    float resInferior;
    float factorMultiplicador;
    float factorNominal;

public:
    EjercitoResistivo(float rSup = 33000.0f, float rInf = 10000.0f);
    
    float getFactor() const;
    void setFactor(float nuevoFactor);
    void resetFactorNominal();
    float aplicarDivisor(float voltajeMedido) const;
};

#endif