#define PIN_RELE_MOTOR_A 13
#define PIN_DIR_A 3
#define PIN_STEP_A 11
#define PIN_ALIM_SWITCH_A 10
#define PIN_READ_SWITCH_A 9
#define ARRIBA 255
#define ABAJO 0
unsigned long ESPERA_GEN = 4000000;
unsigned long ESPERA_PULSO = 4000000;
unsigned long PULSO_CALIBRACION = 9000000;

int direcion_A;

// FUNCIONES
void paso_motor_A(unsigned long retraso) {
  digitalWrite(PIN_STEP_A, HIGH);
  delayMicroseconds(ESPERA_PULSO); //
  digitalWrite(PIN_STEP_A, LOW);
  delayMicroseconds(retraso);
}


void setup() {
  Serial.begin(9600);
  pinMode(PIN_RELE_MOTOR_A, OUTPUT);
  pinMode(PIN_ALIM_SWITCH_A, OUTPUT);
  //pinMode(PIN_DIR_A, OUTPUT);
  pinMode(PIN_STEP_A, OUTPUT);
  pinMode(PIN_READ_SWITCH_A, INPUT);
  digitalWrite(PIN_ALIM_SWITCH_A, HIGH); // Alimentamos el switch A
  // NOTA: Los relevadores de los motores se encienden en bajo
  digitalWrite(PIN_RELE_MOTOR_A, LOW); // Iniciamos con motor encendido
  // INICALIZAMOS POSICIÓN HASTA PEGAR CON EL SWITCH
  // digitalWrite(PIN_DIR_A, LOW); // Nos movemos hasta llegar al switch de final de carrera
  analogWrite(PIN_DIR_A, ABAJO); // Nos movemos hasta llegar al switch de final de carrera
  while (!digitalRead(PIN_READ_SWITCH_A)) {
    paso_motor_A(PULSO_CALIBRACION); // Tomamos 10 ms por paso
  }
}

void loop() {
  // 200 pasos equivalen a una vuelta del motor
  // Para dar 90 vueltas necesitamos 200 x 90 pasos
  // Es decir 18000 pasos
  //digitalWrite(PIN_DIR_A, HIGH); // Empezamos moviéndonos hacia arriba
  analogWrite(PIN_DIR_A, ARRIBA); // Empezamos moviéndonos hacia arriba
  // aceleramos
  
  // Mantenemos velocidad
  for (int i = 0; i < 18000; i++) {
    paso_motor_A(ESPERA_GEN);
  }
  delay(10);

  
  //digitalWrite(PIN_DIR_A, LOW); // Ahora nos movemos hacia abajo
  analogWrite(PIN_DIR_A, ABAJO); // Ahora nos movemos hacia abajo
  // aceleramos
  // mantenemos la velocidad
  for (int i = 0; i < 18000; i++) {
    // Por seguridad, en cada paso revisamos si no chocamos con el switch
    if (digitalRead(PIN_READ_SWITCH_A)){
        break; // Si chocamos con el switch nos cambiamos a dar 90 vueltas hacia arriba
      }
    paso_motor_A(ESPERA_GEN);
  }
  delay(10);

}
