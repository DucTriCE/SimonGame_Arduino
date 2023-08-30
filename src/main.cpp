#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


int yellow = 2, blue = 3, green = 4, red = 5, button1 = 8, button2 = 9, button3 = 10, button4 = 11, select=12, rnd = 0, a[100], mode=1, status=1;

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(select, INPUT);
  randomSeed(analogRead(0));
}

void caseShow(int a[], int &rnd){
	for(int i=0; i<rnd; i++){
    digitalWrite(a[i]+2,HIGH);
		delay(200);
    digitalWrite(a[i]+2,LOW);
    delay(500);
	}
}

void lose(){
  lcd.clear();
  digitalWrite(yellow, HIGH);
  digitalWrite(blue, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  if(mode==2){
    lcd.setCursor(0,0);
    lcd.print("Player "+String((rnd%2)+1)+" thua!!!");
  }
  else lcd.print(" Ban da thua!!! ");
  rnd=0;
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Dang tro ve menu");
  for(int i=0; i<10; i++){
    digitalWrite(yellow, !digitalRead(yellow));
    digitalWrite(blue, !digitalRead(blue));
    digitalWrite(green, !digitalRead(green));
    digitalWrite(red, !digitalRead(red));
    delay(180);
  }
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  lcd.clear();
  status=1;
}

void Play(int a[], int &rnd){
	int cnt = 0;
  if(mode==2){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Player "+(String)((rnd%2)+1)+"'s turn");
    lcd.setCursor(0,1);
    lcd.print("    Playing     ");
  }
	while(cnt!=rnd){
		if(digitalRead(button1)==HIGH){
      while(digitalRead(button1)==HIGH){
				digitalWrite(yellow, HIGH);
			}
			digitalWrite(yellow, LOW);
      lcd.clear();
			lcd.setCursor(0,0);
      lcd.print("   Pick yellow  ");
			if(a[cnt] == 0)cnt++;
			else{
				lose();
				break;
			}
		} 
    else if(digitalRead(button2)==HIGH){
      while(digitalRead(button2)==HIGH){
        digitalWrite(blue, HIGH);
      }
      digitalWrite(blue, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   Pick blue   ");
      if(a[cnt] == 1)cnt++;
      else{
        lose();
        break;
      }
		} 
    else if(digitalRead(button3)==HIGH){
      while(digitalRead(button3)==HIGH){
        digitalWrite(green, HIGH);
      }
      digitalWrite(green, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   Pick green   ");
      if(a[cnt] == 2)cnt++;
      else{
        lose();
        break;
      }
		} 
    else if(digitalRead(button4)==HIGH){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    Pick red    ");
      while(digitalRead(button4)==HIGH){
        digitalWrite(red, HIGH);
      }
      digitalWrite(red, LOW);
      if(a[cnt] == 3)cnt++;
      else{
        lose();
        break;
      }
		}
	}
	delay(750);
}

void caseGenerate_mode_1(int a[], int &rnd){
	int x = random(0, 1000)%4;
	a[rnd] = x;
	rnd++;
}

void caseGenerate_mode_2(int a[], int &rnd){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Player "+(String)((rnd%2)+1)+"'s turn");
  lcd.setCursor(0,1);
  lcd.print(" Generate color ");
  while(1){
    if(digitalRead(button1)==HIGH){
      while(digitalRead(button1)==HIGH)digitalWrite(yellow, HIGH);
      digitalWrite(yellow, LOW);
      a[rnd]=0;
      break;
    }else if(digitalRead(button2)==HIGH){
      while(digitalRead(button2)==HIGH)digitalWrite(blue, HIGH);
      digitalWrite(blue, LOW);
      a[rnd]=1;
      break;
    }else if(digitalRead(button3)==HIGH){
      while(digitalRead(button3)==HIGH)digitalWrite(green, HIGH);
      digitalWrite(green, LOW);
      a[rnd]=2;
      break;
    }else if(digitalRead(button4)==HIGH){
      while(digitalRead(button4)==HIGH)digitalWrite(red, HIGH);
      digitalWrite(red, LOW);
      a[rnd]=3;
      break;
    }
  }
  rnd++;
}

void play_3(){
  String map[4] = {"yellow", "blue", "green", "red"};
  while(1){
    int timeDelay = random(1500,5000);
    int randomize = timeDelay%3;
    int x = (random(0, 1000)%4);
    String s = "button"+String(x);
    delay(timeDelay);
    if(randomize==0){
      lcd.setCursor(0,0);
      lcd.print("Simon says: ");
      lcd.setCursor(0,1);
      lcd.print("   Choose " + map[x]);
      int start = millis();
      float total;
      while(1){
        if(digitalRead(button1)==HIGH){
          if(x==0){
            int end=millis();
            total = end-start;
            total*=0.001;
            lcd.clear();
            lcd.print("Total time: " + String(total));
            break;
          }
          else{
            lcd.clear();
            lose();
            return;
          }
        }
        else if(digitalRead(button2)==HIGH){
          if(x==1){
            int end=millis();
            total = end-start;
            total*=0.001;
            lcd.clear();
            lcd.print("Total time: " + String(total));
            break;
          }
          else{
            lcd.clear();
            lose();
            return;
          }
        }
        else if(digitalRead(button3)==HIGH){
          if(x==2){
            int end=millis();
            total = end-start;
            total*=0.001;
            lcd.clear();
            lcd.print("Total time: " + String(total));
            break;
          }
          else{
            lcd.clear();
            lose();
            return;
          }
        }
        else if(digitalRead(button4)==HIGH){
          if(x==3){
            int end=millis();
            total = end-start;
            total*=0.001;
            lcd.clear();
            lcd.print("Total time: " + String(total));
            break;
          }
          else{
            lcd.clear();
            lose();
            return;
          }
        }
      }
      delay(100);
      if(total>1.5){
        lcd.setCursor(0,1);
        lcd.print("  Vuot qua 1.5s!  ");
        delay(1500);
        lcd.clear();
        lose();
        return;
      }
      else{
        lcd.setCursor(0,1);
        lcd.print("    GOOD JOB    ");
        delay(1500);
        lcd.clear();
      }
    }
    else if (randomize==1){
      lcd.setCursor(0,0);
      lcd.print("Smiths says: ");
      lcd.setCursor(0,1);
      lcd.print("   Choose " + map[x]);
      int start = millis();
      int end = millis();
      float total = (end-start)*0.001;
      while(total<=3){
        end=millis();
        total=end-start;
        total*=0.001;
        if(digitalRead(button1)==HIGH || digitalRead(button2)==HIGH || digitalRead(button3)==HIGH || digitalRead(button4)==HIGH){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Not simon says!");
          lcd.clear();
          delay(1500);
          lose();
          return;
        }
      }
      delay(1500);
      lcd.clear();
    }
  }
}

void modeSelect(int &mode){
  int number = 3;
  lcd.setCursor(0,0);
  lcd.print("   Simon Game   ");
  lcd.setCursor(0,1);
  lcd.print("An nut chon mode");
  while(digitalRead(select)==LOW){
    if(digitalRead(button1)==HIGH){
      while(digitalRead(button1)==HIGH);
      mode=1;
      lcd.setCursor(0,1);
      lcd.print("Dang chon mode 1");
    }
    else if (digitalRead(button2)==HIGH){
      while(digitalRead(button2)==HIGH);
      mode=2;
      lcd.setCursor(0,1);
      lcd.print("Dang chon mode 2");
    }
    else if (digitalRead(button3)==HIGH){
      while(digitalRead(button3)==HIGH);
      mode=3;
      lcd.setCursor(0,1);
      lcd.print("Dang chon mode 3");
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Da chon Mode " + String(mode) + " ");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Bat dau trong  s");
  while(number!=0){
    lcd.setCursor(14,1);
    lcd.print(String(number));
    number--;
    delay(850);
  }
  lcd.clear();
  status=0;
}


void loop(){
  if(status==1)modeSelect(mode);
  switch (mode){
    case 1:
      caseGenerate_mode_1(a, rnd);
      caseShow(a, rnd);
      Play(a, rnd);
      break;
    case 2:
      caseGenerate_mode_2(a, rnd);
      delay(500);
      Play(a, rnd);
      delay(200);
      break;
    case 3:
      play_3();
      break;
  }

}