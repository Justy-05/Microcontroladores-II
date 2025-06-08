#include <DHT.h>

// Definiciones de pines
#define DHTPIN 2
#define DHTTYPE DHT22

#define TRIG_PIN 3
#define ECHO_PIN 4

#define SONIDO_PIN A0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Leer temperatura y humedad
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  // Leer distancia del sensor ultrasónico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracion = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracion * 0.0343 / 2;

  // Leer sonido
  int sonido = analogRead(SONIDO_PIN);

  // Verificar si hay errores de lectura
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error leyendo DHT22");
    return;
  }

  // Enviar datos por Serial (formato compatible con interfaz)
  Serial.print("T:");
  Serial.print(temperatura, 1);
  Serial.print(" H:");
  Serial.print(humedad, 1);
  Serial.print(" D:");
  Serial.print(distancia, 1);
  Serial.print(" S:");
  Serial.println(sonido, 1);

  delay(1000);
}
