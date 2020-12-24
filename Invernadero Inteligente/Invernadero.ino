#include <LiquidCrystal.h>
#include <Servo.h>

Servo Servomotor;

//Relevadores------------
int rele1 = 8;
int rele2 = 7;
//-----------------------

//Ventilador-------------
const int Ventilador = 13;
//-----------------------

//Fotoresistencia--------
int Fotoresistencia = 0;
double Luz;
//-----------------------

//Temperatura------------
int SensorTemp;
double Temperatura;
//-----------------------

LiquidCrystal lcd (12,11,5,4,3,2);
const int inPin =0;

void setup() {
    lcd.begin(16,2);
    Serial.begin(9600);
  
    pinMode(Ventilador, OUTPUT);
  
    pinMode(A1, INPUT);
  
  Servomotor.attach(9);
    
    pinMode(rele1, OUTPUT);
    pinMode(rele2, OUTPUT);
  
}

void loop() 
{
//Potenciometro----------
int Potenciometro = analogRead(A2);
float voltage = Potenciometro * (5.0 / 1023.0);
//-----------------------
  if(voltage < 2.50){
    digitalWrite(rele2, HIGH); 
  }
  else{
    digitalWrite(rele2, LOW);
  }
  
  if (Luz < 96) {
    digitalWrite(rele1, HIGH);   
  }
   else{
    digitalWrite(rele1, LOW); 
  }

  if (Temperatura < 30) {
    Servomotor.write(0);
    digitalWrite (Ventilador, LOW);
    lcd.setCursor(9,1);
    lcd.print("CERRADO");
  }
  if (Temperatura > 35) {
    Servomotor.write(90);
  digitalWrite (Ventilador, HIGH);
    lcd.setCursor(9,1);
    lcd.print("ABIERTO");
  }

  lcd.setCursor(0,0);
  lcd.print("TEMP:");
  lcd.print(Temperatura);  
  lcd.print(" C");
    
  lcd.setCursor(0,1);
  lcd.print("Luz:");
  lcd.print(Luz);

  delay(1000);
  
  Serial.println(analogRead(0));
  delay(100);

//Fotoresistencia-----------  
  Fotoresistencia = analogRead(A0);
  Luz = (double)Fotoresistencia /9.74;
//---------------------------
  
//Calculo De Temperatura A Centigrados
    SensorTemp = analogRead(A1);
    Temperatura =(double)SensorTemp / 1024;
    Temperatura = Temperatura * 5;
    Temperatura = Temperatura - 0.5;
    Temperatura = Temperatura * 100;
//--------------------------------------------
  
}
