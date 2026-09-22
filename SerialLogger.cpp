#include "SerialLogger.h"

void SerialLogger::chequearEImprimirEncabezado(SystemConfig &cfg) {
    if (cfg.encabezado_impreso) return;

    if (cfg.modo_salida == LOG_COLUMNAS) {
        String cabecera = "T(s)\t";
        if (cfg.ads_moderno_activo) cabecera += "V_D1_Mod(V)\tV_D2_Mod(V)\tEsc_D1_Mod(V)\tEsc_D2_Mod(V)\t";
        if (cfg.ads_clasico_activo) cabecera += "V_D1_Clas(V)\tV_D2_Clas(V)\tEsc_D1_Clas(V)\tEsc_D2_Clas(V)\t";
        if (cfg.ina_fabrica1_activo) cabecera += "V_Bus_Ina1(V)\tI_Ina1(mA)\tV_Load_Ina1(V)\tP_Ina1(mW)\t";
        if (cfg.ina_fabrica2_activo) cabecera += "V_Bus_Ina2(V)\tI_Ina2(mA)\tV_Load_Ina2(V)\tP_Ina2(mW)\t";
        if (cfg.ds3231_presente) cabecera += "Temp_RTC(C)\t";
        
        Serial.println();
        Serial.println(cabecera);
        cfg.encabezado_impreso = true;
    } 
    else if (cfg.modo_salida == LOG_PLOTTER) {
        String cabecera = "";
        if (cfg.plotter_con_cotas) {
            cabecera += "Cota_Inf,Cota_Sup";
        }
        
        auto agregarColumna = [&](const char* nombre) {
            if (cabecera.length() > 0) cabecera += ",";
            cabecera += nombre;
        };

        if (cfg.ads_moderno_activo) {
            agregarColumna("V_D1_Mod");
            agregarColumna("V_D2_Mod");
        }
        if (cfg.ads_clasico_activo) {
            agregarColumna("V_D1_Clas");
            agregarColumna("V_D2_Clas");
        }
        if (cfg.ina_fabrica1_activo) {
            agregarColumna("V_Bus_Ina1");
            agregarColumna("I_Ina1");
            agregarColumna("V_Load_Ina1");
            agregarColumna("P_Ina1");
        }
        if (cfg.ina_fabrica2_activo) {
            agregarColumna("V_Bus_Ina2");
            agregarColumna("I_Ina2");
            agregarColumna("V_Load_Ina2");
            agregarColumna("P_Ina2");
        }
        if (cfg.ds3231_presente) {
            agregarColumna("Temp_RTC");
        }

        Serial.println();
        Serial.println(cabecera);
        cfg.encabezado_impreso = true;
    }
}

void SerialLogger::loggearDatos(SystemConfig &cfg, float tiempo, 
                                float v_d1_m1, float v_d2_m1, float esc1_m1, float esc2_m1,
                                float v_d1_m2, float v_d2_m2, float esc1_m2, float esc2_m2,
                                float v_bus1, float i_ma1, float v_load1, float p_mw1,
                                float v_bus2, float i_ma2, float v_load2, float p_mw2,
                                float temp_rtc) {
    if (cfg.modo_salida == LOG_COLUMNAS) {
        // Tabular Columns Format (4 decimal figures for all sensor measurements)
        Serial.print(tiempo, 1); Serial.print(F("\t"));
        
        if (cfg.ads_moderno_activo) {
            Serial.print(v_d1_m1, 4); Serial.print(F("\t")); Serial.print(v_d2_m1, 4); Serial.print(F("\t"));
            Serial.print(esc1_m1, 3); Serial.print(F("\t")); Serial.print(esc2_m1, 3); Serial.print(F("\t"));
        }
        if (cfg.ads_clasico_activo) {
            Serial.print(v_d1_m2, 4); Serial.print(F("\t")); Serial.print(v_d2_m2, 4); Serial.print(F("\t"));
            Serial.print(esc1_m2, 3); Serial.print(F("\t")); Serial.print(esc2_m2, 3); Serial.print(F("\t"));
        }
        if (cfg.ina_fabrica1_activo) {
            Serial.print(v_bus1, 4); Serial.print(F("\t")); Serial.print(i_ma1, 4); Serial.print(F("\t"));
            Serial.print(v_load1, 4); Serial.print(F("\t")); Serial.print(p_mw1, 4); Serial.print(F("\t"));
        }
        if (cfg.ina_fabrica2_activo) {
            Serial.print(v_bus2, 4); Serial.print(F("\t")); Serial.print(i_ma2, 4); Serial.print(F("\t"));
            Serial.print(v_load2, 4); Serial.print(F("\t")); Serial.print(p_mw2, 4); Serial.print(F("\t"));
        }
        if (cfg.ds3231_presente) {
            Serial.print(temp_rtc, 2); Serial.print(F("\t"));
        }
        Serial.println();
    } 
    else if (cfg.modo_salida == LOG_PLOTTER) {
        bool primero = true;
        auto imprimirSeparador = [&]() {
            if (!primero) Serial.print(F(","));
            primero = false;
        };

        if (cfg.plotter_con_cotas) {
            imprimirSeparador(); Serial.print(cfg.cota_inferior, 4);
            imprimirSeparador(); Serial.print(cfg.cota_superior, 4);
        }

        if (cfg.ads_moderno_activo) {
            imprimirSeparador(); Serial.print(v_d1_m1, 4);
            imprimirSeparador(); Serial.print(v_d2_m1, 4);
        }
        if (cfg.ads_clasico_activo) {
            imprimirSeparador(); Serial.print(v_d1_m2, 4);
            imprimirSeparador(); Serial.print(v_d2_m2, 4);
        }
        if (cfg.ina_fabrica1_activo) {
            imprimirSeparador(); Serial.print(v_bus1, 4);
            imprimirSeparador(); Serial.print(i_ma1, 4);
            imprimirSeparador(); Serial.print(v_load1, 4);
            imprimirSeparador(); Serial.print(p_mw1, 4);
        }
        if (cfg.ina_fabrica2_activo) {
            imprimirSeparador(); Serial.print(v_bus2, 4);
            imprimirSeparador(); Serial.print(i_ma2, 4);
            imprimirSeparador(); Serial.print(v_load2, 4);
            imprimirSeparador(); Serial.print(p_mw2, 4);
        }
        if (cfg.ds3231_presente) {
            imprimirSeparador(); Serial.print(temp_rtc, 2);
        }
        Serial.println();
    }
    else if (cfg.modo_salida == LOG_RECUADRO) {
        Serial.println(F("--------------------------------------------------"));
        Serial.print(F(" Tiempo: ")); Serial.print(tiempo, 1); Serial.println(F(" s"));
        
        if (cfg.ads_moderno_activo) {
            Serial.println(F(" [ADS1115 Moderno 0x48]"));
            Serial.print(F("  V_D1: ")); Serial.print(v_d1_m1, 4); Serial.print(F(" V (Esc: ")); Serial.print(esc1_m1, 3); Serial.println(F(" V)"));
            Serial.print(F("  V_D2: ")); Serial.print(v_d2_m1, 4); Serial.print(F(" V (Esc: ")); Serial.print(esc2_m1, 3); Serial.println(F(" V)"));
        }
        if (cfg.ads_clasico_activo) {
            Serial.println(F(" [ADS1115 Clásico 0x4A]"));
            Serial.print(F("  V_D1: ")); Serial.print(v_d1_m2, 4); Serial.print(F(" V (Esc: ")); Serial.print(esc1_m2, 3); Serial.println(F(" V)"));
            Serial.print(F("  V_D2: ")); Serial.print(v_d2_m2, 4); Serial.print(F(" V (Esc: ")); Serial.print(esc2_m2, 3); Serial.println(F(" V)"));
        }
        if (cfg.ina_fabrica1_activo) {
            Serial.println(F(" [INA219 Fábrica 1 (0x40 - Fuente a Circuito)]"));
            Serial.print(F("  V_Bus : ")); Serial.print(v_bus1, 4); Serial.println(F(" V"));
            Serial.print(F("  V_Load: ")); Serial.print(v_load1, 4); Serial.println(F(" V"));
            Serial.print(F("  Corri : ")); Serial.print(i_ma1, 4); Serial.println(F(" mA"));
            Serial.print(F("  Poten : ")); Serial.print(p_mw1, 4); Serial.println(F(" mW"));
        }
        if (cfg.ina_fabrica2_activo) {
            Serial.println(F(" [INA219 Fábrica 2 (0x41 - Libre)]"));
            Serial.print(F("  V_Bus : ")); Serial.print(v_bus2, 4); Serial.println(F(" V"));
            Serial.print(F("  V_Load: ")); Serial.print(v_load2, 4); Serial.println(F(" V"));
            Serial.print(F("  Corri : ")); Serial.print(i_ma2, 4); Serial.println(F(" mA"));
            Serial.print(F("  Poten : ")); Serial.print(p_mw2, 4); Serial.println(F(" mW"));
        }
        if (cfg.ds3231_presente) {
            Serial.println(F(" [Módulo DS3231]"));
            Serial.print(F("  Temp. : ")); Serial.print(temp_rtc, 2); Serial.println(F(" °C"));
        }
    }
}