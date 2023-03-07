#define PIN_A4988_VCC 4
#define PIN_RELES_ALIMENTACION 2
#define PIN_RELE_MOTOR_A 3
#define PIN_DIR_A 9
#define PIN_STEP_A 5
#define PIN_ALIM_SWITCH_A 6
#define PIN_READ_SWITCH_A 7
#define ARRIBA 255
#define ABAJO 0
#define ESPERA_GEN 1000000
#define ESPERA_PULSO 9000

int direcion_A;

// FUNCIONES
void paso_motor_A(int retraso) {
  analogWrite(PIN_STEP_A, 255);
  delayMicroseconds(ESPERA_PULSO); //
  analogWrite(PIN_STEP_A, 0);
  delayMicroseconds(retraso);
}


void setup() {
  Serial.begin(9600);
  pinMode(PIN_RELES_ALIMENTACION, OUTPUT);
  pinMode(PIN_RELE_MOTOR_A, OUTPUT);
  pinMode(PIN_ALIM_SWITCH_A, OUTPUT);
  pinMode(PIN_DIR_A, OUTPUT);
  pinMode(PIN_A4988_VCC, OUTPUT);
  digitalWrite(PIN_RELES_ALIMENTACION, HIGH); // Encendemos motor A
  digitalWrite(PIN_ALIM_SWITCH_A, HIGH); // Alimentamos el switch A
  digitalWrite(PIN_A4988_VCC, HIGH); // Alimentamos el módulo A4988
  // NOTA: Los relevadores de los motores se encienden en bajo
  analogWrite(PIN_RELE_MOTOR_A, 0); // Iniciamos con motor encendido
  // INICALIZAMOS POSICIÓN HASTA PEGAR CON EL SWITCH
  while (!digitalRead(PIN_READ_SWITCH_A)) {
    analogWrite(PIN_DIR_A, ABAJO); // Nos movemos hasta llegar al switch de final de carrera
    paso_motor_A(10); // Tomamos 10 ms por paso
  }
}

void loop() {
  // 200 pasos equivalen a una vuelta del motor
  // Para dar 90 vueltas necesitamos 200 x 90 pasos
  // Es decir 18000 pasos
  analogWrite(PIN_DIR_A, ARRIBA); // Empezamos moviéndonos hacia arriba
  // aceleramos
  
  // Mantenemos velocidad
  for (int i = 0; i < 18000; i++) {
    paso_motor_A(ESPERA_GEN);
  }
  delay(10);

  
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
