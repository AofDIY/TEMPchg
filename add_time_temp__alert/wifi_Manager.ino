 void WIFI_Manager(){
  
   //SPIFFS.format();
  Serial.println("mounting FS...");
  if (SPIFFS.begin()) { 
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
       // Serial.println("t0001");
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(line_token, json["line_token"]);
          strcpy(IdName, json["IdName"]);
          strcpy(TEMPalert, json["TEMPalert"]);
          strcpy(TIMEalert, json["TIMEalert"]);
     
        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
     /* digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000); */
          
  }

  else {
    Serial.println("failed to mount FS");
  }
  WiFiManagerParameter custom_text("<p>   </p>");
  WiFiManagerParameter custom_text0("<lbal> ป้อน ID Line Token  </label>");
  WiFiManagerParameter custom_text1("<lbal> ป้อน ชื่อ ที่ต้องการแจ้งเตือน  </label>");
  WiFiManagerParameter custom_text2("<lbal> ป้อน ค่า Temp  ℃ การแจ้งเตือน  </label>");
  WiFiManagerParameter custom_text3("<lbal> ระยะเวลาในการเตือน  นาที          </label>");
  
    WiFiManagerParameter custom_line_token("line", "line token", line_token, 50);
    WiFiManagerParameter custom_IdName("IdName", "IdName",IdName, 50);
    WiFiManagerParameter custom_TEMPalert("TEMPalert", "TEMPalert",TEMPalert, 5);
    WiFiManagerParameter custom_TIMEalert("TIMEalert", "TIMEalert",TIMEalert, 5);
 
  WiFiManager wifiManager;
 
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.addParameter(&custom_text);
  wifiManager.addParameter(&custom_text0);
  wifiManager.addParameter(&custom_line_token);
  wifiManager.addParameter(&custom_text1);
  wifiManager.addParameter(&custom_IdName);
  wifiManager.addParameter(&custom_text2);
  wifiManager.addParameter(&custom_TEMPalert);
  wifiManager.addParameter(&custom_text3);
  wifiManager.addParameter(&custom_TIMEalert);

//Serial.println("t0001");
//
  if (!wifiManager.autoConnect("Temperature Alert", "password")) { 
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  //Serial.println("t0001");
  Serial.println("wifi connected");
  strcpy(line_token, custom_line_token.getValue());
  strcpy(IdName, custom_IdName.getValue());
    strcpy(TEMPalert, custom_TEMPalert.getValue());
    strcpy(TIMEalert, custom_TIMEalert.getValue());
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["line_token"] = line_token;
    json["IdName"] = IdName;
      json["TEMPalert"] = TEMPalert;
      json["TIMEalert"] = TIMEalert; 
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }
    json.printTo(Serial);
    json.printTo(configFile);
  //  Serial.println("t0001");
    configFile.close();
     // digitalWrite(LED_BUILTIN, LOW); 

    
  }
  
  }
  
