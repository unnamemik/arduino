/* Ginger v5.0 30.05.2021  */

void(* reset) (void) = 0;

const int whitePin = 5; //Белый
const int blackPin = 6; //Черный
const int yellowPin = 7; //Желтый
const int redPin = 8; //Красный
const int greenPin = 9; //Зеленый
const int bluePin = 10; //Синий

String color, timer;
char sign;
int passFlag=0, passFlag1=0, duration=1 ;

int durat=100;

void setup() {
  Serial.begin(9600);
  pinMode(whitePin, OUTPUT);
  pinMode(blackPin, OUTPUT);  
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);  
  pinMode(bluePin, OUTPUT);
  portReset();
  
  Serial.println("***************************************************");
  Serial.println("***********************Hello!**********************");
  Serial.println("                  Device cleaner                   ");
  Serial.println("Please, input channel color (ex W, S, Y, R, G or B)");
  Serial.println("***************************************************");
  Serial.println();  
}


void loop() {
        if (color =="\0") {
      get_color ();}
      
        if (color!="\0"&&duration==1) {
      while (passFlag==0) {Serial.println("Enter cleaning time, in second (min 2, max 120)"); passFlag++;}  
      get_durat ();}     
      
        if (color!="\0"&&duration!=1) {
      while (passFlag1==0) {colorSwitch (); passFlag1++;}}      
          
}

/////////////////////////////////COLOR INPUT//////////////////////////////
void get_color (){
   clr (); 
   if (Serial.available() > 0){
   color = Serial.readString();
   delay (5);
   Serial.print("Selected channel: ");
   Serial.println(color);
   Serial.println();
   sign = color.charAt (0);
   }
}

void get_durat () {
   clr (); 
   if (Serial.available() > 0){
   timer = Serial.readString();
   delay (5);
   duration=timer.toInt();
   Serial.print("Selected duration: ");
   Serial.print(duration);
   Serial.println(" second");
   if (duration<1||duration>120) {Serial.print("Invalid value!"); delay(500); exit();}

   Serial.println();
   Serial.println("***************************************************");
   Serial.println("Cleaning...");
   Serial.println("***************************************************");
   Serial.println();
   }   
}


void colorSwitch (){
  switch (sign) {
      case 'W': for (int i=0; i<durat*duration; i++){digitalWrite(whitePin, LOW); delay (10);}  exit(); break;
      case 'S': for (int i=0; i<durat*duration; i++){digitalWrite(blackPin, LOW); delay (10);}  exit(); break;
      case 'Y': for (int i=0; i<durat*duration; i++){digitalWrite(yellowPin, LOW);delay (10);}  exit(); break;
      case 'R': for (int i=0; i<durat*duration; i++){digitalWrite(redPin, LOW);   delay (10);}  exit(); break;
      case 'G': for (int i=0; i<durat*duration; i++){digitalWrite(greenPin, LOW); delay (10);}  exit(); break;
      case 'B': for (int i=0; i<durat*duration; i++){digitalWrite(bluePin, LOW);  delay (10);}  exit(); break;

      default: Serial.print("Invalid value!"); delay(500); exit();}
}


///////////////////////////////////EXIT////////////////////////////////////////////////
void clr (){
    if (Serial.available() > 0){Serial.read();}
    delay (50);
}
void portReset (){
    digitalWrite(whitePin, HIGH);
    digitalWrite(blackPin, HIGH);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
}
void exit(){
  portReset ();
  delay (3000);
  Serial.println();
  Serial.println ("Finish! Wait... Restart program");
  Serial.println("***************************************************");
  Serial.println();Serial.println();Serial.println();Serial.println();
  delay (3000);
  reset ();  
}
