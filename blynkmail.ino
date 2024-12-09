// Define pins for Sensor 1
const int TRIG_PIN_1 = 2;
const int ECHO_PIN_1 = 3;

// Define pins for Sensor 2
const int TRIG_PIN_2 = 4;
const int ECHO_PIN_2 = 5;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pins for Sensor 1 as input/output
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);

  // Set pins for Sensor 2 as input/output
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
}

void loop() {
  // Get distance from Sensor 1
  float distance1 = getDistance(TRIG_PIN_1, ECHO_PIN_1);
  // Get distance from Sensor 2
  float distance2 = getDistance(TRIG_PIN_2, ECHO_PIN_2);

  // Print distances to Serial Monitor
  Serial.print("Distance from Sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Distance from Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Wait before next reading
  delay(1000);
}

// Function to measure distance using ultrasonic sensor
float getDistance(int trigPin, int echoPin) {
  // Clear the TRIG_PIN
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse to TRIG_PIN
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the ECHO_PIN pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distance = (duration * 0.034) / 2;

  return distance;
}
