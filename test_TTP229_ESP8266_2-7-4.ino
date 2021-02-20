/*
  Created by SENSORVN.COM, February 19, 2021.
  Wiring
  VCC -> 3.3V
  GND -> GND
  SCL -> GPIO3
  SDO -> GPIO4
*/
const int SDO = 4; //SDO
const int SCL_ = 3;//SCL
const int LED = 14;//LED
byte data_ = 0;
byte data = 0;
void ICACHE_RAM_ATTR handleInterrupt();

/* Function */
void work()
{
  for(byte i=1;i<17;i++)
  { 
    data_ = i;
    attachInterrupt(digitalPinToInterrupt(SDO), handleInterrupt, FALLING);
    digitalWrite(SCL_,LOW);
    delay(1);
    digitalWrite(SCL_,HIGH);
    delay(1);
  }
  delay(2);
  detachInterrupt(digitalPinToInterrupt(SDO));
  delay(1000);
}

/* Arduino Function */
void setup() 
{ 
  Serial.begin(115200);
  pinMode(LED,OUTPUT); 
  pinMode(SCL_,OUTPUT); 
  pinMode(SDO, INPUT); 
  Serial.println("Calibrating Sensor .................. ");
  delay(5000);//calibration
  digitalWrite(LED,HIGH);
  Serial.print("Done");
} 

void loop() 
{ 
  work();
} 

void ICACHE_RAM_ATTR handleInterrupt() 
{ 
  data = data_;
  Serial.println(data); 
}
