/* Ginger v5.0 30.05.2021  */

void(* reset) (void) = 0;

const int whitePin = 5; //Белый
const int blackPin = 6; //Черный
const int yellowPin = 7; //Желтый
const int redPin = 8; //Красный
const int greenPin = 9; //Зеленый
const int bluePin = 10; //Синий

String color,base;
int msgFlag=0,msgFlag1=0,msgFlag2=0,passFlag=0,exitFlag=0;
String char_0,char_1,char_2,char_3,char_5,char_6;
float quantity,blackness,chromaticness,hue,hueQuant,yellow,red,green,blue;
char char_4,char_7,hueColor1, hueColor2;


//int freq = 3;

///////////////////////calibration///////////////////////////////////////
int whiteDurat=388;   //388
int blackDurat=14;   //380 (/26)
int yellowDurat=200;  //367 (/1.8)
int redDurat=363;     //363
int greenDurat=358;   //358
int blueDurat=376;    //376
/////////////////////////////////////////////////////////////////////////

int durat=1;
int rotate =1;

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
  Serial.println("    Chek the paints before use - fill it up! ");
  Serial.println("Please, input your NCS color (ex 5000N or 2550Y50R)");
  Serial.println("***************************************************");
  Serial.println();  
}

void loop() {
    if (color =="\0") {
      get_color ();}

    if (base =="\0"&&color !="\0") {
      while (msgFlag==0) {Serial.println("Enter total quantity, ml (min 5, max 100)"); msgFlag++;}   
      get_base ();}

    if (base !="\0"&&color !="\0"&&passFlag==1) {
      whiteStep ();
      blackStep ();
      hue1Step ();
      hue2Step ();
     // delay (freq);
      exitFlag=1;
      }

     if (passFlag==1&&exitFlag==1) {
      delay (3000);
      exit();
     }
}

/////////////////////////////////COLOR INPUT/////////////////////////////////////////
void get_color (){
   clr (); 
   if (Serial.available() > 0){
   color = Serial.readString();
   delay (5);
   Serial.println(color);
   Serial.println();
   nuance ();
   chrom ();
   hue_1 ();
   hue_percent ();
   hue_2 ();}   
}
void get_base () {  
   if (Serial.available() > 0){
   base = Serial.readString();
   delay (5);
   quantity=base.toInt();
   Serial.println(quantity);
   if (quantity<5||quantity>100) {Serial.print("Invalid value!"); delay(500); exit();}
   while (msgFlag1==0) {Serial.println("Color preparing..."); msgFlag1++;}
   Serial.println();
   passFlag=1;
   }
}
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////COLOR SEQUENSE//////////////////////////////////////////
  void nuance (){
    char_0 = color.charAt (0);
    char_1 = color.charAt (1);
    int blackInt0 = char_0.toInt();
    int blackInt1 = char_1.toInt();
    blackness= (blackInt0*10+blackInt1);
    Serial.print("Blackness:    ");
    Serial.println(blackness);
  }
  void chrom (){
    char_2 = color.charAt (2);
    char_3 = color.charAt (3);
    int chromInt0 = char_2.toInt();
    int chromInt1 = char_3.toInt();
    chromaticness= (chromInt0*10+chromInt1);
    Serial.print("Cromaticness: ");
    Serial.println(chromaticness);
  }
  void hue_1 (){
    char_4 = color.charAt (4);
    hueColor1=char_4;
    Serial.print("Color 1:      ");
    Serial.println(hueColor1);
  }
  void hue_percent (){
    char_5 = color.charAt (5);
    char_6 = color.charAt (6);
    int hueInt0 = char_5.toInt();
    int hueInt1 = char_6.toInt();
    hue=(hueInt0*10+hueInt1);
    Serial.print("Hue:          ");
    Serial.println(hue);
  }
  void hue_2 (){
    char_7 = color.charAt (7);
    hueColor2=char_7;
    Serial.print("Color 2:      ");
    Serial.println(hueColor2); 
    Serial.println();   
    Serial.println();
  }
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////color calculate/////////////////////////////////
void  whiteStep (){
    float whiteQuant = ((100 - blackness - chromaticness)*quantity/100);
    Serial.print("White:    ");
    Serial.println(whiteQuant);
    for (int i=0; i<(whiteQuant*whiteDurat); i++) {whiteOut();}
    delay (20);
}    
void  blackStep (){
    float blackQuant = (blackness*quantity)/100;
    Serial.print("Black:    ");
    Serial.println(blackQuant);
    for (int i=0; i<(blackQuant*blackDurat); i++) {blackOut();}
    delay (20);
}
void  hue1Step (){  
    hueQuant = chromaticness*quantity/100;
    float hue1Quant=(100-hue)*hueQuant/100;
    Serial.print("Color 1:  ");
    Serial.println(hue1Quant);
    duratSwitch1 ();
    for (int i=0; i<(hue1Quant*durat); i++) {colorSwitch1();}
    delay (20);
}
void  hue2Step (){
    float hue2Quant=hue*hueQuant/100;
    Serial.print("Color 2:  ");
    Serial.println(hue2Quant);
    duratSwitch2 ();
    for (int i=0; i<(hue2Quant*durat); i++) {colorSwitch2();}
    delay (20);
    
    portReset ();
    while (msgFlag2<51) {Serial.print("*"); delay(50); msgFlag2++;} Serial.println();
   
    Serial.println("**********************Finish!**********************");
}
void colorSwitch1 (){
  switch (hueColor1) {
      case 'Y': yellowOut(); break;
      case 'R': redOut(); break;
      case 'G': greenOut(); break;
      case 'B': blueOut(); break;
      case 'N': blackOut(); break;
      default: Serial.print("Invalid value!"); delay(500); exit();}
}
void colorSwitch2 (){
  switch (hueColor2) {
      case 'Y': yellowOut(); break;
      case 'R': redOut(); break;
      case 'G': greenOut(); break;
      case 'B': blueOut(); break;
      case 'N': blackOut(); break;
      default: Serial.print("Invalid value!"); delay(500); exit();}
} 
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////duratSwitch///////////////////////////////////

  void duratSwitch1 () {
    switch (hueColor1) {
      case 'Y': durat=yellowDurat; break;
      case 'R': durat=redDurat; break;
      case 'G': durat=greenDurat; break;
      case 'B': durat=blueDurat; break;
    }
  }

    void duratSwitch2 () {
    switch (hueColor2) {
      case 'Y': durat=yellowDurat; break;
      case 'R': durat=redDurat; break;
      case 'G': durat=greenDurat; break;
      case 'B': durat=blueDurat; break;
    }
  }

//////////////////////////////////color out////////////////////////////////////
void whiteOut(){
  digitalWrite(whitePin, LOW);
  delay (rotate);  
  digitalWrite(whitePin, HIGH);
  }
void blackOut(){
  digitalWrite(blackPin, LOW);  
  delay (rotate);
  digitalWrite(blackPin, HIGH);
  }
void yellowOut(){
  digitalWrite(yellowPin, LOW);
  delay (rotate);
  digitalWrite(yellowPin, HIGH);
  }
void redOut(){
  digitalWrite(redPin, LOW);
  delay (rotate);
  digitalWrite(redPin, HIGH);
  }
void greenOut(){
  digitalWrite(greenPin, LOW);
  delay (rotate);  
  digitalWrite(greenPin, HIGH);
  }
void blueOut(){
  digitalWrite(bluePin, LOW);
  delay (rotate);
  digitalWrite(bluePin, HIGH);
  }
/////////////////////////////////////////////////////////////////////////////////


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
  Serial.println();
  Serial.println ("Wait... Restart program");
  Serial.println("***************************************************");
  Serial.println();Serial.println();Serial.println();Serial.println();
  delay (3000);
  reset ();  
}
