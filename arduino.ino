// Created By: Mads Lind

#include <SPI.h>
#include <Ethernet.h>

////////////////////////////
// Initial State Streamer //
////////////////////////////
 
// Data destination
// https can't be handled by the ESP8266, thus "insecure"
#define ISDestURL "insecure-groker.initialstate.com"
// Bucket key (hidden reference to your bucket that allows appending):
#define bucketKey "BUCKET-KEY"
// Bucket name (name your data will be associated with in Initial State):
#define bucketName "Temperatur logger"
// Access key (the one you find in your account settings):
#define accessKey "ACCESS-KEY"
// How many signals are in your stream? You can have as few or as many as you want
const int NUM_SIGNALS = 1;
// What are the names of your signals (i.e. "Temperature", "Humidity", etc.)
String signalName[NUM_SIGNALS] = {"Signal 1"};
// This array is to store our signal data later
String signalData[NUM_SIGNALS];

/////////////
// Signals //
////////////

int inputPin = 2;        // choose the input pin (for PIR sensor)
int pirState = LOW;      // we start, assuming no motion detected
int val = 0;             // variable for reading the pin status
 
//////////////////////
// Network Settings //
/////////////////////

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// for manual configuration:
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(8, 8, 8, 8);

// initialize the library instance:
EthernetClient client;

void setup() {
   
  pinMode(inputPin, INPUT);     // declare sensor as input

  // start serial port:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
  // print the Ethernet board/shield's IP address:
  Serial.print("Min ip adresse er: ");
  Serial.println(Ethernet.localIP());
}
void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  
 val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    if (pirState == LOW) {
      
      // we have just turned on
      Serial.println("Motion detected!");

       // Gather Data
      // Read from a port for input or output or generate your own values/messages
      signalData[0] = String(1);

      // The postData() function streams our events
       while(!postData());   

      // Wait for 1 seconds before collecting and sending the next batch
      delay(1000);
  
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

// this method makes a HTTP connection to the server and sends the signals measured:
bool postData() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(ISDestURL, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    // Build HTTP request.
    // Build HTTP request.

  for (int i=0; i<NUM_SIGNALS; i++){
    String toSend = "POST /api/events HTTP/1.1\r\n";
    toSend += "Host:";
    toSend += ISDestURL;
    toSend += "\r\n" ;
    toSend += "Content-Type: application/json\r\n";
    toSend += "User-Agent: Arduino\r\n";
    toSend += "Accept-Version: ~0\r\n";
    toSend += "X-IS-AccessKey:  " accessKey "\r\n";
    toSend += "X-IS-BucketKey:  " bucketKey "\r\n";
    
    String payload = "[{\"key\": \"" + signalName[i] + "\", "; 
    payload +="\"value\": \"" + signalData[i] + "\"}]\r\n";
    
    toSend += "Content-Length: "+String(payload.length())+"\r\n";
    toSend += "\r\n";
    toSend += payload;
 
    Serial.println(toSend);
    client.println(toSend);
   }
  return true;
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    return false;
  }
}
