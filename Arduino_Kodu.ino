/*
  AĞUSTOS 2022 TALPAY
  PROJE İSMİ: Görüntü İşleme İle Kapı Kilidi Açma
*/

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

int gelen_data;
int degisken = 0;
int sifre[500];
int i = 0;

void setup() {
  myservo.attach(9);
  Serial.setTimeout(1);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  myservo.write(0);

  lcd.setCursor(0, 0);
  lcd.print("SIFRE: ");
  lcd.setCursor(0, 1);
  lcd.print("000");
}

void loop() {
    /************************ PYTHONDAN GELEN STRİNG VERİNİN İNTEGER HALİNE GETİRİLMESİ ***************************/
  if (Serial.available() > 0) {
    gelen_data = Serial.readString().toInt();
  }

  /************************ GELEN RAKAMLARIN DİZİYE ATANIP ŞİFRE HALİNE GETİRİLMESİ ***************************/
  if (degisken != gelen_data) {
    degisken = gelen_data;
    sifre[i] = degisken;
    i += 1;
  }

  /************************ ŞİFRENİN LCD EKRANA YAZDIRILMASI ***************************/
  if (i >= 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SIFRE: ");
    lcd.setCursor(0, 1);
    lcd.print(sifre[0]);
    lcd.setCursor(1, 1);
    lcd.print(sifre[1]);
    lcd.setCursor(2, 1);
    lcd.print(sifre[2]);
  }

  if (i >= 2) {
    if (sifre[0] != 0 and sifre[1] != 0 and sifre[2] != 0 ) { // şifre girilirken sifirlanmasını engelliyor.
      /************************ ŞİFRENİN DOĞRU OLMA DURUMU ***************************/
      if (sifre[0] == 5 and sifre[1] == 4 and sifre[2] == 3 ) {
        myservo.write(90);
        delay(2000);
        myservo.write(0);
        sifre[0] = 0;
        sifre[1] = 0;
        sifre[2] = 0;
      }

      /************************ ŞİFRENİN YANLIŞ OLMA DURUMU ***************************/
      if (sifre[0] != 5 or sifre[1] != 4 or sifre[2] != 3 ) {
        myservo.write(0);
        sifre[0] = 0;
        sifre[1] = 0;
        sifre[2] = 0;
      }
      i = 0;
    }
  }

  delay(200);
}
