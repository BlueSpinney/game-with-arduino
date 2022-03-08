#include <LiquidCrystal.h>  
int Contrast=20;
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   
int Xval = 0;
int Yval = 0;

int state = 0;

String heart = "<3";

int spawn = 0;

String enemy = "-";

int row = 6;

int eTF = 0;

int stb;
int pos = 3;

int dif = 7;

int t1 = 1;

int b1 = 0;

long dt = 100;

int point = 0;
 void setup()
 { 
    analogWrite(6,Contrast);
     lcd.begin(16, 2);
     Serial.begin(9600);
     lcd.setCursor(0,0);
     lcd.print(heart);
     
  }  
 void loop(){  
  b1 = digitalRead(7);
  lcd.setCursor(14,0);
  lcd.print(point);

  if (b1 == 1){
    if (dif == 7){
      dif = 4;
    }
    else if (dif == 4){
      dif = 2;
      dt = 75;
    }
    else if (dif == 2){
      dif = 4;
      dt = 100;
    }
  }

  
  Xval = analogRead(A0);
  Yval = analogRead(A1);

  Serial.print("X value : ");
  Serial.println(Xval);
  Serial.print("Y value : ");
  Serial.println(Yval);

  if (Xval < 100){

    lcd.setCursor(0, 0);
    lcd.print(heart);
    lcd.setCursor(0,1);
    lcd.print("                    ");
    state = 0;

  }
  else if (Xval > 800){
    
    lcd.setCursor(0, 1);
    lcd.print(heart);
    lcd.setCursor(0,0);
    lcd.print("             ");
    state = 1;

  }
  spawn = random(0,dif);

  if (spawn == 1 and eTF == 0){
    stb = random(0,3);
    if (stb-1 == 0){
      lcd.setCursor(6,0);
      lcd.print(enemy);
      pos = 0;
    }
    else if (stb-1 == 1){
      lcd.setCursor(6,1);
      lcd.print(enemy);
      pos = 1;
    }
    eTF = 1;
  }

  if (eTF == 1){
    
    lcd.setCursor(row,pos);
    lcd.print(enemy);
    lcd.setCursor(row+1,pos);
    lcd.print(" ");
    row = row - 1;
    if (row == 0){
      lcd.setCursor(0,pos);
      lcd.print("    ");
      eTF = 0;
      row = 6;
      if (state == pos){
        lcd.setCursor(0,0);

        while (t1 == 1){
          b1 = digitalRead(7);
          lcd.setCursor(0,0);
          lcd.print("         ");
          lcd.setCursor(0,0);
          lcd.print("Retry");
          lcd.setCursor(0,1);
          lcd.print("press B1");
          if (b1 == 1){
            state = 0;
            lcd.setCursor(0,0);
            lcd.print("                    ");
            lcd.setCursor(0,1);
            lcd.print("                    ");
            lcd.setCursor(0,0);
            lcd.print(heart);
            delay(1000);
            point = 0;
            break;
          }
        }

      }
      else{
        point = point + 1;
        lcd.setCursor(14,0);
        lcd.print(point);
      
    }
    
  }
  }
  

  Serial.print("row : ");
  Serial.println(row);
  Serial.print("pos : ");
  Serial.println(pos);

  

  delay(dt);
}
