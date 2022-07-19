const int sensorPin = 2;
const int ledPin = 13;

volatile int sensorState = 0;
volatile int ledState = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), pin_ISR, CHANGE);
}

void loop()
{
  
}

void pin_ISR()
{
  sensorState = digitalRead(sensorPin);
  ledState = sensorState;
  digitalWrite(ledPin, ledState);
  
  // Printing the status
  if (sensorState == HIGH)
  {
  	Serial.print("Motion Detected");
    Serial.print("\nLED On\n");
  } 
  else
  {
    Serial.print("No Motion Detected");
    Serial.print("\nLED Off\n");
  }
}
