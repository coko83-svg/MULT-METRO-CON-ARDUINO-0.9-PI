<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1560 1020" width="100%" height="100%">
  <defs>
    <style>
      .bg { fill: #0b0f19; }
      .title { font-family: 'Segoe UI', system-ui, -apple-system, sans-serif; font-size: 24px; font-weight: 700; fill: #f8fafc; }
      .subtitle { font-family: 'Segoe UI', system-ui, -apple-system, sans-serif; font-size: 13px; fill: #94a3b8; }
      .module-card { fill: #131d31; stroke: #263554; stroke-width: 2px; rx: 8px; }
      .module-header-arduino { fill: #008184; rx: 8px 8px 0 0; }
      .module-header-ads-mod { fill: #1d4ed8; rx: 8px 8px 0 0; }
      .module-header-ads-clas { fill: #6d28d9; rx: 8px 8px 0 0; }
      .module-header-ina1 { fill: #047857; rx: 8px 8px 0 0; }
      .module-header-ina2 { fill: #0f766e; rx: 8px 8px 0 0; }
      .module-header-rtc { fill: #b45309; rx: 8px 8px 0 0; }
      .module-title { font-family: 'Segoe UI', system-ui, sans-serif; font-size: 14px; font-weight: 700; fill: #ffffff; }
      .module-sub { font-family: 'Segoe UI', system-ui, sans-serif; font-size: 11px; fill: #e2e8f0; opacity: 0.9; }
      
      .subcard { fill: #1a263f; stroke: #33466a; stroke-width: 1.2px; rx: 6px; }
      .subcard-title { font-family: 'Segoe UI', system-ui, sans-serif; font-size: 11px; font-weight: 700; fill: #38bdf8; }
      
      .pin-label { font-family: 'Consolas', 'Courier New', monospace; font-size: 11px; font-weight: 600; fill: #cbd5e1; }
      .pin-note { font-family: 'Segoe UI', system-ui, sans-serif; font-size: 10px; fill: #64748b; }
      .text-small { font-family: 'Segoe UI', system-ui, sans-serif; font-size: 11px; fill: #94a3b8; }
      .text-code { font-family: 'Consolas', monospace; font-size: 11px; fill: #facc15; }
      
      /* Bus lines */
      .wire-vcc { stroke: #ef4444; stroke-width: 2.2px; fill: none; stroke-linecap: round; }
      .wire-gnd { stroke: #64748b; stroke-width: 2.2px; fill: none; stroke-linecap: round; }
      .wire-sda { stroke: #06b6d4; stroke-width: 2.2px; fill: none; stroke-linecap: round; }
      .wire-scl { stroke: #fbbf24; stroke-width: 2.2px; fill: none; stroke-linecap: round; }
      .wire-analog { stroke: #10b981; stroke-width: 1.8px; fill: none; stroke-dasharray: 4,3; }
      .wire-power { stroke: #ec4899; stroke-width: 2.5px; fill: none; }
      
      .dot-vcc { fill: #ef4444; }
      .dot-gnd { fill: #64748b; }
      .dot-sda { fill: #06b6d4; }
      .dot-scl { fill: #fbbf24; }
      .dot-star { fill: #38bdf8; stroke: #f8fafc; stroke-width: 2px; }
      
      .opamp { fill: #1e293b; stroke: #38bdf8; stroke-width: 1.5px; }
      .resistor { fill: #0f172a; stroke: #f59e0b; stroke-width: 1.5px; }
      .diode { fill: #ef4444; stroke: #ef4444; stroke-width: 1.5px; }
      
      .legend-box { fill: #0f172a; stroke: #1e293b; stroke-width: 1.5px; rx: 6px; }
    </style>

    <!-- Markers for arrows -->
    <marker id="arrow-sda" markerWidth="6" markerHeight="6" refX="5" refY="3" orient="auto">
      <path d="M0,0 L0,6 L6,3 z" fill="#06b6d4" />
    </marker>
    <marker id="arrow-scl" markerWidth="6" markerHeight="6" refX="5" refY="3" orient="auto">
      <path d="M0,0 L0,6 L6,3 z" fill="#fbbf24" />
    </marker>
    <marker id="arrow-analog" markerWidth="6" markerHeight="6" refX="5" refY="3" orient="auto">
      <path d="M0,0 L0,6 L6,3 z" fill="#10b981" />
    </marker>
  </defs>

  <!-- Background -->
  <rect width="100%" height="100%" class="bg" />

  <!-- Grid decoration -->
  <g opacity="0.04" stroke="#ffffff" stroke-width="1">
    <pattern id="grid" width="40" height="40" patternUnits="userSpaceOnUse">
      <path d="M 40 0 L 0 0 0 40" fill="none" />
    </pattern>
    <rect width="100%" height="100%" fill="url(#grid)" />
  </g>

  <!-- HEADER -->
  <g transform="translate(50, 45)">
    <text class="title" x="0" y="0">MULTÍMETRO DIGITAL CON ARDUINO UNO R4 WiFi</text>
    <text class="subtitle" x="0" y="24">ARQUITECTURA INTEGRAL DE CONEXIONADO ELÉCTRICO, BUS I2C Y TOPOLOGÍA METROLÓGICA (v0.9 PI)</text>
  </g>

  <!-- ========================================================================= -->
  <!-- 1. ARDUINO UNO R4 WIFI (HOST MASTER)                                      -->
  <!-- ========================================================================= -->
  <g id="arduino" transform="translate(50, 95)">
    <rect width="280" height="295" class="module-card" />
    <rect width="280" height="42" class="module-header-arduino" />
    <text class="module-title" x="14" y="26">ARDUINO UNO R4 WiFi</text>
    <text class="module-sub" x="195" y="26">Renesas RA4M1</text>
    
    <!-- Pin headers representation -->
    <g transform="translate(15, 55)">
      <!-- Power Block -->
      <rect x="0" y="0" width="115" height="110" class="subcard" />
      <text class="subcard-title" x="8" y="18">POWER / ALIMENTACIÓN</text>
      <text class="pin-label" x="10" y="40">+5V  (Riel VCC)</text>
      <text class="pin-label" x="10" y="65">GND  (Tierra Santa)</text>
      <text class="pin-label" x="10" y="90">VIN  (7V - 24V Ext)</text>
      
      <!-- Connectors indicators -->
      <circle cx="95" cy="36" r="4.5" fill="#ef4444" />
      <circle cx="95" cy="61" r="5" class="dot-star" />
      <circle cx="95" cy="86" r="4.5" fill="#e2e8f0" />

      <!-- Digital & I2C Block -->
      <rect x="135" y="0" width="115" height="110" class="subcard" />
      <text class="subcard-title" x="143" y="18">BUS I2C MAESTRO</text>
      <text class="pin-label" x="143" y="40">D18 / SDA</text>
      <text class="pin-label" x="143" y="65">D19 / SCL</text>
      <text class="pin-note" x="143" y="85">Pullups nativos 5V</text>
      <text class="pin-note" x="143" y="98">A4/A5 compartidos</text>

      <circle cx="228" cy="36" r="4.5" fill="#06b6d4" />
      <circle cx="228" cy="61" r="4.5" fill="#fbbf24" />

      <!-- Warning info box -->
      <rect x="0" y="125" width="250" height="95" rx="5" fill="#1e293b" stroke="#334155" />
      <text class="subcard-title" x="10" y="142" fill="#f59e0b">IMPORTANTE METROLOGÍA</text>
      <text class="text-small" x="10" y="160">• GND actúa como nodo estrella de referencia.</text>
      <text class="text-small" x="10" y="176">• No conectar sensores analógicos a A4/A5</text>
      <text class="text-small" x="10" y="190">  cuando el bus Wire esté en operación.</text>
      <text class="text-small" x="10" y="206">• Conversor RA4M1 a 48 MHz con FPU nativa.</text>
    </g>
  </g>

  <!-- ========================================================================= -->
  <!-- 2. TRUNK LINES (POWER & I2C BUS DISTRIBUTION)                             -->
  <!-- ========================================================================= -->
  <!-- Main Backbone lines -->
  <line x1="160" y1="131" x2="1490" y2="131" class="wire-vcc" />
  <line x1="160" y1="156" x2="1490" y2="156" class="wire-gnd" />
  <line x1="293" y1="131" x2="293" y2="175" class="wire-sda" />
  <line x1="293" y1="175" x2="1490" y2="175" class="wire-sda" />
  <line x1="293" y1="156" x2="310" y2="156" class="wire-scl" />
  <line x1="310" y1="156" x2="310" y2="195" class="wire-scl" />
  <line x1="310" y1="195" x2="1490" y2="195" class="wire-scl" />

  <!-- Star ground hub label -->
  <rect x="110" y="200" width="105" height="22" rx="4" fill="#0369a1" />
  <text class="pin-label" x="116" y="215" fill="#ffffff">TIERRA SANTA ★</text>
  <path d="M160,156 L160,200" stroke="#38bdf8" stroke-width="1.8" stroke-dasharray="2,2" />

  <!-- ========================================================================= -->
  <!-- 3. DS3231 RTC + AT24C32 EEPROM (0x68 / 0x57)                              -->
  <!-- ========================================================================= -->
  <g id="ds3231" transform="translate(370, 235)">
    <rect width="250" height="155" class="module-card" />
    <rect width="250" height="38" class="module-header-rtc" />
    <text class="module-title" x="12" y="24">DS3231 RTC + EEPROM</text>
    <text class="module-sub" x="175" y="24">0x68 / 0x57</text>

    <!-- Content -->
    <g transform="translate(15, 50)">
      <text class="pin-label" x="0" y="20">VCC  ─────────── [ 5V ]</text>
      <text class="pin-label" x="0" y="42">GND  ─────────── [ GND ]</text>
      <text class="pin-label" x="0" y="64">SDA  ─────────── [ SDA ]</text>
      <text class="pin-label" x="0" y="86">SCL  ─────────── [ SCL ]</text>
      <rect x="155" y="6" width="68" height="85" rx="4" fill="#1e293b" stroke="#475569" />
      <text class="pin-note" x="160" y="24" fill="#fbbf24">AT24C32</text>
      <text class="pin-note" x="160" y="38">EEPROM</text>
      <text class="pin-note" x="160" y="52">Persistente</text>
      <text class="pin-note" x="160" y="68" fill="#34d399">Magic PI09</text>
      <text class="pin-note" x="160" y="82">Checksum</text>
    </g>

    <!-- Tap connections to bus -->
    <path d="M390,285 L390,131" class="wire-vcc" />
    <circle cx="390" cy="131" r="4" class="dot-vcc" />
    <path d="M410,285 L410,156" class="wire-gnd" />
    <circle cx="410" cy="156" r="4" class="dot-gnd" />
    <path d="M430,285 L430,175" class="wire-sda" />
    <circle cx="430" cy="175" r="4" class="dot-sda" />
    <path d="M450,285 L450,195" class="wire-scl" />
    <circle cx="450" cy="195" r="4" class="dot-scl" />
  </g>

  <!-- ========================================================================= -->
  <!-- 4. INA219 #1 (0x40 - FUENTE A CIRCUITO)                                   -->
  <!-- ========================================================================= -->
  <g id="ina1" transform="translate(660, 235)">
    <rect width="380" height="155" class="module-card" />
    <rect width="380" height="38" class="module-header-ina1" />
    <text class="module-title" x="12" y="24">INA219 #1: FUENTE A CIRCUITO</text>
    <text class="module-sub" x="270" y="24">Dir: 0x40 (A0:O, A1:O)</text>

    <!-- Bus pins -->
    <g transform="translate(15, 50)">
      <text class="pin-label" x="0" y="20">VCC  ────── [ 5V ]</text>
      <text class="pin-label" x="0" y="42">GND  ────── [ GND ]</text>
      <text class="pin-label" x="0" y="64">SDA  ────── [ SDA ]</text>
      <text class="pin-label" x="0" y="86">SCL  ────── [ SCL ]</text>
      
      <!-- Power High Side sensing diagram -->
      <rect x="145" y="5" width="205" height="85" rx="5" fill="#064e3b" stroke="#059669" />
      <text class="subcard-title" x="155" y="22" fill="#6ee7b7">MEDICIÓN HIGH-SIDE (Shunt 0.1Ω)</text>
      <text class="pin-label" x="155" y="42" fill="#f8fafc">VIN+ &lt;── Fuente Positiva (+) [0-26V]</text>
      <text class="pin-label" x="155" y="62" fill="#f8fafc">VIN- ──&gt; Carga / Circuito Ensayo (+)</text>
      <text class="pin-note" x="155" y="80" fill="#a7f3d0">Registro: Corriente (mA) + VBus (V) + P (mW)</text>
    </g>

    <!-- Tap connections to bus -->
    <path d="M680,285 L680,131" class="wire-vcc" />
    <circle cx="680" cy="131" r="4" class="dot-vcc" />
    <path d="M700,285 L700,156" class="wire-gnd" />
    <circle cx="700" cy="156" r="4" class="dot-gnd" />
    <path d="M720,285 L720,175" class="wire-sda" />
    <circle cx="720" cy="175" r="4" class="dot-sda" />
    <path d="M740,285 L740,195" class="wire-scl" />
    <circle cx="740" cy="195" r="4" class="dot-scl" />
  </g>

  <!-- ========================================================================= -->
  <!-- 5. INA219 #2 (0x41 - NODO LIBRE)                                          -->
  <!-- ========================================================================= -->
  <g id="ina2" transform="translate(1080, 235)">
    <rect width="380" height="155" class="module-card" />
    <rect width="380" height="38" class="module-header-ina2" />
    <text class="module-title" x="12" y="24">INA219 #2: NODO LIBRE / ENSAYO</text>
    <text class="module-sub" x="260" y="24">Dir: 0x41 (A0:VCC, A1:O)</text>

    <!-- Bus pins -->
    <g transform="translate(15, 50)">
      <text class="pin-label" x="0" y="20">VCC  ────── [ 5V ]</text>
      <text class="pin-label" x="0" y="42">GND  ────── [ GND ]</text>
      <text class="pin-label" x="0" y="64">SDA  ────── [ SDA ]</text>
      <text class="pin-label" x="0" y="86">SCL  ────── [ SCL ]</text>
      
      <!-- Power High Side sensing diagram -->
      <rect x="145" y="5" width="205" height="85" rx="5" fill="#134e4a" stroke="#0d9488" />
      <text class="subcard-title" x="155" y="22" fill="#5eead4">PUNTO DE INSERCIÓN LIBRE</text>
      <text class="pin-label" x="155" y="42" fill="#f8fafc">VIN+ &lt;── Riel Positivo Bajo Ensayo</text>
      <text class="pin-label" x="155" y="62" fill="#f8fafc">VIN- ──&gt; Retorno a Nodo Subordinado</text>
      <text class="pin-note" x="155" y="80" fill="#99f6e4">Shunt intercambiable / Calibración K_I indep.</text>
    </g>

    <!-- Tap connections to bus -->
    <path d="M1100,285 L1100,131" class="wire-vcc" />
    <circle cx="1100" cy="131" r="4" class="dot-vcc" />
    <path d="M1120,285 L1120,156" class="wire-gnd" />
    <circle cx="1120" cy="156" r="4" class="dot-gnd" />
    <path d="M1140,285 L1140,175" class="wire-sda" />
    <circle cx="1140" cy="175" r="4" class="dot-sda" />
    <path d="M1160,285 L1160,195" class="wire-scl" />
    <circle cx="1160" cy="195" r="4" class="dot-scl" />
  </g>

  <!-- ========================================================================= -->
  <!-- 6. ADS1115 MODERNO (0x48) CON BUFFERS ACTIVOS MCP6002                     -->
  <!-- ========================================================================= -->
  <g id="ads-moderno" transform="translate(50, 430)">
    <rect width="690" height="475" class="module-card" />
    <rect width="690" height="42" class="module-header-ads-mod" />
    <text class="module-title" x="14" y="27">ADS1115 MODERNO (Dir: 0x48 | ADDR -&gt; GND)</text>
    <text class="module-sub" x="430" y="27">Front-End con Buffers MCP6002 &amp; Divisor 01</text>

    <!-- Block Inside -->
    <!-- I2C Pin Header of ADS1115 -->
    <g transform="translate(20, 60)">
      <rect x="0" y="0" width="135" height="150" class="subcard" />
      <text class="subcard-title" x="10" y="20">ADS1115 CORE</text>
      <text class="pin-label" x="10" y="44">VDD  ── [ 5V ]</text>
      <text class="pin-label" x="10" y="66">GND  ── [ GND ]</text>
      <text class="pin-label" x="10" y="88">SCL  ── [ SCL ]</text>
      <text class="pin-label" x="10" y="110">SDA  ── [ SDA ]</text>
      <text class="pin-label" x="10" y="132" fill="#38bdf8">ADDR ── [ GND ]</text>

      <!-- ADC Analog inputs on the chip -->
      <rect x="0" y="165" width="135" height="175" class="subcard" />
      <text class="subcard-title" x="10" y="185">ENTRADAS ADC</text>
      <text class="pin-label" x="10" y="210">A0 (D1+ in)</text>
      <text class="pin-label" x="10" y="245">A1 (D1- in)</text>
      <text class="pin-label" x="10" y="280">A2 (D2+ in)</text>
      <text class="pin-label" x="10" y="315">A3 (D2- in)</text>
      <text class="pin-note" x="10" y="332">Autorango 2/3x, 1x, 2x</text>
    </g>

    <!-- MCP6002 Buffer Stage Representation -->
    <g transform="translate(180, 60)">
      <rect x="0" y="0" width="220" height="340" class="subcard" />
      <text class="subcard-title" x="12" y="22">MCP6002 BUFFER UNITARIO (RAIL-TO-RAIL)</text>
      <text class="pin-note" x="12" y="36">Protección activa: Sat. física máx 5.0V / Mín 0.0V</text>

      <!-- Opamp 1 (A0 Buffer) -->
      <g transform="translate(25, 55)">
        <polygon points="40,25 0,5 0,45" class="opamp" />
        <text class="pin-label" x="4" y="18">+</text>
        <text class="pin-label" x="4" y="38">-</text>
        <!-- Feedback -->
        <path d="M40,25 L55,25 L55,42 L12,42 L12,35" fill="none" stroke="#38bdf8" stroke-width="1.2" />
        <line x1="-15" y1="15" x2="0" y2="15" stroke="#10b981" stroke-width="1.8" />
        <line x1="40" y1="25" x2="95" y2="25" stroke="#10b981" stroke-width="1.8" marker-end="url(#arrow-analog)" />
        <text class="pin-note" x="60" y="18">-> A0</text>
      </g>

      <!-- Opamp 2 (A1 Buffer) -->
      <g transform="translate(25, 125)">
        <polygon points="40,25 0,5 0,45" class="opamp" />
        <text class="pin-label" x="4" y="18">+</text>
        <text class="pin-label" x="4" y="38">-</text>
        <!-- Feedback -->
        <path d="M40,25 L55,25 L55,42 L12,42 L12,35" fill="none" stroke="#38bdf8" stroke-width="1.2" />
        <line x1="-15" y1="15" x2="0" y2="15" stroke="#10b981" stroke-width="1.8" />
        <line x1="40" y1="25" x2="95" y2="25" stroke="#10b981" stroke-width="1.8" marker-end="url(#arrow-analog)" />
        <text class="pin-note" x="60" y="18">-> A1</text>
      </g>

      <!-- Opamp 3 & 4 (D2 Channel: A2/A3) -->
      <g transform="translate(25, 205)">
        <rect x="0" y="0" width="170" height="65" rx="4" fill="#0f172a" stroke="#334155" />
        <text class="pin-label" x="10" y="24" fill="#38bdf8">Canal D2 (U2 MCP6002):</text>
        <text class="text-small" x="10" y="42">• Seguidor Buffer D2+ hacia Pin A2</text>
        <text class="text-small" x="10" y="56">• Seguidor Buffer D2- hacia Pin A3</text>
      </g>

      <!-- Decoupling Cap -->
      <text class="pin-note" x="12" y="315" fill="#facc15">C_bypass: 100nF Cerámico entre VDD y VSS</text>
    </g>

    <!-- Ejército Resistivo 01 (33k / 10k) -->
    <g transform="translate(425, 60)">
      <rect x="0" y="0" width="245" height="340" class="subcard" />
      <text class="subcard-title" x="12" y="22">EJÉRCITO RESISTIVO 01 (DIVISOR)</text>
      <text class="pin-note" x="12" y="36">Extensión hasta 21.5V (K nom = 4.3000)</text>

      <g transform="translate(15, 50)">
        <!-- Divisor Channel D1+ -->
        <text class="pin-label" x="0" y="18" fill="#ec4899">Borne (+) D1 [0 - 21.5V]</text>
        <rect x="0" y="28" width="60" height="22" class="resistor" />
        <text class="pin-label" x="12" y="43" fill="#f59e0b">33 kΩ</text>
        <text class="pin-note" x="70" y="42">0.1% Tol</text>

        <circle cx="120" cy="39" r="3.5" fill="#10b981" />
        <line x1="60" y1="39" x2="150" y2="39" stroke="#10b981" stroke-width="1.8" />
        <text class="pin-note" x="135" y="32">-> Al Buffer D1(+)</text>

        <!-- Shunt resistor to GND -->
        <rect x="100" y="65" width="40" height="22" class="resistor" />
        <text class="pin-label" x="105" y="80" fill="#f59e0b">10k</text>
        <path d="M120,39 L120,65" stroke="#10b981" stroke-width="1.5" />
        <path d="M120,87 L120,105" stroke="#64748b" stroke-width="1.5" />
        <text class="pin-note" x="80" y="118">Tierra (GND)</text>
        <circle cx="120" cy="105" r="3" fill="#64748b" />
      </g>

      <g transform="translate(15, 185)">
        <!-- Divisor Channel D1- -->
        <text class="pin-label" x="0" y="18" fill="#ec4899">Borne (-) D1 [Retorno Diferencial]</text>
        <rect x="0" y="28" width="60" height="22" class="resistor" />
        <text class="pin-label" x="12" y="43" fill="#f59e0b">33 kΩ</text>
        
        <circle cx="120" cy="39" r="3.5" fill="#10b981" />
        <line x1="60" y1="39" x2="150" y2="39" stroke="#10b981" stroke-width="1.8" />
        <text class="pin-note" x="135" y="32">-> Al Buffer D1(-)</text>

        <rect x="100" y="65" width="40" height="22" class="resistor" />
        <text class="pin-label" x="105" y="80" fill="#f59e0b">10k</text>
        <path d="M120,39 L120,65" stroke="#10b981" stroke-width="1.5" />
        <path d="M120,87 L120,105" stroke="#64748b" stroke-width="1.5" />
        <circle cx="120" cy="105" r="3" fill="#64748b" />
      </g>

      <!-- Note on pairing -->
      <text class="pin-note" x="12" y="325" fill="#38bdf8">★ Resistencias 0.1% apareadas para no degradar CMRR</text>
    </g>

    <!-- Bottom info box -->
    <rect x="20" y="415" width="650" height="42" rx="4" fill="#0f172a" stroke="#263554" />
    <text class="text-small" x="30" y="440" fill="#cbd5e1">
      <tspan fill="#34d399">✓ Ventaja Metrológica:</tspan> El buffer MCP6002 presenta impedancia &gt; 10¹² Ω. Elimina la caída de tensión en el divisor y protege las entradas del ADC.
    </text>
  </g>

  <!-- ========================================================================= -->
  <!-- 7. ADS1115 CLÁSICO (0x4A) CON CLAMPING SCHOTTKY                           -->
  <!-- ========================================================================= -->
  <g id="ads-clasico" transform="translate(770, 430)">
    <rect width="740" height="475" class="module-card" />
    <rect width="740" height="42" class="module-header-ads-clas" />
    <text class="module-title" x="14" y="27">ADS1115 CLÁSICO (Dir: 0x4A | ADDR -&gt; SDA)</text>
    <text class="module-sub" x="480" y="27">Protección Pasiva Clamping &amp; Divisor 02</text>

    <!-- I2C Pin Header of ADS1115 Clásico -->
    <g transform="translate(20, 60)">
      <rect x="0" y="0" width="135" height="150" class="subcard" />
      <text class="subcard-title" x="10" y="20">ADS1115 CORE</text>
      <text class="pin-label" x="10" y="44">VDD  ── [ 5V ]</text>
      <text class="pin-label" x="10" y="66">GND  ── [ GND ]</text>
      <text class="pin-label" x="10" y="88">SCL  ── [ SCL ]</text>
      <text class="pin-label" x="10" y="110">SDA  ── [ SDA ]</text>
      <text class="pin-label" x="10" y="132" fill="#c084fc">ADDR ── [ SDA ]</text>

      <!-- ADC Analog inputs on the chip -->
      <rect x="0" y="165" width="135" height="175" class="subcard" />
      <text class="subcard-title" x="10" y="185">ENTRADAS ADC</text>
      <text class="pin-label" x="10" y="210">A0 (D1+ in)</text>
      <text class="pin-label" x="10" y="245">A1 (D1- in)</text>
      <text class="pin-label" x="10" y="280">A2 (D2+ in)</text>
      <text class="pin-label" x="10" y="315">A3 (D2- in)</text>
      <text class="pin-note" x="10" y="332">Filtro R-C &amp; Diodos</text>
    </g>

    <!-- Clamping Protection Stage -->
    <g transform="translate(180, 60)">
      <rect x="0" y="0" width="265" height="340" class="subcard" />
      <text class="subcard-title" x="12" y="22">RED CLAMPING SCHOTTKY (BAT43 / BAT54)</text>
      <text class="pin-note" x="12" y="36">Recorta sobretensiones a: GND - 0.3V y 5V + 0.3V</text>

      <!-- Channel A0 Clamping -->
      <g transform="translate(15, 55)">
        <text class="pin-label" x="0" y="14" fill="#a78bfa">Entrada Punta (+)</text>
        <rect x="0" y="25" width="50" height="20" class="resistor" />
        <text class="pin-label" x="8" y="39" fill="#f59e0b">1 kΩ</text>

        <!-- Node -->
        <circle cx="85" cy="35" r="3.5" fill="#10b981" />
        <line x1="50" y1="35" x2="150" y2="35" stroke="#10b981" stroke-width="1.8" />
        <text class="pin-note" x="155" y="38">-> A0 ADC</text>

        <!-- Diode to 5V -->
        <line x1="85" y1="35" x2="85" y2="10" stroke="#ef4444" stroke-width="1.2" />
        <polygon points="85,10 80,18 90,18" class="diode" />
        <line x1="78" y1="10" x2="92" y2="10" stroke="#ef4444" stroke-width="1.5" />
        <text class="pin-note" x="95" y="14" fill="#ef4444">+5V</text>

        <!-- Diode to GND -->
        <line x1="85" y1="35" x2="85" y2="60" stroke="#64748b" stroke-width="1.2" />
        <polygon points="85,60 80,52 90,52" fill="#64748b" stroke="#64748b" />
        <line x1="78" y1="60" x2="92" y2="60" stroke="#64748b" stroke-width="1.5" />
        <text class="pin-note" x="95" y="64" fill="#64748b">GND</text>
      </g>

      <!-- Channel A1 Clamping -->
      <g transform="translate(15, 145)">
        <text class="pin-label" x="0" y="14" fill="#a78bfa">Entrada Punta (-)</text>
        <rect x="0" y="25" width="50" height="20" class="resistor" />
        <text class="pin-label" x="8" y="39" fill="#f59e0b">1 kΩ</text>

        <!-- Node -->
        <circle cx="85" cy="35" r="3.5" fill="#10b981" />
        <line x1="50" y1="35" x2="150" y2="35" stroke="#10b981" stroke-width="1.8" />
        <text class="pin-note" x="155" y="38">-> A1 ADC</text>

        <polygon points="85,10 80,18 90,18" class="diode" />
        <line x1="78" y1="10" x2="92" y2="10" stroke="#ef4444" stroke-width="1.5" />
        <text class="pin-note" x="95" y="14" fill="#ef4444">+5V</text>

        <polygon points="85,60 80,52 90,52" fill="#64748b" stroke="#64748b" />
        <line x1="78" y1="60" x2="92" y2="60" stroke="#64748b" stroke-width="1.5" />
        <text class="pin-note" x="95" y="64" fill="#64748b">GND</text>
      </g>

      <!-- Channel D2 identical notes -->
      <g transform="translate(15, 235)">
        <rect x="0" y="0" width="235" height="55" rx="4" fill="#0f172a" stroke="#334155" />
        <text class="pin-label" x="10" y="20" fill="#c084fc">Canal D2 (A2/A3):</text>
        <text class="text-small" x="10" y="36">• Red idéntica de 1kΩ + diodos para Pin A2 y Pin A3</text>
      </g>

      <text class="pin-note" x="12" y="325" fill="#fbbf24">⚠ La corriente de fuga de los diodos se compensa en soft.</text>
    </g>

    <!-- Ejército Resistivo 02 -->
    <g transform="translate(470, 60)">
      <rect x="0" y="0" width="245" height="340" class="subcard" />
      <text class="subcard-title" x="12" y="22">EJÉRCITO RESISTIVO 02 (DIVISOR)</text>
      <text class="pin-note" x="12" y="36">Divisor Simétrico 33k / 10k Independiente</text>

      <g transform="translate(15, 50)">
        <text class="pin-label" x="0" y="18" fill="#ec4899">Borne (+) D1 [0 - 21.5V]</text>
        <rect x="0" y="28" width="60" height="22" class="resistor" />
        <text class="pin-label" x="12" y="43" fill="#f59e0b">33 kΩ</text>
        <circle cx="120" cy="39" r="3.5" fill="#10b981" />
        <line x1="60" y1="39" x2="140" y2="39" stroke="#10b981" stroke-width="1.8" />
        <text class="pin-note" x="130" y="30">-> Al Clamp A0</text>

        <rect x="100" y="65" width="40" height="22" class="resistor" />
        <text class="pin-label" x="105" y="80" fill="#f59e0b">10k</text>
        <path d="M120,39 L120,65" stroke="#10b981" stroke-width="1.5" />
        <path d="M120,87 L120,105" stroke="#64748b" stroke-width="1.5" />
        <circle cx="120" cy="105" r="3" fill="#64748b" />
      </g>

      <g transform="translate(15, 185)">
        <text class="pin-label" x="0" y="18" fill="#ec4899">Borne (-) D1 [Retorno Divisor]</text>
        <rect x="0" y="28" width="60" height="22" class="resistor" />
        <text class="pin-label" x="12" y="43" fill="#f59e0b">33 kΩ</text>
        <circle cx="120" cy="39" r="3.5" fill="#10b981" />
        <line x1="60" y1="39" x2="140" y2="39" stroke="#10b981" stroke-width="1.8" />
        <text class="pin-note" x="130" y="30">-> Al Clamp A1</text>

        <rect x="100" y="65" width="40" height="22" class="resistor" />
        <text class="pin-label" x="105" y="80" fill="#f59e0b">10k</text>
        <path d="M120,39 L120,65" stroke="#10b981" stroke-width="1.5" />
        <path d="M120,87 L120,105" stroke="#64748b" stroke-width="1.5" />
        <circle cx="120" cy="105" r="3" fill="#64748b" />
      </g>

      <text class="pin-note" x="12" y="325" fill="#a78bfa">Factores K independientes almacenados en EEPROM</text>
    </g>

    <!-- Bottom info box -->
    <rect x="20" y="415" width="700" height="42" rx="4" fill="#0f172a" stroke="#263554" />
    <text class="text-small" x="30" y="440" fill="#cbd5e1">
      <tspan fill="#fbbf24">⚠ Particularidad de direccionamiento:</tspan> El pin ADDR va soldado a SDA para responder en <tspan fill="#facc15">0x4A</tspan> sin colisionar con 0x48.
    </text>
  </g>

  <!-- ========================================================================= -->
  <!-- 8. BUS DROP CONNECTIONS FOR BOTTOM MODULES                                -->
  <!-- ========================================================================= -->
  <!-- Drops to ADS Moderno (0x48) -->
  <path d="M70,490 L70,131" class="wire-vcc" />
  <circle cx="70" cy="131" r="4" class="dot-vcc" />
  <path d="M85,490 L85,156" class="wire-gnd" />
  <circle cx="85" cy="156" r="4" class="dot-gnd" />
  <path d="M100,490 L100,195" class="wire-scl" />
  <circle cx="100" cy="195" r="4" class="dot-scl" />
  <path d="M115,490 L115,175" class="wire-sda" />
  <circle cx="115" cy="175" r="4" class="dot-sda" />

  <!-- Drops to ADS Clásico (0x4A) -->
  <path d="M790,490 L790,131" class="wire-vcc" />
  <circle cx="790" cy="131" r="4" class="dot-vcc" />
  <path d="M805,490 L805,156" class="wire-gnd" />
  <circle cx="805" cy="156" r="4" class="dot-gnd" />
  <path d="M820,490 L820,195" class="wire-scl" />
  <circle cx="820" cy="195" r="4" class="dot-scl" />
  <path d="M835,490 L835,175" class="wire-sda" />
  <circle cx="835" cy="175" r="4" class="dot-sda" />

  <!-- ========================================================================= -->
  <!-- 9. FOOTER & COLOR CONVENTION LEGEND                                       -->
  <!-- ========================================================================= -->
  <g id="legend" transform="translate(50, 930)">
    <rect width="1460" height="55" class="legend-box" />
    <text class="pin-label" x="20" y="32" fill="#ffffff">CÓDIGO DE COLORES:</text>

    <line x1="165" y1="28" x2="195" y2="28" class="wire-vcc" />
    <text class="pin-label" x="205" y="32" fill="#ef4444">+5V VDD</text>

    <line x1="290" y1="28" x2="320" y2="28" class="wire-gnd" />
    <text class="pin-label" x="330" y="32" fill="#94a3b8">GND Tierra Santa</text>

    <line x1="465" y1="28" x2="495" y2="28" class="wire-sda" />
    <text class="pin-label" x="505" y="32" fill="#06b6d4">SDA (Datos I2C)</text>

    <line x1="630" y1="28" x2="660" y2="28" class="wire-scl" />
    <text class="pin-label" x="670" y="32" fill="#fbbf24">SCL (Reloj I2C)</text>

    <line x1="790" y1="28" x2="820" y2="28" class="wire-analog" />
    <text class="pin-label" x="830" y="32" fill="#10b981">Señal ADC Acondicionada</text>

    <line x1="1025" y1="28" x2="1055" y2="28" stroke="#ec4899" stroke-width="2.5" />
    <text class="pin-label" x="1065" y="32" fill="#ec4899">Línea de Prueba / Shunt</text>

    <!-- Project stamp -->
    <text class="pin-note" x="1275" y="32" fill="#64748b">FIRMWARE v0.9 PI | ARDUINO UNO R4</text>
  </g>

</svg>
