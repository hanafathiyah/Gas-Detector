#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (12, 8, 6, 3, 4, 13);

Servo servo_0;
const int servoP = 2;
const int ping_pin = A3;
const int redLED_pin = A4;

int pos = 0;
int irP = 5;
int const gasP = A0;
int const buzzerP = 7;
int const red = 9;
int const blue = 10;
int const green = 11;
int sensePin = A1;
int sensorInput;
double temp;
int boo = 0;
int iterator = 0;


void setup()
{
  lcd.begin(16,2);
  lcd.print("Suhu:");
  
  pinMode(irP, INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);

  servo_0.attach(servoP);
  servo_0.write(pos);
  Serial.begin(9600);
}

void loop()
{
  
  int value = analogRead(gasP);
  sensorInput = analogRead(sensePin);
  temp = (double)sensorInput / 1024;
  temp = temp * 5;
  temp = temp - 0.5;
  temp = temp * 100;
  
  lcd.setCursor(6,0);
  lcd.print(temp);
   
  lcd.setCursor(13,0);
  lcd.print("C");

// membaca ping sensor  
    
  
  if (boo == 0){
    int statusSensor = digitalRead(irP);
  }
  
  if (value > 320){
    tone(buzzerP, 300, 50);
    read_sensor_ultrasonic();
    
    if (boo == 0) {
      int pos = 90;
      servo_0.write(pos);
    }
    else if (boo == 1) {
      int pos = 0;
      servo_0.write(pos);
    }
    RGB();
    
  }
  else {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    redLED_deactivated();
    lcd.setCursor(0,1);
    lcd.print("                ");
    if (boo == 1) {
    int pos = 0;
    servo_0.write(pos);
    }
  }
    
  int statusSensor = digitalRead(irP);
  Serial.println(statusSensor);
  Serial.println(boo);
  if (statusSensor == 0){
    boo = 1;
  }
  
  delay(1000);
}

void read_sensor_ultrasonic() {
  long dur, cm;
  lcd.setCursor(0,1);
  lcd.print("Jarak:");
  pinMode(ping_pin, OUTPUT);
  digitalWrite(ping_pin, LOW);
  digitalWrite(ping_pin, HIGH);
  digitalWrite(ping_pin, LOW);
  
  pinMode(ping_pin, INPUT);
  dur = pulseIn(ping_pin, HIGH);
  cm = long(dur / 29 / 2);
  
  lcd.setCursor(7,1);
  if(cm >= 100 && cm <= 330){
  	lcd.print(cm/100);
    lcd.setCursor(8,1);
    lcd.print(" meter");
    redLED_deactivated();
  } else if(cm >= 2 && cm < 100){
	lcd.print("BAHAYA!");  
    redLED_activated();
  }  
  lcd.print("              ");	
}

void redLED_activated(){
  pinMode(redLED_pin, OUTPUT);
  digitalWrite(redLED_pin, HIGH);
}

void redLED_deactivated(){
  pinMode(redLED_pin, OUTPUT);
  digitalWrite(redLED_pin, LOW);
}

void RGB(){
  if (temp <= 30) {
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(blue, HIGH);
      digitalWrite(green, HIGH);
    }
  else if ((temp > 30 ) && (temp <= 40)){
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(green, HIGH);
    }
  else if ((temp > 40) && (temp <= 50)){
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
    }
  else {
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(red, HIGH);
    }
}