#include "CalibStorage.h"

uint16_t CalibStorage::calcularChecksum(const CalibRecord &rec) {
    const uint8_t *p = (const uint8_t *)&rec;
    size_t len = sizeof(CalibRecord) - sizeof(uint16_t);
    uint16_t csum = 0xAA55;

    for (size_t i = 0; i < len; i++) {
        csum = (csum << 1) | (csum >> 15);
        csum ^= p[i];
    }
    return csum;
}

bool CalibStorage::cargar(DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    if (!rtc.checkConnection()) {
        Serial.println(F(">> [EEPROM] Módulo DS3231 no detectado. Se aplican valores nominales (0.0 / K=1)."));
        adsMod.setFactoresK(4.3000f, 4.3000f);
        adsClas.setFactoresK(4.3000f, 4.3000f);
        ina1.setFactorK_I(1.0000f);
        ina2.setFactorK_I(1.0000f);
        return false;
    }

    CalibRecord rec;
    rtc.leerEEPROM(EEPROM_BASE_ADDR, (uint8_t*)&rec, sizeof(CalibRecord));

    if (rec.magic != CALIB_MAGIC_WORD) {
        Serial.println(F(">> [EEPROM] No se encontró calibración v0.9 PI válida. Se aplican valores nominales."));
        adsMod.setFactoresK(4.3000f, 4.3000f);
        adsClas.setFactoresK(4.3000f, 4.3000f);
        ina1.setFactorK_I(1.0000f);
        ina2.setFactorK_I(1.0000f);
        return false;
    }

    uint16_t csumEsperado = calcularChecksum(rec);
    if (rec.checksum != csumEsperado) {
        Serial.println(F(">> [EEPROM] Error de Checksum en memoria no volátil. Se aplican valores nominales."));
        return false;
    }

    adsMod.setOffsets(rec.adsMod_d1_dir, rec.adsMod_d2_dir, rec.adsMod_d1_ej, rec.adsMod_d2_ej);
    adsClas.setOffsets(rec.adsClas_d1_dir, rec.adsClas_d2_dir, rec.adsClas_d1_ej, rec.adsClas_d2_ej);
    ina1.setOffsets(rec.ina1_i, rec.ina1_vbus, rec.ina1_vshunt);
    ina2.setOffsets(rec.ina2_i, rec.ina2_vbus, rec.ina2_vshunt);

    adsMod.setFactoresK(rec.k_adsMod_d1, rec.k_adsMod_d2);
    adsClas.setFactoresK(rec.k_adsClas_d1, rec.k_adsClas_d2);
    ina1.setFactorK_I(rec.k_ina1_i);
    ina2.setFactorK_I(rec.k_ina2_i);

    Serial.println(F(">> [EEPROM] Calibraciones (Offsets y K) recuperadas con éxito desde módulo externo DS3231."));
    return true;
}

void CalibStorage::guardar(DS3231 &rtc, const MedidorADS &adsMod, const MedidorADS &adsClas, const MedidorINA219 &ina1, const MedidorINA219 &ina2) {
    if (!rtc.checkConnection()) {
        Serial.println(F(">> [EEPROM] ERROR: Módulo DS3231 no detectado. No se pueden guardar los datos."));
        return;
    }

    CalibRecord rec;
    
    // FIX EEPROM: Poner a cero toda la estructura (incluyendo bytes de relleno/padding) 
    // para evitar que la basura de la RAM arruine el cálculo del Checksum cíclico.
    memset(&rec, 0, sizeof(CalibRecord));
    
    rec.magic = CALIB_MAGIC_WORD;

    rec.adsMod_d1_dir = adsMod.getOffsetD1Directo();
    rec.adsMod_d2_dir = adsMod.getOffsetD2Directo();
    rec.adsMod_d1_ej  = adsMod.getOffsetD1Ejercito();
    rec.adsMod_d2_ej  = adsMod.getOffsetD2Ejercito();

    rec.adsClas_d1_dir = adsClas.getOffsetD1Directo();
    rec.adsClas_d2_dir = adsClas.getOffsetD2Directo();
    rec.adsClas_d1_ej  = adsClas.getOffsetD1Ejercito();
    rec.adsClas_d2_ej  = adsClas.getOffsetD2Ejercito();

    rec.ina1_i      = ina1.getOffsetCorriente();
    rec.ina1_vbus   = ina1.getOffsetVBus();
    rec.ina1_vshunt = ina1.getOffsetVShunt();

    rec.ina2_i      = ina2.getOffsetCorriente();
    rec.ina2_vbus   = ina2.getOffsetVBus();
    rec.ina2_vshunt = ina2.getOffsetVShunt();

    rec.k_adsMod_d1  = adsMod.getFactorK_D1();
    rec.k_adsMod_d2  = adsMod.getFactorK_D2();
    rec.k_adsClas_d1 = adsClas.getFactorK_D1();
    rec.k_adsClas_d2 = adsClas.getFactorK_D2();

    rec.k_ina1_i = ina1.getFactorK_I();
    rec.k_ina2_i = ina2.getFactorK_I();

    rec.checksum = calcularChecksum(rec);

    rtc.escribirEEPROM(EEPROM_BASE_ADDR, (const uint8_t*)&rec, sizeof(CalibRecord));
    Serial.println(F(">> [EEPROM] Registro de calibración salvado permanentemente en memoria externa I2C."));
}

void CalibStorage::resetearEEPROM(DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    adsMod.resetOffsets();
    adsClas.resetOffsets();
    ina1.resetOffsets();
    ina2.resetOffsets();

    adsMod.setFactoresK(4.3000f, 4.3000f);
    adsClas.setFactoresK(4.3000f, 4.3000f);
    ina1.setFactorK_I(1.0000f);
    ina2.setFactorK_I(1.0000f);

    guardar(rtc, adsMod, adsClas, ina1, ina2);
    Serial.println(F(">> [EEPROM] Calibraciones restauradas a valores de fábrica (0.0000 / K nominales)."));
}

void CalibStorage::imprimirCalibraciones(const MedidorADS &adsMod, const MedidorADS &adsClas, const MedidorINA219 &ina1, const MedidorINA219 &ina2) {
    Serial.println(F("\n========================================================="));
    Serial.println(F("       ESTADO METROLÓGICO Y CALIBRACIONES (v0.9 PI)      "));
    Serial.println(F("========================================================="));
    Serial.println(F("[ADS1115 Moderno 0x48]"));
    Serial.print(F("  5V Directo : D1 = ")); Serial.print(adsMod.getOffsetD1Directo(), 4);
    Serial.print(F(" V | D2 = ")); Serial.print(adsMod.getOffsetD2Directo(), 4); Serial.println(F(" V"));
    Serial.print(F("  Divisor 01 : D1 = ")); Serial.print(adsMod.getOffsetD1Ejercito(), 4);
    Serial.print(F(" V | D2 = ")); Serial.print(adsMod.getOffsetD2Ejercito(), 4); Serial.println(F(" V"));
    Serial.print(F("  Factores K : K_D1 = ")); Serial.print(adsMod.getFactorK_D1(), 4);
    Serial.print(F(" | K_D2 = ")); Serial.println(adsMod.getFactorK_D2(), 4);

    Serial.println(F("\n[ADS1115 Clásico 0x4A]"));
    Serial.print(F("  5V Directo : D1 = ")); Serial.print(adsClas.getOffsetD1Directo(), 4);
    Serial.print(F(" V | D2 = ")); Serial.print(adsClas.getOffsetD2Directo(), 4); Serial.println(F(" V"));
    Serial.print(F("  Divisor 02 : D1 = ")); Serial.print(adsClas.getOffsetD1Ejercito(), 4);
    Serial.print(F(" V | D2 = ")); Serial.print(adsClas.getOffsetD2Ejercito(), 4); Serial.println(F(" V"));
    Serial.print(F("  Factores K : K_D1 = ")); Serial.print(adsClas.getFactorK_D1(), 4);
    Serial.print(F(" | K_D2 = ")); Serial.println(adsClas.getFactorK_D2(), 4);

    Serial.println(F("\n[INA219 1 (0x40 - Fuente a Circuito)]"));
    Serial.print(F("  Offset I   : ")); Serial.print(ina1.getOffsetCorriente(), 4); Serial.println(F(" mA"));
    Serial.print(F("  Offset Vbus: ")); Serial.print(ina1.getOffsetVBus(), 4); Serial.println(F(" V"));
    Serial.print(F("  Factor K_I : ")); Serial.println(ina1.getFactorK_I(), 4);

    Serial.println(F("\n[INA219 2 (0x41 - Libre)]"));
    Serial.print(F("  Offset I   : ")); Serial.print(ina2.getOffsetCorriente(), 4); Serial.println(F(" mA"));
    Serial.print(F("  Offset Vbus: ")); Serial.print(ina2.getOffsetVBus(), 4); Serial.println(F(" V"));
    Serial.print(F("  Factor K_I : ")); Serial.println(ina2.getFactorK_I(), 4);
    Serial.println(F("========================================================="));
}