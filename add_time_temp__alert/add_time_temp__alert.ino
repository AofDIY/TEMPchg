// display SSD1306
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//potentiometer  ตัวปรับค่า
int val; 

#include <FS.h>
#include <TridentTD_LineNotify.h>
//#include <WiFiClientSecureAxTLS.h>
#include <ESP8266WiFi.h> 

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPin D6
DHT dht(DHTPin, DHTTYPE);

#define pininput D1
#define SET_PIN D7      //ขา เอาไว้รีเซตค่า
#define pinOutput D5    //ขาไฟเลี้ยง +  dht22
//#define LED1 2       //ไฟสถานะเขียว
//#define LED2 D7       //ไฟสถานะแดง

int resetState ;
int value;
String msg;
boolean flag = 0;

float temp;
float humi;
String ip_1;
String mac_addr;

 long previousMillis = 0;        // will store last time LED was updated
 
// constants won't change:
const long interval = 60000; 

char line_token[50] = "Input Line notify Token";
char IdName[50] = "  name ";
char TEMPalert[5] = "00";
char TIMEalert[5] = "00";


bool shouldSaveConfig = false;
int buttonState;

const char* host = "tempchg.synology.me";
const int httpsPort = 443;

 //------------เช็ค wifi---------------------------------------------------------------------------
  //  WiFiClient client;    //
   // const int httpPort = 80;

    unsigned long previousMillis_WIFI = 0;
     unsigned long interval_WIFI = 30000;
    //---------------------------------------------------------------------------------------------------



//----------เวลาในการส่งข้อมูล SQL -------------
int TimesendData = 60000;
long now = millis();
long lastMeasure = 0;


//
long now1 = millis();
long lastMeasure1 = 0;
//----------เวลาเตือนใน line  นับเป็นรอบของ TimesendData  -------------

//int Timesendline = 5;
// Timers auxiliar variables

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}


//--------------------------------------------------------------------------setup()-----------------------------------------------------------------------------------------------------------------------------------------
void setup () {
     //  resetState = digitalRead(SET_PIN);
    
    
     
  
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(LED_BUILTIN, LOW);
  
   dht.begin();
  Serial.begin(9600);
  Serial.println();
  pinMode(pininput, INPUT_PULLUP); 
  pinMode(SET_PIN, INPUT_PULLUP);
  pinMode(pinOutput, OUTPUT);
  digitalWrite(pinOutput, HIGH);
 // pinMode(LED1, OUTPUT);
 // pinMode(LED2, OUTPUT);
       
//display
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
   delay(2000);
   //------------------------------------------DisplayWellcome-------------------------------------------------------------------------------------------
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 0);
  // Display static text
  display.println("Please connect ");
  display.setCursor(0, 20);
  display.println(" SSID =  Temperature Alert");
  display.setCursor(0, 40);
  display.println("Password = password");
  display.setCursor(30, 50);
  display.println("AOF,D.I.Y!");
  display.display(); 



  WIFI_Reset ();
 
 // delay(2000);
//============================================WIFI_Manager=================================================================================================================================================================================
 WIFI_Manager();
//===================================================================================================================================================================================================================================
 DisplayIntro();

  
  Serial.println();
  Serial.print("local ip : ");
  Serial.println(WiFi.localIP());
  Serial.print("Line Token : ");
  Serial.println(line_token);


//============================================แจ้งเตือนใน LINE เปิดเครื่อง==========================================================================================================================================================================
    LINE.setToken(line_token);
   //  LINE.notifySticker(2,34); // เป็นคำสั่งใช้ ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
     LINE.notify("สวัสดีครับระบบแจ้งอุณหภูมิ  "+String(IdName)+"  พร้อมแจ้งเตือนแล้วครับ ^-^!");
    }

    //---------เวลาในการ ส่ง ข้อมูลเตือนใน line -----------count = 1 รอบของ  TimesendData
    /*
int TimeLine_ = atoi(TIMEalert);
int TEMPLine_ = atoi(TEMPalert);
int TimesendLine = 60000*TimeLine_; */
//----------------------------------------------------------------------------------------loop()----------------------------------------------------------------------------------------------------------------------------------------------

  
  void loop() 
{  
  check_Connect_WIFI();  //เช็คการเชื่อมต่อ WIFI 
  val = analogRead(A0);// อ่านค่า Analog ขาA0 เก็บไว้ในตัวแปร Val
  val = map(val, 0, 1023, -100 , 100 ); // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
  float av = val*0.1; //ค่าที่จะเอาไปใช้
  
   
   
   String IdName_ = IdName;
  Serial.print(".");/*
  
   String IdName_ = IdName;
  Serial.print(".");/*
   Serial.println(atoi(TIMEalert));
  Serial.print("TEMPLine_");
  Serial.println(TEMPLine_);
  */

///-----------------Read DHT22----------------------------------------------------
       float h = dht.readHumidity();
       float t = dht.readTemperature();
     
       float f = dht.readTemperature(true);
       delay(2000);
  ///====================  แสดงค่าออกจอ  ====================================================

        ShowDisplay (av,t,h,WiFi.SSID(),IdName);
  
    
  // กำหนดเวลาในการส่งข้อมูลSQL
    now = millis();
   if (now - lastMeasure > TimesendData)
  {
     
       String ip_ = WiFi.localIP().toString();
        mac_addr = WiFi.macAddress();
   
        temp =t+av;
        humi=h;
        ip_1=ip_;
    
       if(isnan(temp) || isnan(humi))
       {
         display.clearDisplay();
         display.setTextColor(WHITE);
         display.setTextSize(1);
         display.setCursor(0, 0);
         display.println("!!!!!Failed to read DHT22!!!!!");
         display.display(); 
         ///////
 
         Serial.println("Failed to read DHT22");
         delay(1000);
         Serial.println("restart");
         delay(1000);
         digitalWrite(pinOutput, LOW);
         delay(1000);
          ESP.restart();       // คำสั่งรีเซ็ต ESP
       }
      else
      {
         Serial.print("Humidity: ");
         Serial.print(humi);
         Serial.print(" %\t");
         Serial.print("Temperature: ");
         Serial.print(temp);
         Serial.println(" ℃");
         Serial.print("NAME : ");
         Serial.print(IdName_);
        }
    lastMeasure = now;
    sendtoSQLServer(ip_,temp,humi,IdName_,mac_addr);
    //  sendlineNotify(temperature,humidity,count);

        delay(100);   
  }

  // กำหนดเวลาในการส่งข้อมูลLine
      now1 = millis();
    if (now1 - lastMeasure1 > atoi(TIMEalert)*60000)
  {
    lastMeasure1 = now1;
    sendlineNotify(temp,humi,IdName_);
   Serial.print("TimeLine_");
   Serial.println(atoi(TIMEalert));

   Serial.print("now1");
   Serial.println(now1);
  }
 
}
