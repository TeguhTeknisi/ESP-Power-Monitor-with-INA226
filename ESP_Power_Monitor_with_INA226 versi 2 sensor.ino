//***Libraries***
#include <Wire.h>              // adds I2C library 
#include <DHT.h>               // adds DHT library
#include <LiquidCrystal_I2C.h> // adds LCD 16x2 or 20x4 Library
#include <INA.h>               // Zanshin INA Library v1.1

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

// For OTA
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>  // For OTA
#include <WiFiUdp.h>      // For OTA
#include <ArduinoOTA.h>   // For OTA

//LCD 1602
LiquidCrystal_I2C lcd(0x3F,16,2);
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// DHT Sensor
#define DHTPIN D6         // DHT digital pin ke D4
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "isi dengan kode auth blynk";
 
// Your WiFi credentials.
// Set password to "" for open networks.
const char ssid[] = "ISI SSID";  //  Network SSID (name)
const char pass[] = "ISI PASSWORD";  // Network password

#define SERIAL_SPEED 115200     
#define SAMPLING_INTERVAL 500 

BlynkTimer timer;


//INA226
INA_Class      INA;
byte devicesFound =      0; ///< Number of INAs found
//Device 1
float ina_current;
float ina_voltage;
float Power_Value;
//Device 2
float ina_current2;
float ina_voltage2;
float Power_Value2;

//Watt Hour meter
unsigned long last_time =0;
unsigned long current_time =0;
unsigned long diff_time =0;
unsigned long culm_time =0;
float energy=0 ; // Energy in Watt-Hour
float energy2=0 ; // Energy in Watt-Hour
float energykw=0 ; // Energy in Kilo Watt-Hour
float energykw2=0 ; // Energy in Kilo Watt-Hour
float saving=0;  // cost saving
float saving2=0;  // cost saving
float kwh_day=0;     // Energy in Mili Watt Hour every 24 hour
float kwh_day2=0;     // Energy in Mili Watt Hour every 24 hour
float kwh_today=0;   // Energy in Watt Hour every 24 hour
float kwh_today2=0;   // Energy in Watt Hour every 24 hour
float kwh_yesterday=0;  // Energy in Watt Hour every Yesterday
float kwh_yesterday2=0;  // Energy in Watt Hour every Yesterday
float kwh_daybefore1=0; // Energy in Watt Hour every 1 Day before
float kwh_daybefore2=0; // Energy in Watt Hour every 2 Day before
float kwh_daybefore3=0; // Energy in Watt Hour every 3 Day before
float kwh_daybefore4=0; // Energy in Watt Hour every 4 Day before
float kwh_daybefore5=0; // Energy in Watt Hour every 5 Day before
float kwh_daybefore6=0; // Energy in Watt Hour every 5 Day before


// sumber https://github.com/jaminNZx/ESP8266-Power-Monitor/blob/master/ESP8266-Power-Monitor.ino
// Device 1
float current_mA = 0.00, current_mA_Max;
float loadvoltage = 0.00, loadvoltageMax;
float power = 0.00, powerMax, powerAvg;
//Device 2
float current_mA2 = 0.00, current_mA_Max2;
float loadvoltage2 = 0.00, loadvoltageMax2;
float power2 = 0.00, powerMax2, powerAvg2;

// sumber https://www.engineersgarage.com/nodemcu-battery-voltage-monitor/
int BAT= A0;                   //Analog channel A0 as used to measure battery voltage
float RatioFactor=7.075;      //Resistors Ration Factor di multimeter 27,51v terukur di arduino 3,88v jadi 7.075

void setup()
{
  //I2C
  Wire.begin();
  //DHT
  dht.begin();
  //LCD
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();

  Serial.begin(115200);
  Serial.println("Booting");
  lcd.println("Booting");
 

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    lcd.setCursor(0,0);
    lcd.println("Connection Fail!");
    lcd.setCursor(0,1); 
    lcd.println("Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Print a message to the LCD.
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("ESP8266 + INA226");
  lcd.setCursor(0,1); 
  lcd.print("Power Monitor");
  delay (60);
  lcd.clear();
   
  devicesFound = INA.begin(41, 2000, 0);  // Sensor 1 dengan R Shunt SMD 2.000 R002 jadi 81,92mV/2mOhm = 40,96A tapi disarankan maks 20A karena PD 1 Watt dengan 20A x 81,92mV = 1,6384 Watt
  devicesFound = INA.begin(55, 1500, 1);  // Sensor 2 dengan R Shunt FL4 50A/75mV = 1,5mOhm jadi 81,92/1,5mOhm = 54,613A

  INA.setBusConversion(8500);            // Maximum conversion time 8.244ms, sebelumnya 8500 trus ganti 100 seperti di SoftPower, kembalikan lagi.
  INA.setShuntConversion(8500);          // Maximum conversion time 8.244ms, sebelumnya 8500 trus ganti 100 seperti di SoftPower, kembalikan lagi.
  INA.setAveraging(128);                 // Average each reading n-times, sebelumnya 128 terus ganti 100, trus ganti 32 seperti di SoftPower, kembalikan lagi.
  INA.setMode(INA_MODE_CONTINUOUS_BOTH); // Bus/shunt measured continuously

  // NodeMCU menyalakan LED onboard yang konek pin D4 ( di esp12 ) dan D0 aka GPIO16 ( di board NodeMCU )
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output - di ESP12F
  digitalWrite(LED_BUILTIN, LOW); 

  // Blynk Setup
  // You can also specify server:
  // Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  Blynk.begin(auth, ssid, pass, IPAddress(10,42,0,1), 8080);
  // Online Server
  // Blynk.begin(auth, ssid, pass);

  lcd.clear(); // bersihkan lcd
  lcd.setCursor(0,0); // kolom pertama, baris kesatu
  lcd.print("ONLINE = ");  lcd.println(ssid);

  ArduinoOTA.setHostname("NodeMCU Power Meter");  // For OTA
  ArduinoOTA.begin();  // For OTA

}

void loop()
{
  // Voltage Monitor using pin A0
  // sumber https://www.engineersgarage.com/nodemcu-battery-voltage-monitor/
  int value = LOW;
  float Tvoltage=0.0;
  float Vvalue=0.0,Rvalue=0.0;

  for(unsigned int i=0;i<10;i++){
  Vvalue=Vvalue+analogRead(BAT);         //Read analog Voltage
  delay(5);                              //ADC stable
  }
  Vvalue=(float)Vvalue/10.0;            //Find average of 10 values ( ganti 15 maka voltase turun 1v
  Rvalue=(float)(Vvalue/1024.0)*5;      //Convert Voltage in 5v factor
  Tvoltage=Rvalue*RatioFactor;          //Find original voltage by multiplying with factor
    /////////////////////////////////////Battery Voltage//////////////////////////////////
  value = HIGH;
  Blynk.virtualWrite(V40, Tvoltage);
  Blynk.virtualWrite(V41, String(Rvalue, 4) + String(" V Average"));
  Blynk.virtualWrite(V42, String(Tvoltage, 2) + String(" V"));
  
  ina_voltage = INA.getBusMilliVolts() / 975.0;
  //Arus dibawah 20mA dianggap 0 untuk menyiasati malam hari yang masih ada pemasukan atau pas dilepas inputnya.
  if ( INA.getBusMicroAmps() / 1000 < 20 ) { ina_current = 0; } else { ina_current = INA.getBusMicroAmps() / 1000.0; }
  Power_Value = Tvoltage * ina_current ;

  ina_voltage2 = INA.getBusMilliVolts(1) / 943.0;
  //Arus dibawah 20mA dianggap 0 untuk menyiasati malam hari yang masih ada pemasukan atau pas dilepas inputnya.
  if ( INA.getBusMicroAmps(1) / 1000 < 20 ) { ina_current2 = 0; } else { ina_current2 = INA.getBusMicroAmps(1) / 1000.0; }
  Power_Value2 = Tvoltage * ina_current2 ;

// Device 1
  Blynk.virtualWrite(V0, ina_voltage);
  Blynk.virtualWrite(V1, ina_current / 1000);
  Blynk.virtualWrite(V2, Power_Value / 1000);
  if (ina_current > 1000) {
    Blynk.virtualWrite(V3, String(ina_current / 1000, 3) + String(" A") );
  } else {
    Blynk.virtualWrite(V3, String(ina_current, 2) + String(" mA"));
  }   
  if (Power_Value > 1000) {
   Blynk.virtualWrite(V4, String((Power_Value / 1000), 3) + String(" W") );
  } else {
   Blynk.virtualWrite(V4, String(Power_Value, 0) + String(" mW") );
  }  

// Device 2
  Blynk.virtualWrite(V5, ina_voltage2);
  Blynk.virtualWrite(V6, ina_current2 / 1000);
  Blynk.virtualWrite(V7, Power_Value2 / 1000);
  if (ina_current2 > 1000) {
    Blynk.virtualWrite(V8, String(ina_current2 / 1000, 3) + String(" A") );
  } else {
    Blynk.virtualWrite(V8, String(ina_current2, 2) + String(" mA"));
  }   
  if (Power_Value2 > 1000) {
   Blynk.virtualWrite(V9, String((Power_Value2 / 1000), 3) + String(" W") );
  } else {
   Blynk.virtualWrite(V9, String(Power_Value2, 0) + String(" mW") );
  }  

  last_time = current_time;
  current_time = millis(); 
  energy = energy +  Power_Value *(( current_time -last_time) /3600000.0) ; // calculate power in Watt-Hour // 1 Hour = 60mins x 60 Secs x 1000 Milli Secs
  energy2 = energy2 +  Power_Value2 *(( current_time -last_time) /3600000.0) ; // calculate power in Watt-Hour // 1 Hour = 60mins x 60 Secs x 1000 Milli Secs
  energykw = energy/1000;
  energykw2 = energy2/1000;
  saving = 1446 * ( energy /1000000 );                                       // Rp 1.446 is cost per kWh
  Blynk.virtualWrite(V10,energy/1000); 
  Blynk.virtualWrite(V11,energy2/1000); 
  Blynk.virtualWrite(V12,saving);

  //Kwh harian dari https://openenergymonitor.org/forum-archive/node/198.html
  //Time Calcs
  if ( current_time > last_time ) {   //check to see if millis has overflowed back to zero (after approx 49 days)
      diff_time = current_time - last_time; } //if not, the time each emon cycle takes
       else {  //if millis has reset...
         diff_time = 4127; }   //t_diff = (the amount of time each average emon cycle takes), again dealing with the millis reset.
  culm_time += diff_time;
  last_time = current_time;

  if ( culm_time > (3600000 * 24)){ //check to see if 24hrs has elapsed and if so reset the max value to zero
   kwh_daybefore6 = kwh_daybefore5;
   kwh_daybefore5 = kwh_daybefore4;
   kwh_daybefore4 = kwh_daybefore3;
   kwh_daybefore3 = kwh_daybefore2;
   kwh_daybefore2 = kwh_daybefore1;
   kwh_daybefore1 = kwh_yesterday;
   kwh_yesterday  = kwh_today;
   kwh_yesterday2  = kwh_today2;
   kwh_day = 0;     // RESET
   kwh_day2 = 0;     // RESET
   kwh_today = 0;   // RESET
   kwh_today2 = 0;   // RESET
   loadvoltageMax = 0;     // RESET
   current_mA_Max = 0;   // RESET
   powerMax = 0; // RESET
   loadvoltageMax2 = 0;     // RESET
   current_mA_Max2 = 0;   // RESET
   powerMax2 = 0; // RESET
   culm_time = 0;   // RESET
  }

  //Calculate number of kwh generated.
  kwh_day += (Power_Value* diff_time) / 3600000 ;
  kwh_today = round(kwh_day/1000);
  Blynk.virtualWrite(V13,kwh_today); 
  Blynk.virtualWrite(V14,kwh_yesterday); 
  Blynk.virtualWrite(V15,kwh_daybefore1);
  Blynk.virtualWrite(V16,kwh_daybefore2);
  Blynk.virtualWrite(V17,kwh_daybefore3);
  Blynk.virtualWrite(V18,kwh_daybefore4);
  Blynk.virtualWrite(V19,kwh_daybefore5);
  Blynk.virtualWrite(V20,kwh_daybefore6);

  saving2 = 1446 * ( energy2 /1000000 );                                       // Rp 1.446 is cost per kWh
  kwh_day2 += (Power_Value2* diff_time) / 3600000 ;
  kwh_today2 = round(kwh_day2/1000);
  Blynk.virtualWrite(V25,saving2);
  Blynk.virtualWrite(V26,kwh_today2); 
  Blynk.virtualWrite(V27,kwh_yesterday2); 
  
  Blynk.virtualWrite(V28, String(ina_voltage, 2) + String(" V"));
  Blynk.virtualWrite(V29, String(ina_voltage2, 2) + String(" V"));

  // Mengukur Suhu dan Kelembaban
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  Blynk.virtualWrite(V30, temp);
  Blynk.virtualWrite(V31, hum);

  // sumber https://github.com/jaminNZx/ESP8266-Power-Monitor/blob/master/ESP8266-Power-Monitor.ino
  // LOAD VOLTAGE (HIGH) DEVICE 1
  loadvoltage = ina_voltage;
  if (loadvoltage > loadvoltageMax) {
    loadvoltageMax = loadvoltage;
    Blynk.virtualWrite(V32, String(loadvoltageMax, 3) + String(" V") );
  }
  // LOAD CURRENT (HIGH) DEVICE 1
  current_mA = ina_current;
  if (current_mA > current_mA_Max) {
    current_mA_Max = current_mA;
    if (current_mA_Max > 1000) {
      Blynk.virtualWrite(V33, String((current_mA_Max / 1000), 2) + String(" A") );
    } else {
      Blynk.virtualWrite(V33, String(current_mA_Max, 2) + String(" mA"));
    }
  }
  // LOAD POWER (HIGH) DEVICE 1
  power = Power_Value;
  if (power > powerMax) {
    powerMax = power;
    if (powerMax > 1000 ) {
      Blynk.virtualWrite(V34, String((powerMax / 1000), 2) + String(" W") );
    } else {
      Blynk.virtualWrite(V34, String(powerMax, 2) + String(" mW"));
    }
  }

  // LOAD VOLTAGE (HIGH) DEVICE 2
  loadvoltage2 = ina_voltage2;
  if (loadvoltage2 > loadvoltageMax2) {
    loadvoltageMax2 = loadvoltage2;
    Blynk.virtualWrite(V35, String(loadvoltageMax2, 3) + String(" V") );
  }
  // LOAD CURRENT (HIGH) DEVICE 2
  current_mA2 = ina_current2;
  if (current_mA2 > current_mA_Max2) {
    current_mA_Max2 = current_mA2;
    if (current_mA_Max2 > 1000) {
      Blynk.virtualWrite(V36, String((current_mA_Max2 / 1000), 2) + String(" A") );
    } else {
      Blynk.virtualWrite(V36, String(current_mA_Max2, 2) + String(" mA"));
    }
  }
  // LOAD POWER (HIGH) DEVICE 2
  power2 = Power_Value2;
  if (power2 > powerMax2) {
    powerMax2 = power2;
    if (powerMax2 > 1000 ) {
      Blynk.virtualWrite(V37, String((powerMax2 / 1000), 2) + String(" W") );
    } else {
      Blynk.virtualWrite(V37, String(powerMax2, 2) + String(" mW"));
    }
  }


  // Saat tidak ada arus masuk di device 1, maka tampilan akan diganti Ampere, Watt dan Energi dari device 2
  if ( INA.getBusMicroAmps() / 1000 < 20 ) { 
  lcd.clear(); //bersihkan lcd
  lcd.setCursor(0,0); // kolom ke 1 baris ke 1
  lcd.print(Tvoltage, 2); 
  lcd.print("V ");
  lcd.setCursor(7,0); // kolom ke 1 baris ke 7
  lcd.print(Power_Value2 / 1000, 1);
  lcd.print("W ");
  lcd.setCursor(0,1); // kolom kedua baris ke 1
  lcd.print(ina_current2 / 1000, 2);
  lcd.print("A");    
  lcd.setCursor(7,1); // kolom kedua baris ke 7
  lcd.print(kwh_today2, 1); 
  lcd.print("Wh");
   } else { 
   lcd.clear(); //bersihkan lcd
   lcd.setCursor(0,0); // kolom ke 1 baris ke 1
   lcd.print(Tvoltage, 2); 
   lcd.print("V ");
   lcd.setCursor(7,0); // kolom ke 1 baris ke 7
   lcd.print(Power_Value / 1000, 1);
   lcd.print("W ");
   lcd.setCursor(0,1); // kolom kedua baris ke 1
   lcd.print(ina_current / 1000, 2);
   lcd.print("A");    
   lcd.setCursor(7,1); // kolom kedua baris ke 7
   lcd.print(kwh_today, 1); 
   lcd.print("Wh");
  }


  // communication to Bylnk
  Blynk.run();
  timer.run();

  delay(SAMPLING_INTERVAL);
 
  ArduinoOTA.handle();  // For OTA
}
