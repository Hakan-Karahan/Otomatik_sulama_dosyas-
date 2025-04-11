//gerekli kütüphane tanımlamaları (ekran kütüphaneleri tanımları)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD ekran tanımı 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin tanımları
const int nemSensorPin = A0; //nem sensörü pini
const int rolePin = 8;  //role pini

//nem sensörü değerleri 
int nemDegeri = 0;  //nem sensöründen gelen değerin tutuldıuğu değişken
int nemEsik = 905;  //eşik değer tanımlaması bu değer altı motor çalışmaya başlar

void setup() {
  Serial.begin(9600); //pc üzerinde uygulamadan seri haberleşme başlatılır
  
  lcd.init();  //lcd ekran başlatılır
  lcd.backlight(); // arka ışık açılır 
  lcd.setCursor(0,  0);  //lcd ekran 1, sütun tanımı
  lcd.print(" Sulama Sistemi"); //1. sutunda yazan yazı
  lcd.setCursor(0, 1);  //lcd ekran 2. sütun tanımı
  lcd.print(" Baslatiliyor..."); //2. sütunda yazan yazı

  delay(500); //0,5sn ekranda bu yazı gözükçek
  lcd.clear(); //ekranı temizleme işlemi bu kod ile sağlanıyor
  
  pinMode(rolePin, OUTPUT);   //rölepinini çıkış pini olarak tanımlar
  digitalWrite(rolePin, LOW); // Röleyi başlangıçta kapalı tutmak için low seçiyoruz

}

void loop() {
  nemDegeri = analogRead(nemSensorPin); //nemdeğerinin burda analog olarak okunması sağlanır.A0 pininden değer okunur
  Serial.print("Nem Degeri: "); //değer serial monitöre yazdırılır
  Serial.println(nemDegeri); //

  lcd.setCursor(0, 0); //lcd ekrandaki ilk sütun
  lcd.print("Nem: "); 
  lcd.print(nemDegeri); // yukarı ve aşağıdaki kodlar ile nem değeri gözükmesi burda sağlanır.
  lcd.print("   ");

  if (nemDegeri > nemEsik) { //eğer toprak kuru ise (eşik değer üstünde ise)
  
    digitalWrite(rolePin, HIGH); //roleye bu kod ile sinyal gönderilir röle motoru çalıştıran kod budur
    lcd.setCursor(0, 1);        
    lcd.print("Sulama: Pasif ");   //yukarıdaki kod ile de lcd ekranın 2. sütununda bu yazı yazar 
  } else {  // toprak yaş ise (eşik değer altında ise )
    
    digitalWrite(rolePin, LOW); // roleye bu kod ile sinyal gönderilir ve röle motorunu çalıştırmayı durdurur
    lcd.setCursor(0, 1);  
    lcd.print("Sulama: Aktif "); //yukarıdaki kod ile de lcd ekranın 2. sütununda bu yazı yazar
  }

  delay(2000); // 2 saniyede bir kontrol etme işlemini yapar(nem sensörü 2sn sonra tekrar değerleri  okumaya başlar)
}