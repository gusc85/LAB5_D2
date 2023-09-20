// -------------------------------
// DATOS Y ENCABEZADO
// -------------------------------
    
// Archivo:                 LAB5_D2
// Dispositivo:             TIVA-C
// Autor:                   GUSTABO CoRDOVA 
// Programa:                LAB5_D2
// Creado:                  19/09, 2023 
// Ultima modificaci?n:     19/09, 2023

const int buttonPin1 = PUSH2;     // the number of the pushbutton pin
const int buttonPin = PUSH1;      // the number of the pushbutton pin
const int buttonPin2 = 19;        // El número del pin del botón
const int ledPin =  GREEN_LED;    // the number of the LED pin
const int ledPin2 =  BLUE_LED;    // the number of the LED pin
const int ledPin3 =  RED_LED;     // the number of the LED pin
const int ganaP1 = 18;
const int ganaP2 = 15;
const int J1[8] = {2, 3, 4, 5, 6, 7, 8, 9};             // Leds del jugador 1
const int J2[8] = {23, 24, 25, 26, 27, 28, PA_3, 30};   // Leds del jugador 2

// variables will change:
int buttonState = 0;        
int buttonP1 = 0;
int buttonP2 = 0;

int bandera =0;
int Cont = 0;
int Cont2 = 0;

void setup() {
  // Inicializando las entradas y salidas
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ganaP1, OUTPUT);
  pinMode(ganaP2, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  Serial.begin(9600);  // Iniciar la comunicación serial para depuración     
 
  for (int i = 0; i < 8; i++)       // Declarar cada pin que esta en J1 y J2 como salida usando un ciclo for
  {
    pinMode(J1[i],OUTPUT);
    digitalWrite(J1[i],LOW);
    pinMode(J2[i],OUTPUT);
    digitalWrite(J2[i],LOW);
    
  }
}

void loop() {
  // Leer el estado de los botones
  //buttonState = digitalRead(buttonPin2);
  buttonP1 = digitalRead(buttonPin);
  buttonP2 = digitalRead(buttonPin1);

  // Comprobar si se presionó el botón buttonPin
  if (buttonP1 == LOW && bandera == 0) {
    // Apagar todas las leds de los contadores
    for (int i = 0; i < 8; i++) {
      digitalWrite(J1[i], LOW);
      digitalWrite(J2[i], LOW);
    }
    
    // Establecer todos los contadores en cero en caso que no se reinicien 
    Cont = 0;
    Cont2 = 0;
    // Apagar las leds de los jugadores que ganaron
    digitalWrite(ganaP1, LOW);
    digitalWrite(ganaP2, LOW);
    // Secuencia de encendido y apagado de LEDs
    digitalWrite(ledPin, LOW);    // Led verde
    digitalWrite(ledPin3, HIGH);  // Led roja
    digitalWrite(ledPin2, LOW);   // Led azul
    delay(500);
    digitalWrite(ledPin3, HIGH);  // Led verde
    digitalWrite(ledPin, HIGH);   // Led roja
    digitalWrite(ledPin2, LOW);   // Led azul
    delay(500);
    digitalWrite(ledPin2, LOW);   // Led azul
    digitalWrite(ledPin3, LOW);   // Led roja
    digitalWrite(ledPin, HIGH);   // Led verde
    delay(500);

    // Establecer bandera en 1:
    bandera = 1;
  }

//----------------------- JUGADOR 1 --------------------------------//
  if (bandera == 1 && buttonP1 == LOW) {
  // Apagar todos los pines en J1
  for (int i = 0; i < 8; i++) {
    digitalWrite(J2[i], LOW);
  }
  
  // Incrementar el contador y asegurarse de que no sea mayor que el número máximo de pines
  Cont+=1;
  if (Cont > 8) {
    Cont = 0;
    digitalWrite(ganaP1, HIGH);
  }
  
  // Encender el siguiente pin en J1
  digitalWrite(J2[Cont-1], HIGH);
  // Esperar un tiempo para evitar múltiples detecciones del botón
  delay(500);
}
//----------------------- JUGADOR 2 --------------------------------//
if (bandera == 1 && buttonP2 == LOW) {  // Jugador 2
  // Apagar todos los pines en J1
  for (int i = 0; i < 8; i++) {
    digitalWrite(J1[i], LOW);
  }
  
  // Incrementar el contador y asegurarse de que no sea mayor que el número máximo de pines
  Cont2+=1;
  if (Cont2 > 8) {
    Cont2 = 0;
    digitalWrite(ganaP2, HIGH);
  }
  
  // Encender el siguiente pin en J1
  digitalWrite(J1[Cont2-1], HIGH);
  // Esperar un tiempo para evitar múltiples detecciones del botón
  delay(500);
}
//------------------------------ REINICIO DEL JUEGO --------------------------------//  
  // Restablecer bandera a 0 y declara J1 como ganador
  if (buttonP2 == LOW && buttonP1 == LOW) {
    bandera = 0;
    
   //  Apagar todos los pines en PORTB
    for (int i = 0; i < 8; i++) {
      digitalWrite(J1[i], LOW);
      digitalWrite(J2[i], LOW);
    }
  }
 /*
  if (Cont2 == 0 && buttonP2 == LOW) {
    bandera = 0;
    
   //  Apagar todos los pines en PORTB
    for (int i = 0; i < 8; i++) {
      digitalWrite(J2[i], LOW);
    }
  }
  */
}
