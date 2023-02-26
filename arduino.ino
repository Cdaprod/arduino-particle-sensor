// Boilerplate, starting point

int sensorPin = A0; // analog input pin for the sensor
int sensorValue = 0; // variable to store the sensor value

void setup() {
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  sensorValue = analogRead(sensorPin); // read the sensor value
  Serial.println(sensorValue); // print the sensor value to the serial monitor
  delay(1000); // wait for a second before taking the next reading
}
