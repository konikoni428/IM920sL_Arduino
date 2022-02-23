#include <SoftwareSerial.h>
#include <IM920sL.h>

SoftwareSerial IM920sLSerial(10, 9);  // RX, TX

// Create IM920 instance
IM920sL im920sl(IM920sLSerial, 0); // Serial, busyPin
// IM920sL im920sl(IM920sLSerial); // Serial, No busyPin


// Callback Function
void onIM920sLCallback(IM920sL_data_t &data){
  // handle response
  Serial.println("[RECEIVED]");
  Serial.print("DATA: ");
  Serial.println(data.data);
  Serial.print("NODE: ");
  Serial.println(data.node, HEX);
  Serial.print("RSSI: ");
  Serial.println(data.rssi);
  Serial.print("RAW DATA: ");
  Serial.println(data.raw);
}

void setup() {
  Serial.begin(19200);
  IM920sLSerial.begin(19200);
  im920sl.setCallback(onIM920sLCallback);

  while(!Serial);  // wait serial monitor
  while(!IM920sLSerial);  // wait im920sl

  // send command and receive response(string)
  String id = im920sl.sendCommand("RDID");
  Serial.println(id);

  // send command and receive response(boolean: OK -> true, other -> false)
  bool is_send = im920.sendCommandBool("TXDA 1234");
  if(is_send) {
    Serial.println("Send OK");
  } else {
    Serial.println("Send Failed");
  }
}

void loop() {
  // check uart buffer
  im920sl.run();

  delay(10);
}