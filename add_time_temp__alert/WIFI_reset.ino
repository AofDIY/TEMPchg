void WIFI_Reset (){
 if (digitalRead(SET_PIN) == LOW) 
    {
  Serial.println("wifi reset ?.waiting ...");
   display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(30, 0);
      // Display static text
      display.println("wifi reset ?.waiting ...");
      display.display(); 

  WiFiManager wm;
  unsigned long last1;
  SPIFFS.format();
  Serial.println(" reset succes ...");
    display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      // Display static text
      display.println(" *-*reset succes*-*  ");
      display.display(); 
     
 
  wm.resetSettings();
   ESP.reset();
   delay(5000);
    }

/*
resetState = digitalRead(SET_PIN);
  if (digitalRead(SET_PIN) == LOW) 
    {
       SPIFFS.format();
         ESP.reset();
      Serial.println("wifi reset ?.waiting ...");
      
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(30, 0);
      // Display static text
      display.println("reset .waiting ...");
      display.display(); 
     
       wm.resetSettings();
        SPIFFS.format();
         ESP.reset();

        Serial.println(" reset succes ...");
      
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(30, 0);
      // Display static text
      display.println("reset is succes ...");
       display.setCursor(0,40);
  // Display static text
       display.println("please un Jumper");
       display.display(); 
   //  delay(5000);
    }
    else
    {
      
      }
  
  
/*
    
     if (digitalRead(SET_PIN) == LOW) {
      Serial.println("wifi reset ?.waiting ...");
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(30, 0);
      // Display static text
      display.println("wifi reset ?.waiting ...");
      display.display(); 
      ///////
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000); 
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(3000);

          
           
          
         //wifiManager.resetSettings();
          wm.resetSettings();
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(30, 0);
        // Display static text
        display.println("Wifi Reset setting ... OK!");
        display.display(); 
        
          Serial.println("Wifi Reset setting ... OK!");
           delay(5000);

  ///////
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(3000);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(1000); 
          
          
          delay(5000);
          ESP.restart();
        }*/
      
     
    
   
  
  
}
  
