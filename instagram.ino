void FollowersGET() {
    if((WiFi.status() == WL_CONNECTED)) {       // wait for WiFi connection
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://graph.facebook.com/v15.0/aaa?fields=followers_count&access_token=bbb"); 
    String FacebookRequest = "https://graph.facebook.com/v15.0/";           // concatenate the url
           FacebookRequest += IG_USER_ID;                                  // concatenate the url
           FacebookRequest += "?fields=followers_count";                  // concatenate the url
           FacebookRequest += "&access_token=" + INSTAGRAM_ACCESS_TOKEN; // concatenate the url
    http.begin(FacebookRequest); //HTTP    
    Serial.print("[HTTP] GET...\n"); // start connection and send HTTP header
    int httpCode = http.GET();          // record the result of the connexion (negative on error)
    if(httpCode > 0) {                 // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);     // example : {"followers_count":17976,"id":"170--------14"}
        String CuttingString = payload; // now cuting the result 
        int n = CuttingString.length();  // n is the lenght of the payload
        CuttingString.remove(0, 19);    // remove the first 19th char
        n = CuttingString.length();    // re count the strinh lenght
        CuttingString.remove(5);      // remove all the char after the 5th char
        Serial.println(CuttingString);
        String followers = CuttingString;
        Serial.print("followers_count : ");
        Serial.println(CuttingString);
        
        // ePaper display
          display.setRotation(1);
          u8g2Fonts.setFont(u8g2_font_logisoso32_tn); // u8g2_font_fub30_tf / u8g2_font_logisoso62_tn /u8g2_font_logisoso32_tn
          uint16_t x = display.width() / 2 - 100 ; // position en largeur 0 tout a gauche
          uint16_t y = display.height() / 2 + 50;
          
          u8g2Fonts.print(CuttingString);
      
          //display.update();

          u8g2Fonts.setFont(u8g2_font_fub30_tf);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
          u8g2Fonts.setCursor( 70, y);
          u8g2Fonts.print(CuttingString);
         
          //display.update();
      }
    } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
           }
        http.end();
    }
}
