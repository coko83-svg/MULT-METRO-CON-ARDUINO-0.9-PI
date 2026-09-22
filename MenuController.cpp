#include "MenuController.h"

MenuController::MenuController() {
    estadoActual = MSTATE_CONFIG_SELECCION_MODULOS;
    accionPendiente = CALIB_NINGUNA;
    bufferIdx = 0;
    memset(bufferEntrada, 0, sizeof(bufferEntrada));
}

void MenuController::escanearHardware(SystemConfig &cfg, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    Serial.println(F("\n>>> ESCANEANDO DISPOSITIVOS EN BUS I2C (EN FRÍO) <<<"));
    cfg.ds3231_presente       = rtc.checkConnection();
    cfg.ads_moderno_presente  = adsMod.checkConnection();
    cfg.ads_clasico_presente  = adsClas.checkConnection();
    cfg.ina_fabrica1_presente = ina1.checkConnection();
    cfg.ina_fabrica2_presente = ina2.checkConnection();

    Serial.print(F(" [0x57/0x68] Módulo DS3231 (RTC/EEPROM)   : ")); Serial.println(cfg.ds3231_presente ? F("DETECTADO") : F("No presente"));
    Serial.print(F(" [0x48] ADS1115 Moderno (Buffers MCP6002) : ")); Serial.println(cfg.ads_moderno_presente ? F("DETECTADO") : F("No presente"));
    Serial.print(F(" [0x4A] ADS1115 Clásico (Clamping)         : ")); Serial.println(cfg.ads_clasico_presente ? F("DETECTADO") : F("No presente"));
    Serial.print(F(" [0x40] INA219 Fábrica 1 (Fuente a Circ.)  : ")); Serial.println(cfg.ina_fabrica1_presente ? F("DETECTADO") : F("No presente"));
    Serial.print(F(" [0x41] INA219 Fábrica 2 (Libre / Ensayo)  : ")); Serial.println(cfg.ina_fabrica2_presente ? F("DETECTADO") : F("No presente"));

    if (!cfg.ads_moderno_presente && !cfg.ads_clasico_presente && !cfg.ina_fabrica1_presente && !cfg.ina_fabrica2_presente) {
        Serial.println(F("\n[!] ERROR CRÍTICO: No se detectó ningún módulo de medición en el bus I2C."));
        Serial.println(F("    Revise cableado, conexiones a zapatilla I2C y alimentación."));
    }
}

void MenuController::iniciarConfiguracion(SystemConfig &cfg, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    escanearHardware(cfg, rtc, adsMod, adsClas, ina1, ina2);
    CalibStorage::cargar(rtc, adsMod, adsClas, ina1, ina2);
    estadoActual = MSTATE_CONFIG_SELECCION_MODULOS;
    imprimirMenuSeleccionModulos(cfg);
}

void MenuController::imprimirMenuSeleccionModulos(SystemConfig &cfg) {
    Serial.println(F("\n--- SELECCIÓN DE MÓDULOS ACTIVOS (v0.9 PI) ---"));
    Serial.print(F("[1] ADS1115 Moderno (0x48) : "));
    if (!cfg.ads_moderno_presente) Serial.println(F("[NO DETECTADO]"));
    else Serial.println(cfg.ads_moderno_activo ? F("ACTIVO") : F("Inactivo"));

    Serial.print(F("[2] ADS1115 Clásico (0x4A) : "));
    if (!cfg.ads_clasico_presente) Serial.println(F("[NO DETECTADO]"));
    else Serial.println(cfg.ads_clasico_activo ? F("ACTIVO") : F("Inactivo"));

    Serial.print(F("[3] INA219 Fábrica 1 (0x40): "));
    if (!cfg.ina_fabrica1_presente) Serial.println(F("[NO DETECTADO]"));
    else Serial.println(cfg.ina_fabrica1_activo ? F("ACTIVO") : F("Inactivo"));

    Serial.print(F("[4] INA219 Fábrica 2 (0x41): "));
    if (!cfg.ina_fabrica2_presente) Serial.println(F("[NO DETECTADO]"));
    else Serial.println(cfg.ina_fabrica2_activo ? F("ACTIVO") : F("Inactivo"));

    Serial.println(F("[0] Guardar y Continuar"));
    Serial.print(F("Seleccione una opción: "));
}

void MenuController::imprimirMenuADSModerno(SystemConfig &cfg) {
    Serial.println(F("\n--- MODO ESCALA: ADS1115 Moderno (0x48) ---"));
    Serial.print(F("[1] Directo 0-5V ")); Serial.println(!cfg.ads_moderno_usa_ejercito ? F("(*)") : F(""));
    Serial.print(F("[2] Divisores Resistivos 01 (33k/10k) ")); Serial.println(cfg.ads_moderno_usa_ejercito ? F("(*)") : F(""));
    Serial.println(F("[0] Guardar y Continuar"));
    Serial.print(F("Seleccione una opción: "));
}

void MenuController::imprimirMenuADSClasico(SystemConfig &cfg) {
    Serial.println(F("\n--- MODO ESCALA: ADS1115 Clásico (0x4A) ---"));
    Serial.print(F("[1] Directo 0-5V ")); Serial.println(!cfg.ads_clasico_usa_ejercito ? F("(*)") : F(""));
    Serial.print(F("[2] Divisores Resistivos 02 (33k/10k) ")); Serial.println(cfg.ads_clasico_usa_ejercito ? F("(*)") : F(""));
    Serial.println(F("[0] Guardar y Continuar"));
    Serial.print(F("Seleccione una opción: "));
}

void MenuController::imprimirMenuPrincipal(SystemConfig &cfg) {
    Serial.println(F("\n======================================"));
    Serial.println(F("      SISTEMA LISTO (v0.9 PI)         "));
    Serial.println(F("======================================"));
    Serial.println(F("[1] Iniciar/Detener Medición"));
    Serial.print(F("[2] Modo de Salida Serial: "));
    if (cfg.modo_salida == LOG_COLUMNAS) Serial.println(F("Columnas (Tab)"));
    else if (cfg.modo_salida == LOG_RECUADRO) Serial.println(F("Recuadro"));
    else Serial.println(F("Plotter (CSV puro)"));

    Serial.print(F("[P] Opciones de Plotter "));
    if (cfg.modo_salida == LOG_PLOTTER) {
        Serial.print(cfg.plotter_con_cotas ? F("[Con Cotas]") : F("[Sin Cotas]"));
    }
    Serial.println();

    Serial.println(F("[K] Menú de Calibraciones (Offsets y K)"));
    Serial.println(F("[C] Reconfigurar Módulos I2C"));
    Serial.println(F("======================================"));
    cfg.encabezado_impreso = false;
}

void MenuController::imprimirMenuPlotter(SystemConfig &cfg) {
    Serial.println(F("\n--- OPCIONES DE MODO PLOTTER (CSV) ---"));
    Serial.print(F("[1] Alternar Cotas: "));
    Serial.println(cfg.plotter_con_cotas ? F("CON COTAS (Activo)") : F("SIN COTAS (Puro)"));
    Serial.print(F("[2] Configurar Cota Inferior [Actual: ")); Serial.print(cfg.cota_inferior, 4); Serial.println(F("]"));
    Serial.print(F("[3] Configurar Cota Superior [Actual: ")); Serial.print(cfg.cota_superior, 4); Serial.println(F("]"));
    Serial.println(F("[0] Volver al Menú Principal"));
    Serial.print(F("Seleccione una opción: "));
}

void MenuController::imprimirMenuCalibracion() {
    Serial.println(F("\n========================================================="));
    Serial.println(F("   PANEL DE CALIBRACIONES: OFFSETS A CERO Y FACTORES K   "));
    Serial.println(F("========================================================="));
    Serial.println(F("--- PUESTA A CERO INDIVIDUAL (OFFSETS) ---"));
    Serial.println(F(" [1] ADS Moderno (0x48) - Canal D1 Cero [Directo 5V]"));
    Serial.println(F(" [2] ADS Moderno (0x48) - Canal D2 Cero [Directo 5V]"));
    Serial.println(F(" [3] ADS Moderno (0x48) - Canal D1 Cero [Con Divisor]"));
    Serial.println(F(" [4] ADS Moderno (0x48) - Canal D2 Cero [Con Divisor]"));
    Serial.println(F(" [5] ADS Clásico (0x4A) - Canal D1 Cero [Directo 5V]"));
    Serial.println(F(" [6] ADS Clásico (0x4A) - Canal D2 Cero [Directo 5V]"));
    Serial.println(F(" [7] ADS Clásico (0x4A) - Canal D1 Cero [Con Divisor]"));
    Serial.println(F(" [8] ADS Clásico (0x4A) - Canal D2 Cero [Con Divisor]"));
    Serial.println(F(" [9] INA219 1    (0x40) - Cero Corriente (0 mA)"));
    Serial.println(F(" [A] INA219 1    (0x40) - Cero Tensión Bus (0 V)"));
    Serial.println(F(" [B] INA219 2    (0x41) - Cero Corriente (0 mA)"));
    Serial.println(F(" [D] INA219 2    (0x41) - Cero Tensión Bus (0 V)"));
    Serial.println(F("--- FACTORES DE ESCALA INDIVIDUALES (K) ---"));
    Serial.println(F(" [E] Factor K Divisor Moderno D1"));
    Serial.println(F(" [F] Factor K Divisor Moderno D2"));
    Serial.println(F(" [G] Factor K Divisor Clásico D1"));
    Serial.println(F(" [H] Factor K Divisor Clásico D2"));
    Serial.println(F(" [I] Factor K Corriente INA219 1"));
    Serial.println(F(" [J] Factor K Corriente INA219 2"));
    Serial.println(F("---------------------------------------------------------"));
    Serial.println(F(" [V] Ver Estado Actual de Calibraciones (Offsets y K)"));
    Serial.println(F(" [L] Recargar desde EEPROM"));
    Serial.println(F(" [R] Resetear a Valores de Fábrica"));
    Serial.println(F(" [0] Volver al Menú Principal"));
    Serial.println(F("========================================================="));
    Serial.print(F("Seleccione una opción: "));
}

void MenuController::mostrarInstruccionesCero(CalibAccion accion) {
    Serial.println(F("\n---------------------------------------------------------"));
    switch (accion) {
        case CALIB_ZERO_ADS_MOD_D1_DIR:
        case CALIB_ZERO_ADS_MOD_D2_DIR:
        case CALIB_ZERO_ADS_CLAS_D1_DIR:
        case CALIB_ZERO_ADS_CLAS_D2_DIR:
            Serial.println(F("INSTRUCCIONES: Calibración de Cero en Modo 5V Directo"));
            Serial.println(F("1. Desconecte las puntas del circuito bajo prueba."));
            Serial.println(F("2. Una Punta+ y Punta- del canal a calibrar entre sí"));
            Serial.println(F("   y conéctelas temporalmente a la plaqueta de GND común."));
            break;

        case CALIB_ZERO_ADS_MOD_D1_EJ:
        case CALIB_ZERO_ADS_MOD_D2_EJ:
        case CALIB_ZERO_ADS_CLAS_D1_EJ:
        case CALIB_ZERO_ADS_CLAS_D2_EJ:
            Serial.println(F("INSTRUCCIONES: Calibración de Cero con Divisor Resistivo"));
            Serial.println(F("1. Asegure que la entrada del divisor no tenga tensión externa."));
            Serial.println(F("2. Conecte la entrada positiva del divisor directamente"));
            Serial.println(F("   a la plaqueta de GND común para forzar 0.0000 V estricto."));
            break;

        case CALIB_ZERO_INA1_CORRIENTE:
            Serial.println(F("INSTRUCCIONES: INA219 1 (0x40) - Cero de Corriente"));
            Serial.println(F("Recordatorio: Este módulo va fijo entre la fuente y el circuito."));
            Serial.println(F("1. Deje la fuente conectada en Vin+."));
            Serial.println(F("2. Desconecte TOTALMENTE la carga de Vin- (circuito abierto, 0.00 mA)."));
            break;

        case CALIB_ZERO_INA1_VBUS:
            Serial.println(F("INSTRUCCIONES: INA219 1 (0x40) - Cero de Tensión de Bus"));
            Serial.println(F("1. Apague la fuente o desconecte Vin+ de toda alimentación externa."));
            break;

        case CALIB_ZERO_INA2_CORRIENTE:
            Serial.println(F("INSTRUCCIONES: INA219 2 (0x41) - Cero de Corriente"));
            Serial.println(F("1. Asegure circuito abierto total en el shunt (sin corriente)."));
            break;

        case CALIB_ZERO_INA2_VBUS:
            Serial.println(F("INSTRUCCIONES: INA219 2 (0x41) - Cero de Tensión de Bus"));
            Serial.println(F("1. Desconecte Vin+ de cualquier punto con tensión."));
            break;

        default:
            break;
    }
    Serial.println(F("---------------------------------------------------------"));
    Serial.print(F("¿Desea ejecutar la calibración ahora? [S = Sí / C = Cancelar]: "));
}

void MenuController::mostrarInstruccionesFactorK(CalibAccion accion, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    Serial.println(F("\n---------------------------------------------------------"));
    float factorActual = 1.0f;
    switch (accion) {
        case CALIB_FACTOR_K_MOD_D1:  factorActual = adsMod.getFactorK_D1(); break;
        case CALIB_FACTOR_K_MOD_D2:  factorActual = adsMod.getFactorK_D2(); break;
        case CALIB_FACTOR_K_CLAS_D1: factorActual = adsClas.getFactorK_D1(); break;
        case CALIB_FACTOR_K_CLAS_D2: factorActual = adsClas.getFactorK_D2(); break;
        case CALIB_FACTOR_K_INA1_I:  factorActual = ina1.getFactorK_I(); break;
        case CALIB_FACTOR_K_INA2_I:  factorActual = ina2.getFactorK_I(); break;
        default: break;
    }

    if (accion >= CALIB_FACTOR_K_MOD_D1 && accion <= CALIB_FACTOR_K_CLAS_D2) {
        Serial.println(F("INSTRUCCIONES: Calibración de Factor de Escala (Divisor Resistivo)"));
        Serial.println(F("1. Conecte una tensión continua estable y conocida (V_patron, ej: 10.0000 V)"));
        Serial.println(F("   a la entrada del divisor resistivo."));
        Serial.println(F("2. Observe la lectura obtenida por el multímetro (V_leido)."));
        Serial.println(F("3. Calcule: K_nuevo = (V_patron / V_leido) * K_actual"));
        Serial.print(F("   [Factor K actual en memoria: ")); Serial.print(factorActual, 4); Serial.println(F("]"));
    } else {
        Serial.println(F("INSTRUCCIONES: Calibración de Ganancia de Corriente (INA219 Shunt)"));
        Serial.println(F("1. Conecte un multímetro patrón en serie con la carga (I_patron, ej: 500.0 mA)."));
        Serial.println(F("2. Observe la corriente reportada por el INA219 (I_leido)."));
        Serial.println(F("3. Calcule: K_nuevo = (I_patron / I_leido) * K_actual"));
        Serial.print(F("   [Factor K actual en memoria: ")); Serial.print(factorActual, 4); Serial.println(F("]"));
    }
    Serial.println(F("---------------------------------------------------------"));
    Serial.print(F("Ingrese el nuevo valor numérico del Factor K y presione ENTER: "));
    bufferIdx = 0;
    memset(bufferEntrada, 0, sizeof(bufferEntrada));
}

void MenuController::ejecutarCalibracionCero(CalibAccion accion, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    // FIX I2C HANG: Reiniciamos el bus y los sensores antes de medir
    Serial.println(F("\n>> Limpiando bus I2C tras manipulación física de cables..."));
    Wire.end();
    Wire.begin();
    if (rtc.checkConnection()) rtc.init();
    if (adsMod.checkConnection()) adsMod.init();
    if (adsClas.checkConnection()) adsClas.init();
    if (ina1.checkConnection()) ina1.init();
    if (ina2.checkConnection()) ina2.init();
    delay(50); // Estabilización post-reinicio

    Serial.println(F(">> Adquiriendo 32 muestras para promedio de offset..."));

    switch (accion) {
        case CALIB_ZERO_ADS_MOD_D1_DIR:
            adsMod.calibrarCeroDirectoD1(32);
            Serial.print(F(">> ADS Moderno D1 (5V) -> Offset: ")); Serial.print(adsMod.getOffsetD1Directo(), 4); Serial.println(F(" V"));
            break;
        case CALIB_ZERO_ADS_MOD_D2_DIR:
            adsMod.calibrarCeroDirectoD2(32);
            Serial.print(F(">> ADS Moderno D2 (5V) -> Offset: ")); Serial.print(adsMod.getOffsetD2Directo(), 4); Serial.println(F(" V"));
            break;
        case CALIB_ZERO_ADS_MOD_D1_EJ:
            adsMod.calibrarCeroEjercitoD1(32);
            Serial.print(F(">> ADS Moderno D1 (Divisor) -> Offset: ")); Serial.print(adsMod.getOffsetD1Ejercito(), 4); Serial.println(F(" V"));
            break;
        case CALIB_ZERO_ADS_MOD_D2_EJ:
            adsMod.calibrarCeroEjercitoD2(32);
            Serial.print(F(">> ADS Moderno D2 (Divisor) -> Offset: ")); Serial.print(adsMod.getOffsetD2Ejercito(), 4); Serial.println(F(" V"));
            break;

        case CALIB_ZERO_ADS_CLAS_D1_DIR:
            adsClas.calibrarCeroDirectoD1(32);
            Serial.print(F(">> ADS Clásico D1 (5V) -> Offset: ")); Serial.print(adsClas.getOffsetD1Directo(), 4); Serial.println(F(" V"));
            break;
        case CALIB_ZERO_ADS_CLAS_D2_DIR:
            adsClas.calibrarCeroDirectoD2(32);
            Serial.print(F(">> ADS Clásico D2 (5V) -> Offset: ")); Serial.print(adsClas.getOffsetD2Directo(), 4); Serial.println(F(" V"));
            break;
        case CALIB_ZERO_ADS_CLAS_D1_EJ:
            adsClas.calibrarCeroEjercitoD1(32);
            Serial.print(F(">> ADS Clásico D1 (Divisor) -> Offset: ")); Serial.print(adsClas.getOffsetD1Ejercito(), 4); Serial.println(F(" V"));
            break;
        case CALIB_ZERO_ADS_CLAS_D2_EJ:
            adsClas.calibrarCeroEjercitoD2(32);
            Serial.print(F(">> ADS Clásico D2 (Divisor) -> Offset: ")); Serial.print(adsClas.getOffsetD2Ejercito(), 4); Serial.println(F(" V"));
            break;

        case CALIB_ZERO_INA1_CORRIENTE:
            ina1.calibrarCeroCorriente(32);
            Serial.print(F(">> INA219 1 -> Offset Corriente: ")); Serial.print(ina1.getOffsetCorriente(), 4); Serial.println(F(" mA"));
            break;
        case CALIB_ZERO_INA1_VBUS:
            ina1.calibrarCeroVBus(32);
            Serial.print(F(">> INA219 1 -> Offset V_Bus: ")); Serial.print(ina1.getOffsetVBus(), 4); Serial.println(F(" V"));
            break;

        case CALIB_ZERO_INA2_CORRIENTE:
            ina2.calibrarCeroCorriente(32);
            Serial.print(F(">> INA219 2 -> Offset Corriente: ")); Serial.print(ina2.getOffsetCorriente(), 4); Serial.println(F(" mA"));
            break;
        case CALIB_ZERO_INA2_VBUS:
            ina2.calibrarCeroVBus(32);
            Serial.print(F(">> INA219 2 -> Offset V_Bus: ")); Serial.print(ina2.getOffsetVBus(), 4); Serial.println(F(" V"));
            break;

        default:
            break;
    }

    CalibStorage::guardar(rtc, adsMod, adsClas, ina1, ina2);
}

void MenuController::aplicarFactorK(CalibAccion accion, float valor, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    if (valor <= 0.0001f) {
        Serial.println(F("\n[!] Valor inválido. El factor K debe ser un número positivo mayor que 0."));
        return;
    }

    switch (accion) {
        case CALIB_FACTOR_K_MOD_D1:
            adsMod.setFactoresK(valor, adsMod.getFactorK_D2());
            Serial.print(F("\n>> ADS Moderno D1 -> Nuevo Factor K: ")); Serial.println(valor, 4);
            break;
        case CALIB_FACTOR_K_MOD_D2:
            adsMod.setFactoresK(adsMod.getFactorK_D1(), valor);
            Serial.print(F("\n>> ADS Moderno D2 -> Nuevo Factor K: ")); Serial.println(valor, 4);
            break;
        case CALIB_FACTOR_K_CLAS_D1:
            adsClas.setFactoresK(valor, adsClas.getFactorK_D2());
            Serial.print(F("\n>> ADS Clásico D1 -> Nuevo Factor K: ")); Serial.println(valor, 4);
            break;
        case CALIB_FACTOR_K_CLAS_D2:
            adsClas.setFactoresK(adsClas.getFactorK_D1(), valor);
            Serial.print(F("\n>> ADS Clásico D2 -> Nuevo Factor K: ")); Serial.println(valor, 4);
            break;
        case CALIB_FACTOR_K_INA1_I:
            ina1.setFactorK_I(valor);
            Serial.print(F("\n>> INA219 1 -> Nuevo Factor K Corriente: ")); Serial.println(valor, 4);
            break;
        case CALIB_FACTOR_K_INA2_I:
            ina2.setFactorK_I(valor);
            Serial.print(F("\n>> INA219 2 -> Nuevo Factor K Corriente: ")); Serial.println(valor, 4);
            break;
        default:
            break;
    }

    CalibStorage::guardar(rtc, adsMod, adsClas, ina1, ina2);
}

bool MenuController::validarHardware(SystemConfig &cfg, DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    bool ok = true;
    if (cfg.ds3231_presente && !rtc.checkConnection()) { Serial.println(F("ERROR: Módulo DS3231 (0x57/0x68) NO RESPONDE.")); ok = false; }
    if (cfg.ads_moderno_activo && !adsMod.checkConnection()) { Serial.println(F("ERROR: ADS1115 Moderno (0x48) NO RESPONDE.")); ok = false; }
    if (cfg.ads_clasico_activo && !adsClas.checkConnection()) { Serial.println(F("ERROR: ADS1115 Clásico (0x4A) NO RESPONDE.")); ok = false; }
    if (cfg.ina_fabrica1_activo && !ina1.checkConnection()) { Serial.println(F("ERROR: INA219 1 (0x40) NO RESPONDE.")); ok = false; }
    if (cfg.ina_fabrica2_activo && !ina2.checkConnection()) { Serial.println(F("ERROR: INA219 2 (0x41) NO RESPONDE.")); ok = false; }
    return ok;
}

void MenuController::procesarMenu(SystemConfig &cfg, bool &midiendo, unsigned long &tiempoInicio, 
                                  DS3231 &rtc, MedidorADS &adsMod, MedidorADS &adsClas, MedidorINA219 &ina1, MedidorINA219 &ina2) {
    if (!Serial.available()) return;

    // Buffer reader for numeric inputs
    if (estadoActual == MSTATE_INGRESAR_FACTOR_K || 
        estadoActual == MSTATE_INGRESAR_COTA_INF || 
        estadoActual == MSTATE_INGRESAR_COTA_SUP) {
        
        char ch = Serial.read();
        if (ch == '\r' || ch == '\n') {
            if (bufferIdx > 0) {
                bufferEntrada[bufferIdx] = '\0';
                float num = atof(bufferEntrada);

                if (estadoActual == MSTATE_INGRESAR_FACTOR_K) {
                    aplicarFactorK(accionPendiente, num, rtc, adsMod, adsClas, ina1, ina2);
                    accionPendiente = CALIB_NINGUNA;
                    estadoActual = MSTATE_MENU_CALIBRACION;
                    imprimirMenuCalibracion();
                } else if (estadoActual == MSTATE_INGRESAR_COTA_INF) {
                    cfg.cota_inferior = num;
                    Serial.print(F("\n>> Cota Inferior fijada en: ")); Serial.println(cfg.cota_inferior, 4);
                    estadoActual = MSTATE_MENU_PLOTTER;
                    imprimirMenuPlotter(cfg);
                } else if (estadoActual == MSTATE_INGRESAR_COTA_SUP) {
                    cfg.cota_superior = num;
                    Serial.print(F("\n>> Cota Superior fijada en: ")); Serial.println(cfg.cota_superior, 4);
                    estadoActual = MSTATE_MENU_PLOTTER;
                    imprimirMenuPlotter(cfg);
                }
                bufferIdx = 0;
            }
        } else if (bufferIdx < sizeof(bufferEntrada) - 1) {
            if ((ch >= '0' && ch <= '9') || ch == '.' || ch == '-') {
                bufferEntrada[bufferIdx++] = ch;
                Serial.print(ch); // Local terminal echo
            }
        }
        return;
    }

    char c = Serial.read();
    if (c == '\n' || c == '\r') return;

    switch (estadoActual) {
        case MSTATE_CONFIG_SELECCION_MODULOS:
            if (c == '1') {
                if (cfg.ads_moderno_presente) cfg.ads_moderno_activo = !cfg.ads_moderno_activo;
                else Serial.println(F("\n[!] ADS Moderno no detectado."));
                imprimirMenuSeleccionModulos(cfg);
            }
            else if (c == '2') {
                if (cfg.ads_clasico_presente) cfg.ads_clasico_activo = !cfg.ads_clasico_activo;
                else Serial.println(F("\n[!] ADS Clásico no detectado."));
                imprimirMenuSeleccionModulos(cfg);
            }
            else if (c == '3') {
                if (cfg.ina_fabrica1_presente) cfg.ina_fabrica1_activo = !cfg.ina_fabrica1_activo;
                else Serial.println(F("\n[!] INA219 1 no detectado."));
                imprimirMenuSeleccionModulos(cfg);
            }
            else if (c == '4') {
                if (cfg.ina_fabrica2_presente) cfg.ina_fabrica2_activo = !cfg.ina_fabrica2_activo;
                else Serial.println(F("\n[!] INA219 2 no detectado."));
                imprimirMenuSeleccionModulos(cfg);
            }
            else if (c == '0') {
                if (!cfg.ads_moderno_activo && !cfg.ads_clasico_activo && !cfg.ina_fabrica1_activo && !cfg.ina_fabrica2_activo) {
                    Serial.println(F("\n[!] ERROR: Debe activar al menos 1 módulo."));
                    imprimirMenuSeleccionModulos(cfg);
                } else {
                    if (cfg.ads_moderno_activo) {
                        estadoActual = MSTATE_CONFIG_ADS_MODERNO;
                        imprimirMenuADSModerno(cfg);
                    } else if (cfg.ads_clasico_activo) {
                        estadoActual = MSTATE_CONFIG_ADS_CLASICO;
                        imprimirMenuADSClasico(cfg);
                    } else {
                        estadoActual = MSTATE_IDLE;
                        imprimirMenuPrincipal(cfg);
                    }
                }
            }
            break;

        case MSTATE_CONFIG_ADS_MODERNO:
            if (c == '1') { cfg.ads_moderno_usa_ejercito = false; imprimirMenuADSModerno(cfg); }
            else if (c == '2') { cfg.ads_moderno_usa_ejercito = true; imprimirMenuADSModerno(cfg); }
            else if (c == '0') {
                adsMod.setModoEjercito(cfg.ads_moderno_usa_ejercito);
                if (cfg.ads_clasico_activo) {
                    estadoActual = MSTATE_CONFIG_ADS_CLASICO;
                    imprimirMenuADSClasico(cfg);
                } else {
                    estadoActual = MSTATE_IDLE;
                    imprimirMenuPrincipal(cfg);
                }
            }
            break;

        case MSTATE_CONFIG_ADS_CLASICO:
            if (c == '1') { cfg.ads_clasico_usa_ejercito = false; imprimirMenuADSClasico(cfg); }
            else if (c == '2') { cfg.ads_clasico_usa_ejercito = true; imprimirMenuADSClasico(cfg); }
            else if (c == '0') {
                adsClas.setModoEjercito(cfg.ads_clasico_usa_ejercito);
                estadoActual = MSTATE_IDLE;
                imprimirMenuPrincipal(cfg);
            }
            break;

        case MSTATE_IDLE:
            if (c == '1') {
                if (!midiendo) {
                    Serial.println(F("\nVerificando enlace I2C de módulos..."));
                    if (validarHardware(cfg, rtc, adsMod, adsClas, ina1, ina2)) {
                        midiendo = true;
                        tiempoInicio = millis();
                        cfg.encabezado_impreso = false;

                        if (cfg.ds3231_presente) rtc.init();
                        if (cfg.ads_moderno_activo) adsMod.init();
                        if (cfg.ads_clasico_activo) adsClas.init();
                        if (cfg.ina_fabrica1_activo) ina1.init();
                        if (cfg.ina_fabrica2_activo) ina2.init();

                        Serial.println(F("\n>>> MEDICIÓN INICIADA <<<"));
                    } else {
                        Serial.println(F(">>> CANCELADO POR FALLA DE HARDWARE. Presione 'C' para reconfigurar. <<<"));
                    }
                } else {
                    midiendo = false;
                    Serial.println(F("\n>>> MEDICIÓN DETENIDA <<<"));
                    imprimirMenuPrincipal(cfg);
                }
            }
            else if (c == '2') {
                // Toggle mode cycle: Columnas -> Recuadro -> Plotter -> Columnas
                if (cfg.modo_salida == LOG_COLUMNAS) cfg.modo_salida = LOG_RECUADRO;
                else if (cfg.modo_salida == LOG_RECUADRO) cfg.modo_salida = LOG_PLOTTER;
                else cfg.modo_salida = LOG_COLUMNAS;

                cfg.encabezado_impreso = false;
                Serial.print(F("\nModo de Salida cambiado a: "));
                if (cfg.modo_salida == LOG_COLUMNAS) Serial.println(F("Columnas (Tabulado)"));
                else if (cfg.modo_salida == LOG_RECUADRO) Serial.println(F("Recuadro Diagnóstico"));
                else Serial.println(F("Modo Plotter (CSV puro)"));
            }
            else if (c == 'P' || c == 'p') {
                midiendo = false;
                estadoActual = MSTATE_MENU_PLOTTER;
                imprimirMenuPlotter(cfg);
            }
            else if (c == 'K' || c == 'k') {
                midiendo = false;
                estadoActual = MSTATE_MENU_CALIBRACION;
                imprimirMenuCalibracion();
            }
            else if (c == 'C' || c == 'c') {
                midiendo = false;
                iniciarConfiguracion(cfg, rtc, adsMod, adsClas, ina1, ina2);
            }
            break;

        case MSTATE_MENU_PLOTTER:
            if (c == '1') {
                cfg.plotter_con_cotas = !cfg.plotter_con_cotas;
                cfg.encabezado_impreso = false;
                imprimirMenuPlotter(cfg);
            }
            else if (c == '2') {
                estadoActual = MSTATE_INGRESAR_COTA_INF;
                Serial.print(F("\nIngrese Cota Inferior (ej: 0.0) y presione ENTER: "));
                bufferIdx = 0;
            }
            else if (c == '3') {
                estadoActual = MSTATE_INGRESAR_COTA_SUP;
                Serial.print(F("\nIngrese Cota Superior (ej: 15.0) y presione ENTER: "));
                bufferIdx = 0;
            }
            else if (c == '0') {
                estadoActual = MSTATE_IDLE;
                imprimirMenuPrincipal(cfg);
            }
            break;

        case MSTATE_MENU_CALIBRACION:
            if (c == '1') { accionPendiente = CALIB_ZERO_ADS_MOD_D1_DIR; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == '2') { accionPendiente = CALIB_ZERO_ADS_MOD_D2_DIR; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == '3') { accionPendiente = CALIB_ZERO_ADS_MOD_D1_EJ; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == '4') { accionPendiente = CALIB_ZERO_ADS_MOD_D2_EJ; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == '5') { accionPendiente = CALIB_ZERO_ADS_CLAS_D1_DIR; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == '6') { accionPendiente = CALIB_ZERO_ADS_CLAS_D2_DIR; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == '7') { accionPendiente = CALIB_ZERO_ADS_CLAS_D1_EJ; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == '8') { accionPendiente = CALIB_ZERO_ADS_CLAS_D2_EJ; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == '9') { accionPendiente = CALIB_ZERO_INA1_CORRIENTE; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == 'A' || c == 'a') { accionPendiente = CALIB_ZERO_INA1_VBUS; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == 'B' || c == 'b') { accionPendiente = CALIB_ZERO_INA2_CORRIENTE; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == 'D' || c == 'd') { accionPendiente = CALIB_ZERO_INA2_VBUS; estadoActual = MSTATE_CONFIRMAR_CALIBRACION_CERO; mostrarInstruccionesCero(accionPendiente); }
            else if (c == 'E' || c == 'e') { accionPendiente = CALIB_FACTOR_K_MOD_D1; estadoActual = MSTATE_INGRESAR_FACTOR_K; mostrarInstruccionesFactorK(accionPendiente, adsMod, adsClas, ina1, ina2); }
            else if (c == 'F' || c == 'f') { accionPendiente = CALIB_FACTOR_K_MOD_D2; estadoActual = MSTATE_INGRESAR_FACTOR_K; mostrarInstruccionesFactorK(accionPendiente, adsMod, adsClas, ina1, ina2); }
            else if (c == 'G' || c == 'g') { accionPendiente = CALIB_FACTOR_K_CLAS_D1; estadoActual = MSTATE_INGRESAR_FACTOR_K; mostrarInstruccionesFactorK(accionPendiente, adsMod, adsClas, ina1, ina2); }
            else if (c == 'H' || c == 'h') { accionPendiente = CALIB_FACTOR_K_CLAS_D2; estadoActual = MSTATE_INGRESAR_FACTOR_K; mostrarInstruccionesFactorK(accionPendiente, adsMod, adsClas, ina1, ina2); }
            else if (c == 'I' || c == 'i') { accionPendiente = CALIB_FACTOR_K_INA1_I; estadoActual = MSTATE_INGRESAR_FACTOR_K; mostrarInstruccionesFactorK(accionPendiente, adsMod, adsClas, ina1, ina2); }
            else if (c == 'J' || c == 'j') { accionPendiente = CALIB_FACTOR_K_INA2_I; estadoActual = MSTATE_INGRESAR_FACTOR_K; mostrarInstruccionesFactorK(accionPendiente, adsMod, adsClas, ina1, ina2); }
            else if (c == 'V' || c == 'v') {
                CalibStorage::imprimirCalibraciones(adsMod, adsClas, ina1, ina2);
                imprimirMenuCalibracion();
            }
            else if (c == 'L' || c == 'l') {
                CalibStorage::cargar(rtc, adsMod, adsClas, ina1, ina2);
                imprimirMenuCalibracion();
            }
            else if (c == 'R' || c == 'r') {
                CalibStorage::resetearEEPROM(rtc, adsMod, adsClas, ina1, ina2);
                imprimirMenuCalibracion();
            }
            else if (c == '0') {
                estadoActual = MSTATE_IDLE;
                imprimirMenuPrincipal(cfg);
            }
            break;

        case MSTATE_CONFIRMAR_CALIBRACION_CERO:
            if (c == 'S' || c == 's') {
                ejecutarCalibracionCero(accionPendiente, rtc, adsMod, adsClas, ina1, ina2);
                accionPendiente = CALIB_NINGUNA;
                estadoActual = MSTATE_MENU_CALIBRACION;
                imprimirMenuCalibracion();
            }
            else if (c == 'C' || c == 'c') {
                Serial.println(F("\n>> Calibración cancelada."));
                accionPendiente = CALIB_NINGUNA;
                estadoActual = MSTATE_MENU_CALIBRACION;
                imprimirMenuCalibracion();
            }
            break;

        default:
            break;
    }
}