# Resumen del Proyecto: Multímetro con Arduino (Versión 0.9 PI)

## 1. Objetivo del Proyecto
Desarrollo de un sistema de adquisición de datos y multímetro digital de alta precisión y robustez para laboratorio, diseñado específicamente sobre la arquitectura de un **Arduino UNO R4 WiFi**.

## 2. Hardware Principal
* **ADS1115 (Moderno 0x48 con buffers MCP6002 y Clásico 0x4A):** Utilizados para la medición de voltaje diferencial con autorrango inteligente y divisores resistivos independientes ("Ejército Resistivo").
* **INA219 (Direcciones 0x40 y 0x41):** Monitores dedicados al registro de corriente, voltaje de bus y potencia en alta y baja escala.
* **Módulo DS3231:** Incorpora un reloj de tiempo real (RTC), sensor de temperatura y una memoria EEPROM externa (AT24C32) para almacenamiento no volátil.

## 3. Características Metrológicas y de Software (v0.9 PI)
* **Calibración desacoplada:** Calibración de cero independiente canal por canal y gestión de factores de escala ($K$) para divisores y shunts.
* **Persistencia en EEPROM:** Almacenamiento seguro de perfiles de calibración protegido mediante verificación de integridad por Checksum.
* **Modos de Visualización Serial:** Soporta salidas en formato de columnas tabulares, recuadros de diagnóstico y un modo Plotter (CSV puro con cotas configurables) para graficación en tiempo real.
* **Control Interactivo:** Sistema de menús no bloqueantes administrados por comandos seriales para configurar el hardware activo, calibrar ceros y alternar modos de visualización.
