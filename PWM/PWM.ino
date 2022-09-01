// PWM 11.09.2021
// 100 33150 256000

volatile float PWM=0;
float pwr=0.4; //power (40% optimal for relief print)

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);    // step A
  pinMode(3, INPUT);    // step Z
  pinMode(4, INPUT);    // dir A
  pinMode(5, OUTPUT);   // PWM
  pinMode(6, INPUT);    // dir Z
         attachInterrupt (0, pinOutA, CHANGE); //A down
         attachInterrupt (1, pinOutZ, CHANGE); //Z up
}

void loop() {
     if (PWM>0) {PWM=0;} else if (PWM<-255) {PWM=-255;}    
         
   //  if (PWM>(-155)) {pwr=0;} else {pwr=0.4;}
       
       Serial.println (-PWM);
       analogWrite (5, (-PWM*pwr));
}
       
void pinOutA (){if (digitalRead (4)==LOW) {--PWM;}}

void pinOutZ (){if (digitalRead (6)==HIGH) {PWM++;}}
