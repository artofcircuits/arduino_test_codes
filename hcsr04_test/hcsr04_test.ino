/*--------------------------------------------------------------------
  Arduino test code for HC-SR04 and JSN-SR04T ultrasonid distance sensor
  module

  -- Sensor Pinouts
  Sensor		Arduino
  VCC       5V
  Trig      12
  Echo      13
  GND       GND
  
  -- Status LEDS
  LED RED    11		(Anode to pin 11, Cathode through 560 ohm resistor to GND)
  LED GREEN  10		(Anode to pin 10, Cathode through 560 ohm resistor to GND)  
  
  Art of Circuits is Pakistan’s popular online store that sells electronics 
  components, boards and tools to make your electronics projects possible. 
  Art of Circuits is located in Islamabad, and sells products across all 
  cities of Pakistan.

  Contact Info:
  Email: support@artofcircuits.com
  Web:  http://artofcircuits.com

  -------------------------------------------------------------------------*/

#define trigPin 13
#define echoPin 12
#define ledRedPin 11
#define ledGreenPin 10

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 4) {  // comparison for led ON/OFF
    digitalWrite(ledRedPin,HIGH); // when Red LED turns ON, Green LED turns off
  digitalWrite(ledGreenPin,LOW);
}
  else {
    digitalWrite(ledRedPin,LOW);
    digitalWrite(ledGreenPin,HIGH);
  }
  if (distance >= 400 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
