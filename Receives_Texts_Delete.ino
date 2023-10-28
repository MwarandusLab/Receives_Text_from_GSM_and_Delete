#include <SoftwareSerial.h>

SoftwareSerial sim800l(5, 4); // RX, TX pins for SIM800L module

int relayPin = 6; // pin connected to the relay

void setup() {
  Serial.begin(9600); // initialize the serial monitor
  sim800l.begin(9600); // initialize the SIM800L module
  digitalWrite(relayPin, HIGH);
  // configure SIM800L to receive text messages
  sim800l.println("AT+CMGF=1"); // set SMS text mode
  delay(100);
  sim800l.println("AT+CNMI=1,2,0,0,0"); // set SIM800L to notify when new SMS is received
  delay(100);

  pinMode(relayPin, OUTPUT); // set the relay pin as an output
}

void loop() {
  if (sim800l.available()) { // check if there is a message available
    String message = sim800l.readString(); // read the message
    Serial.println("Received message: " + message); // print the message to the serial monitor
    if (message.indexOf("ON") != -1) { // if the message contains "ON"
      digitalWrite(relayPin, HIGH); // turn on the relay
      Serial.println("Relay turned ON.");
    } else if (message.indexOf("OFF") != -1) { // if the message contains "OFF"
      digitalWrite(relayPin, LOW); // turn off the relay
      Serial.println("Relay turned OFF.");
    }
    delay(1000); // wait for 1 second before deleting the message
    sim800l.println("AT+CMGD=1,4"); // delete all messages from the SIM card
  }
  delay(1000); // wait for 1 second before checking for new messages
}
