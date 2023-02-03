// Includes for RF receiver
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 

#define RXBUFSIZE 40

// Create Amplitude Shift Keying Object
RH_ASK rf_driver(2000, 17);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Initialize ASK Object
  rf_driver.init();
  // set up serial port for diagnostics
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  
  // Set buffer to size of expected message
  uint8_t buf[40];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  Serial.printf("%8d", millis());
  Serial.print(" : ");
  //Serial.print("About to read buffer of ");
  //Serial.print(buflen);
  //Serial.print(" bytes ... ");
  if (rf_driver.recv(buf, &buflen))
  {    
    // Message received with valid checksum
    Serial.print("Message Received: >");
    buf[buflen-1] = 0;
    Serial.print((char*)buf);
    Serial.println("<");         
  }
  else if (RXBUFSIZE != buflen)
  {
    // something received but not expected buffer size
    Serial.printf("Received %d characters as >%s<\n", buflen, (char *)buf);
  }
  else
  {
    // Nothing received
    Serial.println("Nothing received");
  }
  //Serial.print("After rx buflen was ");
  //Serial.print(buflen);
  //Serial.println(" bytes");

  delay(1000);                      // wait for a second
}
