// License http://tamberg.mit-license.org/

#include <SPI.h>
#include <Ethernet.h>
#include <YalerEthernetServer.h>

byte rPin = 5;
byte gPin = 3;
byte bPin = 6;

// Enter a MAC address for your controller below.
// Some Ethernet shields have a MAC address printed on a sticker
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Local EthernetServer at http://LOCAL_IP/ (check serial monitor output)
//EthernetServer server(80);

// Get a free relay domain at http://yaler.net/ to replace RELAY_DOMAIN below
// Public YalerEthernetServer accessible at http://RELAY_DOMAIN.try.yaler.net/
YalerEthernetServer server("try.yaler.net", 80, "gsiot-17g7-pgfq");

const char html[] =
  "<html><head>"
    "<script type=\"text/javascript\">"
    "var r;"
    "try {"
      "r = new XMLHttpRequest();"
    "} catch (e) {"
      "try {"
        "r = new ActiveXObject('Microsoft.XMLHTTP');"
      "} catch (e) {}"
    "}"
    "function set (c) {"
      "r.open('PUT', './gsiot-17g7-pgfq/led/' + c, false);"
      "r.send(null);"
    "}"
    "</script>"
    "<style type=\"text/css\">"
      ".b {width:112; height:112}"
      ".g {color:lightgrey}"
    "</style>"
  "</head>"
  "<body><table height=\"100%\" width=\"100%\">"
    "<tr><td align=\"center\" valign=\"middle\">"
      "<p>"
        "<input type=\"button\" class=\"b\" style=\"background-color:#ff0000\" onclick=\"set('ff0000')\"/>&nbsp;&nbsp;"
        "<input type=\"button\" class=\"b\" style=\"background-color:#00ff00\" onclick=\"set('00ff00')\"/>&nbsp;&nbsp;"
        "<input type=\"button\" class=\"b\" style=\"background-color:#0000ff\" onclick=\"set('0000ff')\"/>"
      "</p>"
      "<p>HTML served from <a href=\"\">this</a> Arduino, made accessible by <a href=\"http://www.yaler.org/\">Yaler</a>.</p>"
    "</td></tr>"
  "</table></body></html>";

void setColor (byte r, byte g, byte b) {
  Serial.print("Setting LED color (");
  Serial.print(r); Serial.print(",");
  Serial.print(g); Serial.print(",");
  Serial.print(b); Serial.println(")");
  // SparkFun LED
  analogWrite(rPin, r);
  analogWrite(gPin, g); 
  analogWrite(bPin, b);
  // Adafruit LED
  //analogWrite(rPin, 255 - r);
  //analogWrite(gPin, 255 - g); 
  //analogWrite(bPin, 255 - b);  
}

void setup() {
  Serial.begin(9600);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  setColor(255, 255, 255);
  Serial.println("Aquiring IP address...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP failed.");
  } else {
    Serial.println(Ethernet.localIP());
    server.begin();
  }
  setColor(0, 0, 0);
}

byte byteFromHexChar (char ch) {
  byte result;
  if ((ch >= '0') && (ch <= '9')) {
    result = ch - '0';
  } else if ((ch >= 'a') && (ch <= 'f')) {
    result = 10 + (ch - 'a');
  } else if ((ch >= 'A') && (ch <= 'F')) {
    result = 10 + (ch - 'A');
  } else {
    result = 0;
  }
  return result;
}

void sendPutResponse(EthernetClient client) {
  Serial.println("Sending PUT response...");
  client.print("HTTP/1.1 200 OK\r\n");
  client.print("Connection: close\r\n");
  client.print("Content-Length: 0\r\n");
  client.print("\r\n");
}

void sendGetResponse(EthernetClient client) {
  Serial.println("Sending GET response...");
  client.print("HTTP/1.1 200 OK\r\n");
  client.print("Connection: close\r\n");
  client.print("Content-Type: text/html\r\n");
  client.print("Content-Length: ");
  client.print(sizeof(html) - 1);
  client.print("\r\n");
  client.print("\r\n");
  client.print(html);
}

void loop() {
  Serial.println("Accepting clients...");
  EthernetClient client = server.available();
  if (client && client.connected()) {
    Serial.println("Receiving request...");
    int ch = client.read(); // read first char of incoming request
    if (ch == 'P') {
      Serial.print("PUT /led/");
      client.find("/led/");
      byte led[] = {0, 0, 0};
      for (int i = 0; i < 6; i++) { // parse hex color, e.g. ff0000
        ch = client.read();
        Serial.print((char) ch);
        byte b = byteFromHexChar(ch);
        led[i / 2] = led[i / 2] * 16 * (i % 2) + b;
      }
      Serial.println();
      setColor(led[0], led[1], led[2]);
      client.find("\r\n\r\n"); // consume request headers
      sendPutResponse(client);
    } else {
      Serial.println("GET"); // ignore request path
      client.find("\r\n\r\n"); // consume request headers
      sendGetResponse(client);
    }
    delay(1); // give the Web browser time to receive the data
    client.stop();
  }
}
