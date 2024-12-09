#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME " "
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi and Blynk configuration
char ssid[] = "";           // Replace with your Wi-Fi SSID
char pass[] = "";       // Replace with your Wi-Fi password
char auth[] = ;     // Replace with your Blynk Auth Token

// Ultrasonic Sensor pins
#define TRIG_PIN D1
#define ECHO_PIN D2


// Bin dimensions
const int binHeight = 30; // Bin height in cm (adjust based on actual bin height)

// Function to notify when the bin is full
void notifyWhenFull(int percentageFull) {
  if (percentageFull >= 85) { 
    Serial.println("Garbage bin is full!");
    // Trigger a Blynk event notification when the bin is full
    Blynk.logEvent("blynk_smart_bin", "Garbage bin is full!");
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(19200);
  
  // Set up Blynk
  Blynk.begin(auth, ssid, pass);

  // Configure ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  Blynk.run(); // Run Blynk

  // Measure distance and calculate fullness percentage
  int distance = measureDistance();
  int percentageFull = calculatePercentageFull(distance);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Fullness: ");
  Serial.print(percentageFull);
  Serial.println("%");

  // Send distance and fullness percentage to Blynk virtual pins
  Blynk.virtualWrite(V0, distance);         // Send distance to V0
  Blynk.virtualWrite(V1, percentageFull);   // Send fullness percentage to V1

  // Check if bin is full and send notification
  notifyWhenFull(percentageFull);

  delay(1000); // Update every minute
}

// Function to measure distance using ultrasonic sensor
int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2; // Convert time to distance in cm
  return distance;
}

// Function to calculate fullness percentage
int calculatePercentageFull(int distance) {
  int percentageFull = map(distance, binHeight, 0, 0, 100);  // Map distance to 0-100%
  percentageFull = constrain(percentageFull, 0, 100);         // Limit to 0-100%
  return percentageFull;
}
