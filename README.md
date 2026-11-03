# Controlador físico – Misión Meteorito

**Diseño de Interfaces · Unidad 2 · Entrega 1 (UAI)**
Autor: Juan Domingo Pastorino

Controlador físico hecho con Arduino Uno, un **fader** (potenciómetro deslizante) y un **botón arcade**.
Se conecta al computador por USB y controla un **dashboard web** con un minijuego: el fader mueve la nave y el botón dispara.

▶️ **Jugar en línea:** _(pega aquí el link de GitHub Pages)_
🎥 **Video:** _(pega aquí el link del video)_

---

## Cómo funciona

| Control físico | Qué hace en la página |
|---|---|
| Fader (A0) | Mueve la nave arriba y abajo · barra de nivel 0–100 % |
| Botón (pin 2) | Dispara · luz ON/OFF en el panel |

El Arduino envía por USB una línea ~50 veces por segundo con el formato `boton,fader` (por ejemplo `1,768`).
La página la lee con la **Web Serial API** de Chrome/Edge, sin instalar nada.

### El juego
- Esquiva meteoritos (10 pts) y destruye naves enemigas (2 disparos, 50 pts).
- Cada 20 segundos subes de nivel y todo va más rápido.
- El panel derecho muestra en tiempo real el estado del botón, el nivel del fader y un gráfico de la señal.

## Conexiones

| Componente | Pin del Arduino |
|---|---|
| Fader – extremo | 5V |
| Fader – cursor (pata del medio) | A0 |
| Fader – otro extremo | GND |
| Botón – COM | GND |
| Botón – NO | Pin 2 (`INPUT_PULLUP`, sin resistencia) |

Todas las conexiones están soldadas en una **placa perforada que funciona como shield**: se monta y desmonta sobre el Arduino sin desoldar nada.

![Diagrama esquemático](imagenes/esquematico.png)

## Archivos

```
controlador/controlador.ino   código del Arduino
dashboard.html                página del juego y panel
imagenes/                     fotos del proceso y diagrama
```

## Cómo usarlo

1. Abrir `controlador/controlador.ino` en el Arduino IDE y subirlo al Arduino Uno.
2. Abrir `dashboard.html` en **Chrome o Edge** (o el link de GitHub Pages).
3. Apretar **"Conectar controlador"** y elegir el puerto del Arduino.
4. Apretar el botón físico para empezar a jugar.

> Sin Arduino también se puede probar: mouse o flechas ↑ ↓ para mover y barra espaciadora para disparar.

## Proceso de fabricación

_(Agrega aquí tus fotos: piezas, soldadura del shield, armado interno y caja terminada)_

![Piezas](imagenes/piezas.jpg)
![Soldadura del shield](imagenes/soldadura.jpg)
![Armado interno](imagenes/interior.jpg)
![Controlador terminado](imagenes/final.jpg)
