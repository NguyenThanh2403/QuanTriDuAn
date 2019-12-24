
#include <SPI.h>
#include <Ethernet.h>
int led = 8;
int led2 = 7;
int led3 = 6;
int led4 = 5;
byte mac[] = { 0xAD, 0x4D, 0x54, 0x2F, 0xB6, 0x74 };   //physical mac address
byte ip[] = { 172,16,2,207 };                      // ip in lan (that's what you need to use in your browser. ("192.168.")
byte gateway[] = { 172, 16, 2, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(88);                             //server port     
String readString;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led, OUTPUT);digitalWrite(led,HIGH);
  pinMode(led2, OUTPUT);digitalWrite(led2,HIGH);
  pinMode(led3, OUTPUT);digitalWrite(led3,HIGH);
  pinMode(led4, OUTPUT);digitalWrite(led4,HIGH);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
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
