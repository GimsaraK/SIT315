const int motionSensor1Pin = 3;
const int ledPin = 13;
const int moistureSensorPin = 2;
const int motionSensor2Pin = 8;

int ledState = 0;
volatile int motionSensor1State = 0;
volatile int moistureSensorState = 0;
volatile int motionSensor2State = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(motionSensor1Pin, INPUT);
  pinMode(moistureSensorPin, INPUT);
  pinMode(motionSensor2Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), moistureSensorPin_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), motionSensor1Pin_ISR, CHANGE);
  
  PCICR |= 0b00000001; // turn on port b
  PCMSK0 |= 0b00000001; // pin PB0, PCINT0, physical pin 14
  
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // we want to turn the led to blink every 2 seconds = 0.5 Hz
  // 0.5Hz = (16000000/((31249+1)*1024))
  
  //Set timer compare
  OCR1A = 31249;
  
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  
  // CTC
  TCCR1B |= (1 << WGM12);
  
  interrupts();
}

void loop()
{
  
}

void motionSensor1Pin_ISR()
{
  motionSensor1State = digitalRead(motionSensor1Pin);
  ledState = motionSensor1State;
  digitalWrite(ledPin, ledState);
  
  // Printing the status
  if (motionSensor1State == HIGH)
  {
  	Serial.print("Motion Detected on sensor 1");
    Serial.print("\nLED On\n");
  } 
  else
  {
    Serial.print("No Motion Detected on sensor 1");
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

ISR(PCINT0_vect)
{
  // Interrupt for Port B
  motionSensor2State = digitalRead(motionSensor2Pin);
  ledState = motionSensor2State;
  digitalWrite(ledPin, ledState);
  
  // Printing the status
  if (motionSensor2State == HIGH)
  {
  	Serial.print("Motion Detected on sensor 2");
    Serial.print("\nLED On\n");
  } 
  else
  {
    Serial.print("No Motion Detected on sensor 2");
    Serial.print("\nLED Off\n");
  }
}

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}