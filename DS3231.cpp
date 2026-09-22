#include "DS3231.h"

DS3231::DS3231(uint8_t rtc_addr, uint8_t eeprom_addr) {
    addr_rtc = rtc_addr;
    addr_eeprom = eeprom_addr;
}

void DS3231::init() {
    Wire.begin();
}

bool DS3231::checkConnection() {
    // Buscamos prioritariamente la EEPROM ya que es el componente critico
    Wire.beginTransmission(addr_eeprom);
    if (Wire.endTransmission() == 0) {
        return true;
    }
    return false;
}

float DS3231::getTemperatura() {
    Wire.beginTransmission(addr_rtc);
    Wire.write(0x11); // Puntero al registro MSB de Temperatura
    if (Wire.endTransmission() != 0) return 0.0f;

    Wire.requestFrom((uint8_t)addr_rtc, (uint8_t)2);
    if (Wire.available() == 2) {
        int8_t msb = Wire.read();     // Parte entera (Two's complement)
        uint8_t lsb = Wire.read();    // Parte fraccional (2 bits MSB)
        // La resolucion es de 0.25 °C por cada incremento de los bits superiores del lsb
        return (float)msb + ((lsb >> 6) * 0.25f);
    }
    return 0.0f;
}

bool DS3231::escribirEEPROM(uint16_t direccion, const uint8_t* datos, size_t tamano) {
    size_t escritos = 0;
    while (escritos < tamano) {
        // La AT24C32 tiene paginas de 32 bytes, pero el buffer de Arduino Wire es de 32 bytes maximo
        // Usamos chunks seguros de 16 bytes.
        size_t chunk = tamano - escritos;
        if (chunk > 16) chunk = 16;

        Wire.beginTransmission(addr_eeprom);
        Wire.write((uint8_t)((direccion + escritos) >> 8));   // MSB Address
        Wire.write((uint8_t)((direccion + escritos) & 0xFF)); // LSB Address
        
        for (size_t i = 0; i < chunk; i++) {
            Wire.write(datos[escritos + i]);
        }
        
        if (Wire.endTransmission() != 0) return false;
        
        delay(5); // Retardo obligatorio por datasheet para grabar la pagina (tWR)
        escritos += chunk;
    }
    return true;
}

bool DS3231::leerEEPROM(uint16_t direccion, uint8_t* datos, size_t tamano) {
    size_t leidos = 0;
    while (leidos < tamano) {
        size_t chunk = tamano - leidos;
        if (chunk > 16) chunk = 16;

        Wire.beginTransmission(addr_eeprom);
        Wire.write((uint8_t)((direccion + leidos) >> 8));
        Wire.write((uint8_t)((direccion + leidos) & 0xFF));
        if (Wire.endTransmission() != 0) return false;

        Wire.requestFrom((uint8_t)addr_eeprom, (uint8_t)chunk);
        for (size_t i = 0; i < chunk; i++) {
            if (Wire.available()) {
                datos[leidos + i] = Wire.read();
            }
        }
        leidos += chunk;
    }
    return true;
}