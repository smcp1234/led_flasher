#include "Arduino.h"
#include "myserver.h"

const char *PARAM_INPUT_1 = "output";
const char *PARAM_INPUT_2 = "state";
AsyncWebServer servee(80);
MyServer::MyServer()
{
     // Initialize LittleFS
     Serial.print("Server Object");
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
}

String outputState(int output)
{
    if (digitalRead(output))
    {
        return "checked";
    }
    else
    {
        return "";
    }
}

String processor(const String &var)
{
    if (var == "BUTTONPLACEHOLDER")
    {
        String buttons = "";
        buttons += "<h4>Output - GPIO 16</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"16\" " + outputState(16) + "><span class=\"slider\"></span></label>";
        return buttons;
    }
    return String();
}

void MyServer::setUp()
{
  
  Serial.print("server created");

    // Route for root / web page
  servee.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    //request->send_P(200, "text/html", index_html, processor);
    request->send(LittleFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  servee.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");
  });

 // Route to load style.css file
  servee.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/main.js", "text/javascript");
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  servee.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    } else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });
  servee.on("/*", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Invalid Route");
    //request->send(LittleFS, "/main.js", "text/javascript");
  });

  // Start server
  servee.begin();
}


