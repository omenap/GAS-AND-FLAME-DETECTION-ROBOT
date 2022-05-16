#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ESP8266WebServer.h>
ESP8266WebServer webserver(80);

#define FIREBASE_HOST "smoke-and-fire-robot-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "NYgBdJOwMqnItoVfRM82L2FQOmWBXUFQ3xfUkgZU"

FirebaseData firebaseData;
FirebaseData loadData;
String str;
void setup() {
  Serial.begin(115200);
  Serial.begin(9600);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin("8pxX2", "coldmineral1");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected");
}

void loop() {
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, Serial);

  //Test parsing
  if (error) {
    Serial.println("Invalid Json Object");
    return;
  }

  int text = doc["Smoke"];
  Serial.println(text);
  int text2 = doc["Fire"];
  Serial.println(text2);

  if ( text == 1 && text2 == 1) {
    str = String("Smoke Detected_") + String("Fire Detected");
    Firebase.setString(firebaseData, "Environment", str);
  }
  else if ( text == 0 && text2 == 1) {
    str = String("NO Smoke Detected_") + String("Fire Detected");
    Firebase.setString(firebaseData, "Environment", str);
  }
  else if ( text == 1 && text2 == 0) {
    str = String("Smoke Detected_") + String("No Fire Detected");
    Firebase.setString(firebaseData, "Environment", str);
  }
  else {
    str = String("NO Smoke Detected_") + String("No Fire Detected");
    Firebase.setString(firebaseData, "Environment", str);
  }


}




