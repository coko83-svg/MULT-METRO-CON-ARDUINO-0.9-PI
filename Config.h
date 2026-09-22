#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Firmware version metadata
#define FIRMWARE_VERSION "0.9 PI"

// Verified hardware I2C addresses
#define ADDR_ADS_MODERNO  0x48 // ADS1115 with MCP6002 input buffers
#define ADDR_ADS_CLASICO  0x4A // ADS1115 with clamping protection
#define ADDR_INA_FABRICA1 0x40 // High-side between power supply and circuit under test
#define ADDR_INA_FABRICA2 0x41 // Free sensing module for arbitrary circuit nodes

#define ADDR_DS3231_RTC    0x68 // RTC Address
#define ADDR_DS3231_EEPROM 0x57 // AT24C32 EEPROM Address

// Sampling period (milliseconds)
#define INTERVALO_MUESTREO 1000

// Serial visualization modes
enum LogMode {
    LOG_COLUMNAS = 1, // Standard tabular output with time column (tab delimited)
    LOG_RECUADRO = 2, // Diagnostic multiline block
    LOG_PLOTTER  = 3  // Clean CSV stream for Serial Plotter / Teleplot (comma delimited)
};

// System configuration and runtime state structure
struct SystemConfig {
    // Active modules selected by user
    bool ads_moderno_activo = false;
    bool ads_clasico_activo = false;
    bool ina_fabrica1_activo = false;
    bool ina_fabrica2_activo = false;

    // Physical presence detected during cold I2C bus scan
    bool ads_moderno_presente = false;
    bool ads_clasico_presente = false;
    bool ina_fabrica1_presente = false;
    bool ina_fabrica2_presente = false;
    bool ds3231_presente = false;

    // Scale mode for ADS1115 (Direct 5V or Resistive Divider)
    bool ads_moderno_usa_ejercito = false;
    bool ads_clasico_usa_ejercito = false;

    // Serial logging configuration
    LogMode modo_salida = LOG_COLUMNAS;
    bool encabezado_impreso = false;

    // Plotter Mode bounds (Volatile session state - NOT written to EEPROM)
    bool plotter_con_cotas = false;
    float cota_inferior = 0.0000f;
    float cota_superior = 15.0000f;
};

#endif