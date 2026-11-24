# Misión Meteorito · Controlador físico

**Taller de Diseño de Interfaces · Unidad 2: Interfaces Físicas · Universidad Adolfo Ibáñez · 2026**
**Autor:** Juan Domingo Pastorino (trabajo individual)

🎮 **Demo web (modo prueba con mouse o teclado):** https://juandomingoo.github.io/controlador-fisico-entrega1/
🎬 **Video demostrativo:** [ver video](PEGAR-AQUÍ-EL-LINK-DEL-VIDEO)

![Controlador terminado](docs/img/caja-cerrada.jpg)

---

## Descripción

Controlador físico tipo arcade, hecho con **Arduino Uno**, un **fader** (potenciómetro deslizante) y un **botón arcade**, montado en una caja propia. Se conecta al computador por USB y controla una página web que tiene dos zonas:

- **Misión Meteorito**: un minijuego de naves. El fader mueve la nave hacia arriba y hacia abajo, y el botón dispara.
- **Panel técnico**: muestra en tiempo real el nivel del fader, el estado del botón y un gráfico de la señal. Así se puede comprobar que la lectura es continua, inmediata y sin ruido.

**Experiencia de interacción:** traducir un gesto físico (deslizar y apretar) en una respuesta en pantalla inmediata y fácil de entender, como en los controladores MIDI, los pedales de efectos y las consolas arcade que sirvieron de referencia.

**Público y contexto de uso:** pensado para demostraciones en vivo (en clases, en una muestra o en un stand) donde cualquier persona pueda tomar el controlador y jugar sin explicación previa. El panel técnico está dirigido a quien quiera entender cómo viaja la señal desde el hardware hasta la web.

## Objetivos

1. Construir un controlador con al menos **1 botón y 1 fader**.
2. Soldar la electrónica en una **placa perforada que funcione como shield**, removible y sin protoboard.
3. Lograr una caja **firme y con buen acabado**, que se pueda dar vuelta sin que nada se suelte.
4. Mantener una **comunicación serial estable** entre el Arduino y el computador.
5. Crear un **dashboard web** que muestre el estado de los controles en tiempo real, con un juego para que la demostración sea entretenida.

## Tecnologías, hardware y librerías

| Tipo | Detalle |
|---|---|
| Microcontrolador | Arduino Uno R3 |
| Entrada analógica | Fader deslizante (potenciómetro 10 kΩ, doble, de 6 patitas) |
| Entrada digital | Botón arcade con microswitch (COM / NO / NC) |
| Shield | Placa perforada de 5 × 7 cm, soldada con estaño |
| Caja | Diseñada en **Rhino**, preparada en **Bambu Studio** ⚠️ *completar: material y método de la caja final (impresión 3D en PLA o corte láser en MDF)* |
| Firmware | Arduino IDE 1.8.19, sin librerías externas (`Serial`, `INPUT_PULLUP`, `analogRead`, antirrebote con `millis()`) |
| Web | HTML + CSS + JavaScript en un solo archivo, **Web Serial API** (115200 baudios) y **Canvas 2D** |

## Conexiones

![Diagrama de conexión](docs/img/diagrama-conexion.png)

| Componente | Patita | Pin del Arduino |
|---|---|---|
| Fader | Extremo | 5V |
| Fader | Cursor (la patita que cambia al mover) | A0 |
| Fader | Otro extremo | GND |
| Botón | COM | GND |
| Botón | NO | Pin 2 (`INPUT_PULLUP`, sin resistencia) |

El Arduino envía `boton,fader` unas 50 veces por segundo (por ejemplo `1,768`). El botón tiene antirrebote de 15 ms y el fader se promedia en 8 lecturas para eliminar el ruido.

## Instrucciones de ejecución

1. Abrir `controlador/controlador.ino` en el Arduino IDE.
2. **Herramientas → Placa → Arduino Uno**, y en **Herramientas → Puerto** elegir el COM del Arduino.
3. Subir el código con la flecha **→**.
4. Abrir la demo en **Chrome o Edge** (o `dashboard.html` en local).
5. Apretar **"Conectar controlador"**, elegir el puerto y apretar el botón físico para empezar a jugar.

> Sin Arduino, la página funciona en **modo prueba**: el mouse o las flechas ↑ ↓ mueven la nave y la barra espaciadora dispara.
> Si aparece "Acceso denegado" al subir el código, hay que cerrar la página conectada y el Monitor Serial, porque ocupan el puerto.

## Cómo se juega

- El **fader** mueve la nave y el **botón** dispara.
- Cada meteorito vale **10 puntos**. Las naves enemigas aparecen con el aviso "¡NAVE ENEMIGA!", aguantan 2 disparos y valen **50 puntos**.
- Tienes **3 vidas**. Cada 20 segundos subes de **nivel** y todo se acelera.

## Documentación del proceso

### 1. Ideación
Se evaluaron varias ideas simples: una consola "ON AIR", un interruptor de luz, un pedal de guitarra, un termostato, un cohete y una máquina de café. Se eligió una **caja tipo controlador** con fader y botón, inspirada en controladores MIDI y pedales de efectos, junto con una web de dos zonas: un juego y un panel técnico.

### 2. Prototipo electrónico y pruebas
![Shield soldado](docs/img/shield-soldadura.jpg)

| Problema | Solución |
|---|---|
| El fader tenía **6 patitas sin marcas**, no 3. | Se escribió un código "detective" con `INPUT_PULLUP` para identificar, moviendo el fader, cuál patita era el cursor y cuál el otro extremo. |
| No se sabía cuál patita del botón era cuál. | Una foto de cerca del microswitch mostró que la patita doblada es COM. Si el botón queda invertido, se cambia de patita o se usa `BOTON_INVERTIDO = true`. |
| No había headers para el shield. | Se usaron las puntas metálicas de cables jumper como pines, soldadas a la placa perforada. |
| Error "can't open device COM3". | Se había cambiado de Arduino y el nuevo estaba en COM5. Se eligió el puerto correcto. |
| Error "Acceso denegado" en COM5. | El puerto estaba ocupado por la página o el Monitor Serial. Se cierran antes de subir el código. |

### 3. Iteraciones de la caja
![Caja abierta](docs/img/caja-abierta.jpg)

1. **Caja original en Rhino**: paredes y piso de 0,5 mm y tapa sin fijación. Se corrigió a paredes de 2 mm, con borde en la tapa y holguras.
2. **Caja v2**: 135 × 105 × 60 mm, con tapa atornillada en 4 columnas.
3. **Caja v3**: 121 × 91 × 51 mm, paredes de 1,6 mm y tapa a presión con 2 trabas, para imprimir en unas 2 horas.
4. **Alternativa de corte láser**: 6 piezas con dientes, en MDF de 3 mm.

### 4. Evolución del software
1. Dashboard con el juego de meteoritos, el panel técnico y el modo prueba.
2. Se agregaron **naves enemigas** que cruzan la pantalla y disparan.
3. Se agregó **dificultad progresiva**, con niveles cada 20 segundos.

## Qué mejoraría

- Usar **headers macho** de verdad para el shield, en vez de puntas de cables jumper.
- **Medir las piezas reales** antes de diseñar la caja.
- Dar más tiempo a la fabricación, considerando las horas de impresión y la fila del laboratorio.
- **Marcar en el shield** qué cable va a cada pin.

## Estructura del repositorio

```
controlador-fisico-entrega1/
├── index.html                 # redirige al dashboard (para GitHub Pages)
├── dashboard.html             # juego + panel técnico (Web Serial)
├── controlador/
│   └── controlador.ino        # código del Arduino
├── docs/img/                  # fotos y diagrama del proceso
└── README.md
```
