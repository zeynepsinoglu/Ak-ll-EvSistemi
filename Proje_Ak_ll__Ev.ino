//200202061-200202062
//Tuğçe Nur Kardelen Mutlu-Zeynep Sinoğlu
#include <LiquidCrystal.h>
#include <Keypad.h>
LiquidCrystal lcd(34,33,32,31,30,29);

int Red_pin=12;
int Green_pin =13;
int Buzzer_pin=11;
int Lamp_pin=18;
int Alev_pin=A0;

const byte Satir=4;//keypad tanımlaması 
const byte Sutun=3;
String sifre="4165";
String girilenSifre="";

int Term_pin=A1;//termometre
float TempCel=0;//okumayı voltaja dönüştürür.
float Temp=0;//voltajı santigrata çevirir.
int TempValue=0;//Sıcaklık Sensorunden bir okuma alır.
int Hareket_pin=2;
int eveGiris=A6;
int SicaklikButton=A7;

char Tuslar[Satir][Sutun]={//keypad tanımı
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };
  byte SatPins[Satir]={9,8,7,6};
  byte SutPins[Sutun]={5,4,3};
Keypad TusTakimi=Keypad(makeKeymap(Tuslar),SatPins,SutPins,Satir,Sutun);

void setup() {
 lcd.begin(16,2);
 lcd.setCursor(1,2);
pinMode(Red_pin,OUTPUT);
pinMode(Green_pin,OUTPUT);
pinMode(Buzzer_pin,OUTPUT);
pinMode(Lamp_pin,OUTPUT);
pinMode(Alev_pin,INPUT);
pinMode(Hareket_pin,INPUT);
pinMode(eveGiris,INPUT);
}

void loop() {
if(digitalRead(eveGiris)==1){
  char Tus=TusTakimi.getKey();
if(Tus!=NO_KEY){
  switch(Tus){
     case '*':
     lcd.clear();
     girilenSifre="";
     lcd.setCursor(0,1);
     lcd.print("kilitleniyor");
     delay(1000);
     lcd.clear();
     break;
     case '#':
     lcd.setCursor(0,1);
     if(girilenSifre==sifre){
       lcd.print("SIFRE DOGRU");
        digitalWrite(Green_pin,HIGH);
      digitalWrite(Buzzer_pin,HIGH);
      delay(1000);
      digitalWrite(Buzzer_pin,LOW);
      digitalWrite(Green_pin,LOW);
      }
      else{
        lcd.print("SIFRE YANLIS");
        digitalWrite(Red_pin,HIGH);
        digitalWrite(Buzzer_pin,HIGH);
         delay(1000);
          digitalWrite(Buzzer_pin,LOW);
          digitalWrite(Red_pin,LOW);
        }
        delay(1000);
        lcd.clear();
        girilenSifre="";
        break;
        default:
        lcd.print("*");
        girilenSifre+=Tus;
        break;
     }
    }
  }
  int  hareket=digitalRead(Hareket_pin); 

if(digitalRead(eveGiris)==0){
   if(hareket==HIGH){
    lcd.println("DIKKAT !!!");
    lcd.setCursor(2,1);
    lcd.println("HAREKET VAR !!!");
    digitalWrite(Buzzer_pin,HIGH);
    digitalWrite(Lamp_pin,HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(Buzzer_pin,LOW);
    digitalWrite(Lamp_pin,LOW);
    }
  }
 int flame=digitalRead(Alev_pin);
  if(flame==HIGH){
     lcd.print("DIKKAT !!");
      lcd.setCursor(2,1);
      lcd.print("YANGIN ALARMI !!");
        digitalWrite(Buzzer_pin,HIGH);
      delay(1000);
      lcd.clear();
        digitalWrite(Buzzer_pin,LOW);
      }
      

TempValue=analogRead(Term_pin);//gerilimden sıcaklığadönonuşturme işlemi
TempCel=(TempValue/1023.0)*5000;
Temp=TempCel/10.0;
if(digitalRead(SicaklikButton)==1){
  lcd.println("Termometre");
  lcd.print(Temp);
  lcd.setCursor(2,1);
  delay(1000); 
  lcd.clear();
  }

if(Temp>30){
   lcd.print("DIKKAT !!");
      lcd.setCursor(2,1);
      lcd.print("SICAKLIK YUKSELDI !!");
        digitalWrite(Buzzer_pin,HIGH);
      delay(1000);
      lcd.clear();
        digitalWrite(Buzzer_pin,LOW);
  }
  if(Temp<20){
   lcd.print("DIKKAT !!");
      lcd.setCursor(2,1);
      lcd.print("SICAKLIK DUSTU !!");
        digitalWrite(Buzzer_pin,HIGH);
      delay(1000);
      lcd.clear();
        digitalWrite(Buzzer_pin,LOW);
  
  }
}
