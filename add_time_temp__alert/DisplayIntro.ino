void DisplayIntro()
{
  String ssid = WiFi.SSID(); 
  String ip_Address = WiFi.localIP().toString();

  
    display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("!! WiFi connected !!");
 display.setTextSize(1);
   
   //===============================SSID==================================
   display.setTextColor(WHITE);
   display.setCursor(0,20);
  // Display static text
  display.println("SSID : ");
  display.setCursor(30,20);
  // Display static text
  display.println(ssid);
  
  //===============================IP========================================
  
  display.setCursor(0, 40);
  display.println("IP  : ");
  display.setCursor(30,40);
  // Display static text
  display.println(ip_Address);
  display.display(); 
 delay(5000);

  }
