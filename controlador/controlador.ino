// =============================================================
//  CONTROLADOR FÍSICO - Entrega 1  (juego "Misión Meteorito")
//  Envía al computador:  boton,fader   por ejemplo:  1,768
//
//  CONEXIONES:
//    Fader  EXTREMO  -> 5V
//    Fader  CURSOR   -> A0
//    Fader  patita 5 -> GND
//    Botón  COM (patita doblada) -> GND
//    Botón  patita recta         -> pin 2
// =============================================================

const int PIN_BOTON = 2;
const int PIN_FADER = A0;

// Si en el juego el botón aparece "apretado" sin apretarlo,
// cambia false por true (o cambia el cable a la otra patita recta).
const bool BOTON_INVERTIDO = false;

int estadoBoton = 0;
int lecturaAnterior = 0;
unsigned long tiempoCambio = 0;

void setup() {
  Serial.begin(115200);               // tiene que ser igual que en la página
  pinMode(PIN_BOTON, INPUT_PULLUP);   // no necesita resistencia
}

void loop() {
  // ---- Botón (con antirrebote para evitar falsos clics) ----
  int lectura = (digitalRead(PIN_BOTON) == LOW) ? 1 : 0;   // apretado = 1
  if (BOTON_INVERTIDO) lectura = 1 - lectura;

  if (lectura != lecturaAnterior) {
    tiempoCambio = millis();
    lecturaAnterior = lectura;
  }
  if (millis() - tiempoCambio > 15) {
    estadoBoton = lectura;
  }

  // ---- Fader (promedio de 8 lecturas para quitar el ruido) ----
  long suma = 0;
  for (int i = 0; i < 8; i++) suma += analogRead(PIN_FADER);
  int fader = suma / 8;

  // ---- Enviar al computador ----
  Serial.print(estadoBoton);
  Serial.print(',');
  Serial.println(fader);

  delay(20);   // unas 50 veces por segundo
}
