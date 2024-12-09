#define BLYNK_TEMPLATE_ID "give your blynk template id"
#define BLYNK_TEMPLATE_NAME "give the template name"
#define BLYNK_AUTH_TOKEN "give the auth token"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "";
char pass[] = "";

// Sensor pins
#define TRIG_PIN_1 D1
#define ECHO_PIN_1 D2
#define TRIG_PIN_2 D3
#define ECHO_PIN_2 D4

// Maximum measurable distance for percentage calculation (adjust as needed)
#define MAX_DISTANCE 100.0 // in cm

void setup() {
  // Blynk setup
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Sensor setup
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);

  Serial.begin(115200);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  if (duration == 0) {
    Serial.println("No echo received!");
    return MAX_DISTANCE; // Return max distance if no echo is received
  }
  float distance = duration * 0.034 / 2; // Convert time to distance
  return distance;
}

float calculatePercentage(float distance, float maxDistance) {
  if (distance > maxDistance) distance = maxDistance;
  if (distance < 0) distance = 0; // Handle negative values (just in case)
  return ((maxDistance - distance) / maxDistance) * 100.0; // Inverse percentage
}

void loop() {
  Blynk.run();

  // Measure distances
  float distance = getDistance(TRIG_PIN_1, ECHO_PIN_1);  // Sensor 1
  delay(50); // Short delay to prevent interference
  float distance1 = getDistance(TRIG_PIN_2, ECHO_PIN_2); // Sensor 2

  // Calculate percentages
  float percentage = calculatePercentage(distance, MAX_DISTANCE);   // For Sensor 1
  float percentage1 = calculatePercentage(distance1, MAX_DISTANCE); // For Sensor 2

  // Send distances and percentages to Blynk app
  Blynk.virtualWrite(V0, distance);      // Distance for Sensor 1
  Blynk.virtualWrite(V1, percentage);    // Percentage for Sensor 1
  Blynk.virtualWrite(V2, distance1);     // Distance for Sensor 2
  Blynk.virtualWrite(V3, percentage1);   // Percentage for Sensor 2

  // Debug output
  Serial.print("Sensor 1: ");
  Serial.print(distance);
  Serial.print(" cm (");
  Serial.print(percentage);
  Serial.print("%), Sensor 2: ");
  Serial.print(distance1);
  Serial.print(" cm (");
  Serial.print(percentage1);
  Serial.println("%)");

  delay(500); // Adjust delay as needed
}
