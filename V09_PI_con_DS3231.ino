/*
  =============================================================================
  PROYECTO: MULTÍMETRO CON ARDUINO
  VERSIÓN:  0.9 PI
  =============================================================================
  COMPATIBILIDAD CRÍTICA DE HARDWARE: 100% ARDUINO UNO R4 WIFI (RENESAS RA4M1)
  MAPEO I2C:
    - ADS1115 Moderno (Buffers MCP6002) : 0x48
    - ADS1115 Clásico (Protección Clamp): 0x4A
    - INA219 1 (Fijo Fuente a Circuito) : 0x40
    - INA219 2 (Libre de Ensayo)        : 0x41

  NOVEDADES EN VERSIÓN 0.9 PI:
    1) Calibración a cero totalmente desacoplada canal por canal.
    2) Factores de escala (K) independientes (4 divisores y 2 shunts INA219).
    3) Almacenamiento persistente en EEPROM del modulo RTC DS3231.
    4) Modo Plotter (CSV puro sin columna de tiempo y con comas).
    5) Cotas volátiles configurables para congelar escalas en graficadores.
  =============================================================================
*/

#include <Wire.h>
#include "Config.h"
#include "EjercitoResistivo.h"
#include "DS3231.h"
#include "MedidorADS.h"
#include "MedidorINA219.h"
#include "SerialLogger.h"
#include "MenuController.h"

// Divisores resistivos independientes por canal (Nominal: 33k / 10k)
EjercitoResistivo divModD1(33000.0f, 10000.0f);
EjercitoResistivo divModD2(33000.0f, 10000.0f);
EjercitoResistivo divClasD1(33000.0f, 10000.0f);
EjercitoResistivo divClasD2(33000.0f, 10000.0f);

// Instancia del módulo DS3231 (RTC y EEPROM I2C externa)
DS3231 miRTC(ADDR_DS3231_RTC, ADDR_DS3231_EEPROM);

// Hardware module instances
MedidorADS miADS_Moderno(ADDR_ADS_MODERNO, &divModD1, &divModD2);
MedidorADS miADS_Clasico(ADDR_ADS_CLASICO, &divClasD1, &divClasD2);
MedidorINA219 miINA_Fabrica1(ADDR_INA_FABRICA1);
MedidorINA219 miINA_Fabrica2(ADDR_INA_FABRICA2);

// Logger, controller and state instances
SerialLogger miLogger;
MenuController miMenu;
SystemConfig sysCfg;

bool midiendo = false;
unsigned long ultimoMuestreo = 0;
unsigned long tiempoInicio = 0;

void setup() {
    Serial.begin(115200);
    
    // FIX SERIAL: Esperar un maximo de 3 segundos al puerto serial, luego continuar sí o sí.
    unsigned long t_inicio_serial = millis();
    while (!Serial && (millis() - t_inicio_serial < 3000));
    delay(500); // Dar tiempo al puente USB a estabilizar los buffers

    Wire.begin(); // Initialize native I2C bus

    Serial.println(F("=================================================="));
    Serial.print(F(" MULTÍMETRO ARDUINO - VERSIÓN "));
    Serial.println(F(FIRMWARE_VERSION));
    Serial.println(F(" Arquitectura Metrológica y Persistencia EEPROM   "));
    Serial.println(F("=================================================="));

    miMenu.iniciarConfiguracion(sysCfg, miRTC, miADS_Moderno, miADS_Clasico, miINA_Fabrica1, miINA_Fabrica2);
}

void loop() {
    // 1. Process serial commands and menu state machine (non-blocking)
    miMenu.procesarMenu(sysCfg, midiendo, tiempoInicio, miRTC, miADS_Moderno, miADS_Clasico, miINA_Fabrica1, miINA_Fabrica2);

    // 2. Periodic acquisition engine
    if (midiendo && (millis() - ultimoMuestreo >= INTERVALO_MUESTREO)) {
        ultimoMuestreo = millis();
        float tiempo_s = (millis() - tiempoInicio) / 1000.0f;

        // Print header if required
        miLogger.chequearEImprimirEncabezado(sysCfg);

        // Acquisition storage variables
        float v_d1_m1 = 0.0f, v_d2_m1 = 0.0f, escD1_m1 = 0.0f, escD2_m1 = 0.0f;
        float v_d1_m2 = 0.0f, v_d2_m2 = 0.0f, escD1_m2 = 0.0f, escD2_m2 = 0.0f;
        float v_bus1 = 0.0f, i_ma1 = 0.0f, v_load1 = 0.0f, p_mw1 = 0.0f;
        float v_bus2 = 0.0f, i_ma2 = 0.0f, v_load2 = 0.0f, p_mw2 = 0.0f;
        float temp_rtc = 0.0f;

        if (sysCfg.ds3231_presente) {
            temp_rtc = miRTC.getTemperatura();
        }

        // Reading ADS Moderno (0x48)
        if (sysCfg.ads_moderno_activo) {
            v_d1_m1 = miADS_Moderno.leerDiferencialAutorrango(0, escD1_m1);
            v_d2_m1 = miADS_Moderno.leerDiferencialAutorrango(1, escD2_m1);
        }

        // Reading ADS Clásico (0x4A)
        if (sysCfg.ads_clasico_activo) {
            v_d1_m2 = miADS_Clasico.leerDiferencialAutorrango(0, escD1_m2);
            v_d2_m2 = miADS_Clasico.leerDiferencialAutorrango(1, escD2_m2);
        }

        // Reading INA219 1 (0x40 - Fixed Source to Circuit)
        if (sysCfg.ina_fabrica1_activo) {
            v_bus1 = miINA_Fabrica1.leerVoltajeBus();
            float v_shunt_mv1 = miINA_Fabrica1.leerVoltajeShunt();
            i_ma1 = miINA_Fabrica1.leerCorriente();
            p_mw1 = miINA_Fabrica1.leerPotencia();
            v_load1 = v_bus1 + (v_shunt_mv1 / 1000.0f);
        }

        // Reading INA219 2 (0x41 - Free Sensing Node)
        if (sysCfg.ina_fabrica2_activo) {
            v_bus2 = miINA_Fabrica2.leerVoltajeBus();
            float v_shunt_mv2 = miINA_Fabrica2.leerVoltajeShunt();
            i_ma2 = miINA_Fabrica2.leerCorriente();
            p_mw2 = miINA_Fabrica2.leerPotencia();
            v_load2 = v_bus2 + (v_shunt_mv2 / 1000.0f);
        }

        miLogger.loggearDatos(sysCfg, tiempo_s, 
                              v_d1_m1, v_d2_m1, escD1_m1, escD2_m1,
                              v_d1_m2, v_d2_m2, escD1_m2, escD2_m2,
                              v_bus1, i_ma1, v_load1, p_mw1,
                              v_bus2, i_ma2, v_load2, p_mw2,
                              temp_rtc);
    }
}