
#include <SPI.h>
#include <Ethernet.h>
int led = 8;
int led2 = 7;
int led3 = 6;
int led4 = 5;

#define LED_PIN 13
 
#define CMD_SEND_BEGIN  "AT+CIPSEND=0"
#define CMD_SEND_END    "AT+CIPCLOSE=0"
 
#define E360_PROTOCOL_HTTP     80
#define E360_PROTOCOL_HTTPS    443
#define E360_PROTOCOL_FTP      21
#define E360_PROTOCOL_CURRENT  E360_PROTOCOL_HTTP
 
#define E360_CHAR_CR     0x0D
#define E360_CHAR_LF     0x0A
 
#define E360_STRING_EMPTY  ""
 
#define E360_DELAY_SEED  1000
#define E360_DELAY_1X    (1*E360_DELAY_SEED)
#define E360_DELAY_2X    (2*E360_DELAY_SEED)
#define E360_DELAY_3X    (3*E360_DELAY_SEED)
#define E360_DELAY_4X    (4*E360_DELAY_SEED)
#define E360_DELAY_0X    (5*E360_DELAY_SEED)

void setup() {
  delay(E360_DELAY_0X);
  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT); 
  digitalWrite(LED_PIN, LOW);
  
  initESP8266();
}


void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>Trang Chu</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>PROJECT2 - DIEU KHIEN THIET BI</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Four Relay </H2>");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">Bat RELAY 1</a>");
           client.println("<a href=\"/?button1off\"\">Tat RELAY 1</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           client.println("<a href=\"/?button2on\"\">Bat RELAY 2</a>");
           client.println("<a href=\"/?button2off\"\">Tat RELAY 2</a><br />"); 
           client.println("<br />"); 

           client.println("<br />"); 
           client.println("<a href=\"/?button3on\"\">Bat RELAY 3</a>");
           client.println("<a href=\"/?button3off\"\">Tat RELAY 3</a><br />"); 
           client.println("<br />"); 

           client.println("<br />"); 
           client.println("<a href=\"/?button4on\"\">Bat RELAY 4</a>");
           client.println("<a href=\"/?button4off\"\">Tat RELAY 4</a><br />"); 
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons
           if (readString.indexOf("?button1on") >0){
               digitalWrite(led, LOW);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(led, HIGH);
           }

           if (readString.indexOf("?button2on") >0){
               digitalWrite(led2, LOW);
           }
           if (readString.indexOf("?button2off") >0){
               digitalWrite(led2, HIGH);
           }

           if (readString.indexOf("?button3on") >0){
               digitalWrite(led3, LOW);
           }
           if (readString.indexOf("?button3off") >0){
               digitalWrite(led3, HIGH);
           }

           if (readString.indexOf("?button4on") >0){
               digitalWrite(led4, LOW);
           }
           if (readString.indexOf("?button4off") >0){
               digitalWrite(led4, HIGH);
           }

            readString="";  
         }
       }
    }
}
}

void initESP8266()
{
  deliverMessage("AT+RST", E360_DELAY_2X);
  deliverMessage("AT+CWMODE=2", E360_DELAY_3X);
  deliverMessage("AT+CWSAP=\"TuHocArduino\",\"123456789\",1,4", E360_DELAY_3X);
  deliverMessage("AT+CIFSR", E360_DELAY_1X);
  deliverMessage("AT+CIPMUX=1", E360_DELAY_1X); // để cho phép các kết nối TCP
  deliverMessage(String("AT+CIPSERVER=1,") + E360_PROTOCOL_CURRENT, E360_DELAY_1X);  //để tạo 1 TCP server
}

void deliverMessage(const String& msg, int dt)
{
  Serial.println(msg);
  delay(dt);

}
