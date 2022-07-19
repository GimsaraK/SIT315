const int motionSensorPin = 3;
const int ledPin = 13;
const int moistureSensorPin = 2;

volatile int motionSensorState = 0;
volatile int ledState = 0;
volatile int moistureSensorState = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(motionSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(moistureSensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), moistureSensorPin_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), motionSensorPin_ISR, CHANGE);
}

void loop()
{
  
}

void motionSensorPin_ISR()
{
  motionSensorState = digitalRead(motionSensorPin);
  ledState = motionSensorState;
  digitalWrite(ledPin, ledState);
  
  // Printing the status
  if (motionSensorState == HIGH)
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

void moistureSensorPin_ISR()
{
  moistureSensorState = digitalRead(moistureSensorPin);
  ledState = moistureSensorState;
  digitalWrite(ledPin, ledState);
  
  // Printing the status
  if (moistureSensorState == HIGH)
  {
  	Serial.print("Soil Moisture is High");
    Serial.print("\nLED On\n");
  } 
  else
  {
    Serial.print("Soil Moisture is Low");
    Serial.print("\nLED Off\n");
  }
}