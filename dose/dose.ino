/* Ginger v4.0 19.07.2020  */

void(* reset) (void) = 0;

//Модуль SM1
const int clockPinSM1 = 8; //Пин подключен к SH_CP входу 74HC595
const int latchPinSM1 = 9; //Пин подключен к ST_CP входу 74HC595
const int dataPinSM1 = 10; //Пин подключен к DS входу 74HC595
//Модуль SM2
const int clockPinSM2 = 11; //Пин подключен к SH_CP входу 74HC595
const int latchPinSM2 = 12; //Пин подключен к ST_CP входу 74HC595
const int dataPinSM2 = 13; //Пин подключен к DS входу 74HC595

String color,base;
int msgFlag=0,msgFlag1=0,msgFlag2=0;
String char_0,char_1,char_2,char_3,char_4,char_5,char_6,char_7;
int quantity,blackness,chromaticness,hue,yellow,red,green,blue;
float hueQuant = chromaticness*quantity/100;

unsigned int staticBitSM1 = 0b0000000000000000;   // 0000 white, 0000 black, 0000 yellow, 0000 red.
unsigned int dynamicBitSM1 =0b0000000000000000;   // 0 clock, 0 dir, 0 enable, 0 speed 1/2

unsigned int staticBitSM2 = 0b0000000000000000;   // 0000 green, 0000 blue.
unsigned int dynamicBitSM2 =0b0000000000000000;

int freq = 50000;
int durat=1;

void setup() {
  Serial.begin(9600);
  Serial.println("***************************************************");
  Serial.println("Hello!");
  Serial.println("Please, input your NCS color (ex 5502R or 4055B40G)");
  Serial.println("***************************************************");
  Serial.println();
}

void loop() {
    if (color =="\0") {
      get_color ();}

    if (base =="\0"&&color !="\0") {
      while (msgFlag==0) {Serial.println("Enter total quantity, ml (min 5, max 25)"); msgFlag++;}   
      get_base ();}

}

/////////////////////////////////COLOR INPUT/////////////////////////////////////////
void get_color (){
   clr (); 
   if (Serial.available() > 0){
   color = Serial.readString();
   delay (5);
   Serial.println(color);
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
   if (quantity<5||quantity>25) {Serial.print("Invalid value!"); delay(500); exit();}
   while (msgFlag1==0) {Serial.println("Color preparing..."); msgFlag1++;}
   while (msgFlag2<51) {Serial.print("*"); delay(300); msgFlag2++;} Serial.println();
   delay (3000);
   exit();}
}
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////COLOR SEQUENSE//////////////////////////////////////////
  void nuance (){
    char_0 = color.charAt (0);
    char_1 = color.charAt (1);
    int blackInt0 = char_0.toInt();
    int blackInt1 = char_1.toInt();
    blackness= (blackInt0*10+blackInt1);
    Serial.println(blackness);
  }
  void chrom (){
    char_2 = color.charAt (2);
    char_3 = color.charAt (3);
    int chromInt0 = char_2.toInt();
    int chromInt1 = char_3.toInt();
    chromaticness= (chromInt0*10+chromInt1);
    Serial.println(chromaticness);
  }
  void hue_1 (){
    char_4 = color.charAt (4);
    Serial.println(char_4);
  }
  void hue_percent (){
    char_5 = color.charAt (5);
    char_6 = color.charAt (6);
    int hueInt0 = char_5.toInt();
    int hueInt1 = char_6.toInt();
    hue= (hueInt0*10+hueInt1);
    Serial.println(hue);
  }
  void hue_2 (){
    char_7 = color.charAt (7);
    Serial.println(char_7);
    Serial.println();
  }
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////EXIT////////////////////////////////////////////////
void clr (){
    if (Serial.available() > 0){Serial.read();}
    delay (50);
}
void exit(){
  Serial.println();
  Serial.println ("Wait... Restart program");
  Serial.println("***************************************************");
  Serial.println();Serial.println();Serial.println();Serial.println();
  delay (3000);
  reset ();  
}
