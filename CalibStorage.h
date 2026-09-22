#ifndef CALIBSTORAGE_H
#define CALIBSTORAGE_H

#include <Arduino.h>
#include "DS3231.h"
#include "MedidorADS.h"
#include "MedidorINA219.h"

// Integrity signature for version 0.9 PI: "PI09"
#define CALIB_MAGIC_WORD 0x50493039
#define EEPROM_BASE_ADDR 0

struct CalibRecord {
    uint32_t magic;
    
    // ADS Moderno (0x48) zero offsets
    float adsMod_d1_dir;
    float adsMod_d2_dir;
    float adsMod_d1_ej;
    float adsMod_d2_ej;

    // ADS Clásico (0x4A) zero offsets
    float adsClas_d1_dir;
    float adsClas_d2_dir;
    float adsClas_d1_ej;
    float adsClas_d2_ej;

    // INA219 1 (0x40 - Fixed Source) zero offsets
    float ina1_i;
    float ina1_vbus;
    float ina1_vshunt;

    // INA219 2 (0x41 - Free) zero offsets
    float ina2_i;
    float ina2_vbus;
    float ina2_vshunt;

    // Resistive divider scale factors (K)
    float k_adsMod_d1;
    float k_adsMod_d2;
    float k_adsClas_d1;
    float k_adsClas_d2;

    // INA219 current gain correction factors (K)
    float k_ina1_i;
    float k_ina2_i;

    uint16_t checksum;
};

class CalibStorage {
private:
    static uint16_t calcularChecksum(const CalibRecord &rec);

public:
    static bool cargar(DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);
    static void guardar(DS3231 &rtc, const MedidorADS &adsMod, const MedidorADS &adsClas, const MedidorINA219 &ina1, const MedidorINA219 &ina2);
    static void resetearEEPROM(DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2);
    static void imprimirCalibraciones(const MedidorADS &adsMod, const MedidorADS &adsClas, const MedidorINA219 &ina1, const MedidorINA219 &ina2);
};

#endif