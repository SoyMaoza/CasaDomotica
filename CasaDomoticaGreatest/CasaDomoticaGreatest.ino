//incluimos libreria para la pantalla LCD
#include <LiquidCrystal.h>
// Incluimos librería sensor de humedad y temperatura
#include <DHT.h>

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 39
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <Servo.h>

//LEDS
int ledGarage = 8;
int ledPasillo1 = 9;
int ledPasillo2 = 10;
int ledCuarto1 = 11;
int ledCuarto2 = 12;
int ledSala = 13;
int ledEntrada = 2;
//sensor ultrasonico
int echoPin = 26;
int trigPin = 27;

//PANTALLA LCD
int rs = 28;
int e = 29;
int d4 = 30;
int d5 = 31;
int d6 = 32;
int d7 = 33;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

//declaramos el dato necesario para el sensor ultrasonico
float velocidad = 0.0343;
long duracion, distancia;

//puertas y ventanas
Servo PVGarage;
Servo PVVentana;
Servo PVCuarto1;
Servo PVCuarto2;

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Comenzamos el sensor DHT11
  dht.begin();
  //creamos las medidas de la lcd
  lcd.begin(20, 4);


  pinMode(ledGarage, OUTPUT);
  pinMode(ledPasillo1, OUTPUT);
  pinMode(ledPasillo2, OUTPUT);
  pinMode(ledCuarto1, OUTPUT);
  pinMode(ledCuarto2, OUTPUT);
  pinMode(ledSala, OUTPUT);
  pinMode(ledEntrada, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  PVGarage.attach(22);
  PVVentana.attach(23);
  PVCuarto1.attach(24);
  PVCuarto2.attach(25);
}

void loop() {
  // put your main code here, to run repeatedly:
  //parte de la LCD, Sensor de Humedad, Sensor de Temperatura
  delay(3000);

  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahrenheit
  float f = dht.readTemperature(true);

  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  // Calcular el índice de calor en Fahrenheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  lcd.setCursor(4, 0);
  lcd.print("INDICADORES");
  lcd.setCursor(0, 1);
  lcd.print("Temperatura: ");
  lcd.print(t);
  lcd.print("*C");
  lcd.setCursor(0, 2);
  lcd.print("Humedad: ");
  lcd.print(h);
  lcd.print("%");


  //parte de la app para controlarla por bluetooth
  if (Serial.available() > 0) {
    char controlador = Serial.read();
    if (controlador == 'a') {
      digitalWrite(ledGarage, HIGH);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("ENCENDIENDO");
      lcd.setCursor(5, 2);
      lcd.print("LED GARAGE");
    }
    if (controlador == 'A') {
      digitalWrite(ledGarage, LOW);
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("APAGANDO");
      lcd.setCursor(5, 2);
      lcd.print("LED GARAGE");
    }
    if (controlador == 'b') {
      digitalWrite(ledPasillo1, HIGH);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("ENCENDIENDO");
      lcd.setCursor(4, 2);
      lcd.print("LED PASILLO1");
    }
    if (controlador == 'B') {
      digitalWrite(ledPasillo1, LOW);
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("APAGANDO");
      lcd.setCursor(3, 2);
      lcd.print("LED PASILLO1");
    }
    if (controlador == 'c') {
      digitalWrite(ledPasillo2, HIGH);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("ENCENDIENDO");
      lcd.setCursor(3, 2);
      lcd.print("LED PASILLO2");
    }
    if (controlador == 'C') {
      digitalWrite(ledPasillo2, LOW);
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("APAGANDO");
      lcd.setCursor(5, 2);
      lcd.print("LED PASILLO2");
    }
    if (controlador == 'd') {
      digitalWrite(ledCuarto1, HIGH);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("ENCENDIENDO");
      lcd.setCursor(4, 2);
      lcd.print("LED CUARTO1");
    }
    if (controlador == 'D') {
      digitalWrite(ledCuarto1, LOW);
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("APAGANDO");
      lcd.setCursor(5, 2);
      lcd.print("LED CUARTO1");
    }
    if (controlador == 'e') {
      digitalWrite(ledCuarto2, HIGH);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("ENCENDIENDO");
      lcd.setCursor(4, 2);
      lcd.print("LED CUARTO2");
    }
    if (controlador == 'E') {
      digitalWrite(ledCuarto2, LOW);
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("APAGANDO");
      lcd.setCursor(5, 2);
      lcd.print("LED CUARTO2");
    }
    if (controlador == 'f') {
      digitalWrite(ledSala, HIGH);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("ENCENDIENDO");
      lcd.setCursor(6, 2);
      lcd.print("LED SALA");
    }
    if (controlador == 'F') {
      digitalWrite(ledSala, LOW);
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("APAGANDO");
      lcd.setCursor(5, 2);
      lcd.print("LED SALA");
    }
    //Condicional para encender todos los LEDS
    if (controlador == 'g') {
      digitalWrite(ledGarage, HIGH);
      digitalWrite(ledPasillo1, HIGH);
      digitalWrite(ledPasillo2, HIGH);
      digitalWrite(ledCuarto1, HIGH);
      digitalWrite(ledCuarto2, HIGH);
      digitalWrite(ledSala, HIGH);
      digitalWrite(ledEntrada, HIGH);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("ENCENDIENDO");
      lcd.setCursor(8, 2);
      lcd.print("TODO");
    }
    //Condicional para apagar todos los LEDS
    if (controlador == 'G') {
      digitalWrite(ledGarage, LOW);
      digitalWrite(ledPasillo1, LOW);
      digitalWrite(ledPasillo2, LOW);
      digitalWrite(ledCuarto1, LOW);
      digitalWrite(ledCuarto2, LOW);
      digitalWrite(ledSala, LOW);
      digitalWrite(ledEntrada, LOW);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("APAGANDO");
      lcd.setCursor(8, 2);
      lcd.print("TODO");
    }
    //apartado de servomotores
    if (controlador == 'h') {
      for (int i = 0; i <= 120; i++) {
        PVGarage.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("ABRIENDO");
      lcd.setCursor(7, 2);
      lcd.print("GARAGE");
    }
    if (controlador == 'H') {
      for (int i = 120; i >= 0; i--) {
        PVGarage.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("CERRANDO");
      lcd.setCursor(7, 2);
      lcd.print("GARAGE");
    }
    if (controlador == 'i') {
      for (int i = 0; i <= 120; i++) {
        PVVentana.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("ABRIENDO");
      lcd.setCursor(6, 2);
      lcd.print("VENTANA");
    }
    if (controlador == 'I') {
      for (int i = 120; i >= 0; i--) {
        PVVentana.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("CERRANDO");
      lcd.setCursor(6, 2);
      lcd.print("VENTANA");
    }
    if (controlador == 'j') {
      for (int i = 0; i <= 180; i++) {
        PVCuarto1.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("ABRIENDO");
      lcd.setCursor(6, 2);
      lcd.print("CUARTO1");
    }
    if (controlador == 'J') {
      for (int i = 180; i >= 0; i--) {
        PVCuarto2.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("CERRANDO");
      lcd.setCursor(6, 2);
      lcd.print("CUARTO2");
    }
    if (controlador == 'k') {
      for (int i = 0; i <= 180; i++) {
        PVCuarto1.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("ABRIENDO");
      lcd.setCursor(6, 2);
      lcd.print("CUARTO2");
    }
    if (controlador == 'K') {
      for (int i = 180; i >= 0; i--) {
        PVCuarto1.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("CERRANDO");
      lcd.setCursor(6, 2);
      lcd.print("CUARTO2");
    }
    //Condicional para abrir todas las Puertas Y Ventanas
    if (controlador == 'l') {
      for (int i = 0; i <= 179; i++) {
        PVGarage.write(i);
        PVVentana.write(i);
        PVCuarto1.write(i);
        PVCuarto2.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("ABRIENDO");
      lcd.setCursor(8, 2);
      lcd.print("TODO");
  }
  //Condicional para cerrar todas las Puertas Y Ventanas
    if (controlador == 'L') {
      for (int i = 180; i >= 0; i--) {
        PVGarage.write(i);
        PVVentana.write(i);
        PVCuarto1.write(i);
        PVCuarto2.write(i);
        delay(15);
      }
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("CERRANDO");
      lcd.setCursor(8, 2);
      lcd.print("TODO");
  }
  //Escribi el encendido y el apagado del led de la entrada porque se me habia olvidado
 if(controlador == 'm'){
  digitalWrite(ledEntrada, HIGH);
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print("ENCENDIENDO");
      lcd.setCursor(4, 2);
      lcd.print("LED ENTRADA");
    }
    if(controlador == 'M'){
  digitalWrite(ledEntrada, LOW);
      lcd.clear();
      lcd.setCursor(6, 1);
      lcd.print("APAGANDO");
      lcd.setCursor(4, 2);
      lcd.print("LED ENTRADA");
    }
    Serial.println(controlador);
 }
}