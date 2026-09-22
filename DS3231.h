#ifndef DS3231_H
#define DS3231_H

#include <Arduino.h>
#include <Wire.h>

class DS3231 {
private:
    uint8_t addr_rtc;
    uint8_t addr_eeprom;

public:
    DS3231(uint8_t rtc_addr, uint8_t eeprom_addr);
    
    void init();
    bool checkConnection();
    
    // Obtiene la lectura térmica directamente de los registros internos del reloj
    float getTemperatura();
    
    // Funciones de memoria no volátil paginadas para sortear la restricción 
    // del búfer de 32 bytes de la librería Wire.
    bool escribirEEPROM(uint16_t direccion, const uint8_t* datos, size_t tamano);
    bool leerEEPROM(uint16_t direccion, uint8_t* datos, size_t tamano);
};

#endif