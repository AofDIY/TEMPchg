void ShowDisplay (float av,float t,float h,String ssidSHOW,String IdNameSHOW)
{
    
     
  //===============================SSID==================================
  display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(0,0);
  // Display static text
  display.println("SSID: ");
  display.setCursor(30,0);
  // Display static text
  display.println(ssidSHOW);

  //=============================== name ==================================
   display.setTextColor(WHITE);
   display.setCursor(0,20);
  // Display static text
  display.println("name: ");
  display.setCursor(30,20);
  // Display static text
  display.println(IdNameSHOW);
     
     //A04
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println("A0 :");
  display.setCursor(30, 30);
  // Display static text
  display.println(av);

///temp
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(0,40);
  // Display static text
  display.println("T :");
  display.setCursor(20,40);
  // Display static text
  display.println(t);

//humi
display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(70,40);
  // Display static text
  display.println("H :");
  display.setCursor(95,40);
  // Display static text
  display.println(h);

//temp+av

   display.setTextColor(WHITE);
   display.setCursor(0,50);
  // Display static text
  display.println("T + a0 :");
  display.setCursor(70,50);
  // Display static text
  display.println(t+av);
  display.display(); 
  delay(100);
  
  
  
  
  
  }
