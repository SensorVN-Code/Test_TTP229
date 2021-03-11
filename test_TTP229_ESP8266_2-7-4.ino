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
volatile int flag = 0;
volatile int flag2 = 0;
byte data_ = 0;
byte data = 0;
void ICACHE_RAM_ATTR handleInterrupt();

/* Function */
void delaySensor()
{
  for(int i=0;i<50;i++)
  {
    if(!digitalRead(SDO))
    {
      if(flag2 == 0)
      {
        data = data_;
        flag2 ++;
      }
      if(flag2 == 1)
      {
        Serial.println(data);
        flag2 ++;
      }
    }
  }
}
void work()
{
  for(int i = 1;i<17;i++)
  {
    data_ = i;
    digitalWrite(SCL_,LOW);
    delaySensor();
    digitalWrite(SCL_,HIGH);
    delaySensor();
  }
  flag2 = 0;
  flag = 0;
  delay(300);
  attachInterrupt(digitalPinToInterrupt(SDO), handleInterrupt, FALLING);
}

/* Arduino Function */
void setup() 
{ 
  Serial.begin(115200);
  pinMode(LED,OUTPUT); 
  pinMode(SCL_,OUTPUT); 
  pinMode(SDO, INPUT);
  digitalWrite(SCL_,HIGH); 
  Serial.println("Calibrating Sensor .................. ");
  delay(4000);//calibration
  attachInterrupt(digitalPinToInterrupt(SDO), handleInterrupt, FALLING);  
  digitalWrite(LED,HIGH);
  Serial.print("Done");
} 

void loop() 
{ 
  if(flag == 1)
  {
    work();
  }
} 

void ICACHE_RAM_ATTR handleInterrupt() 
{ 
  flag = 1;
  detachInterrupt(digitalPinToInterrupt(SDO));
}
