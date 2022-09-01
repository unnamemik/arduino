#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12); // RX, TX, connect across

  char mas;
  String str;
  int pwm_value=10;
  char end_of_command = '\r';

void setup(){
  Serial.begin(9600);
  while (!Serial) {;}
  mySerial.begin(9600);  
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT); //PWM
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT); //PWM
  pinMode (10, OUTPUT);
  digitalWrite (10, LOW);
}

void loop(){
      serialEvent();
      pwm();
      if (str=="Forward") {forward();}
      else if (str=="Back") {back();}
      else if (str=="Left") {left();}
      else if (str=="Right") {right();}
      else if (str=="Lighton") {light_on();}
      else if (str=="Lightoff") {light_off();}
      else if (str=="Hornon") {horn_on();}
      else if (str=="Hornoff") {horn_off();}      
      else if (str=="Rst"){rst();}
      
    str="";
    replica();
}                   

void serialEvent (){
    while (mySerial.available()){
    mas = (mySerial.read());
    str += mas;
    delay(1);}
    if (str!="") {Serial.println (str);}
}

void pwm(){
  if (str.substring(0,3)=="PWM"){
  String val=str.substring(str.length()-3);
  pwm_value = val.toInt();}
  
    //while (!mySerial.available()){    
    //Serial.println (pwm_value);
    //analogWrite (10, pwm_value);} 
}

void replica (){
    if (Serial.available())
    mySerial.write(Serial.read());    
}

void forward(){//Serial.println ("Forward replica");
    //while (!mySerial.available()){
   digitalWrite (2, LOW); 
   digitalWrite (3, HIGH);//}

}

void back(){//Serial.println ("Back replica");
   // while (!mySerial.available()){
   digitalWrite (2, HIGH); 
   digitalWrite (3, LOW);//}
}

void left(){//Serial.println ("Left replica");
    while (!mySerial.available()){
   digitalWrite (4, LOW); 
   digitalWrite (5, HIGH); }
}

void right(){//Serial.println ("Right replica");
    while (!mySerial.available()){
   digitalWrite (4, HIGH); 
   digitalWrite (5, LOW);}
}

void light_on(){
  while (!mySerial.available()){
   analogWrite (10, pwm_value);}  
}

void light_off(){
  while (!mySerial.available()){
  digitalWrite(10, LOW);}
}

void horn_on(){
  while (!mySerial.available()){
  digitalWrite(10, HIGH); delay (50);
  digitalWrite(10, LOW); delay (50); } 
}

void horn_off(){
  while (!mySerial.available()){
  digitalWrite(10, LOW);}
}

void rst(){
  while (!mySerial.available()){
  digitalWrite(10, LOW);}
   digitalWrite (2, LOW); 
   digitalWrite (3, LOW);
   digitalWrite (4, LOW); 
   digitalWrite (5, LOW);
}
