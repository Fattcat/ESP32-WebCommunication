#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WebServer server(80);

String nickname = "";
String chatLog = "";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, handleRoot);
  server.on("/", HTTP_POST, handlePost);
  
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h2>Set Your Nickname:</h2>";
  html += "<form method='post'>";
  html += "Nickname: <input type='text' name='nickname'><br>";
  html += "<input type='submit' value='Set Nickname'>";
  html += "</form>";
  html += "<h2>Chat:</h2>";
  html += "<div style='border:1px solid #ccc; padding:10px; height:200px; overflow:auto;'>";
  html += chatLog;
  html += "</div></body></html>";
  
  server.send(200, "text/html", html);
}

void handlePost() {
  if (server.hasArg("nickname")) {
    nickname = server.arg("nickname");
  }

  if (server.hasArg("message")) {
    String message = "[" + nickname + "]: " + server.arg("message") + "<br>";
    chatLog += message;
  }

  handleRoot();
}
