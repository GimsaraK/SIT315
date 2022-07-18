
int motionSensor = 13;
int led = 8;

void setup()
{
  Serial.begin(9600);
  pinMode(motionSensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  if (digitalRead(motionSensor) == HIGH) {
    digitalWrite(led, HIGH);
    Serial.print("Motion Detected");
    Serial.print("\nLED On\n");
  } else {
    digitalWrite(led, LOW);
    Serial.print("No Motion Detected");
    Serial.print("\nLED Off\n");
  }
  delay(5000);
}
