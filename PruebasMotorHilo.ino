#define PIN_RELES_ALIMENTACION 2
#define PIN_RELE_MOTOR_A 3
#define PIN_DIR_A 9
#define PIN_STEP_A 5
#define PIN_ALIM_SWITCH_A 6
#define PIN_READ_SWITCH_A 7
int direcion_A;

// FUNCIONES



void setup() {
  Serial.begin(9600);
  pinMode(PIN_RELES_ALIMENTACION, OUTPUT);
  pinMode(PIN_RELE_MOTOR_A, OUTPUT);
  pinMode(PIN_ALIM_SWITCH_A, OUTPUT);
  pinMode(PIN_DIR_A, OUTPUT);
  digitalWrite(PIN_RELES_ALIMENTACION, HIGH); // Encendemos motor A
  digitalWrite(PIN_ALIM_SWITCH_A, HIGH); // Alimentamos el switch A
  // NOTA: Los relevadores de los motores se encienden en bajo
  analogWrite(PIN_RELE_MOTOR_A, 0); // Iniciamos con motor encendido
  // INICALIZAMOS POSICIÓN HASTA PEGAR CON EL SWITCH
  while !digitalRead(PIN_READ_SWITCH_A) {
    direccion_A = 
    delay(10);
  }
}

void loop() {
  // DIR en alto gira a la derecha, sube la pieza central
  // DIR en bajo gira a la izquierda, baja la pieza central
  analogWrite(PIN_DIR_A, 0);
  for (int i = 0; i < 200; i++) {
    analogWrite(PIN_STEP_A, 255);
    delay(2); //
    analogWrite(PIN_STEP_A, 0);
    delay(10);
  }
  delay(1000);

}
