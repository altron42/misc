#include <SoftwareSerial.h>

#define RxD 9 // Conect the HC-05 TX
#define TxD 8 // Conect the HC-05 RX via voltage divider

SoftwareSerial mSerial(RxD,TxD);

char c = ' ';

void setup() {
  Serial.begin(38400); //debug purpose
  Serial.println("Commencing sketch init");
  mSerial.begin(38400);
  Serial.println("Serial started at 38400 baudrate");
  pinMode(RxD,INPUT);
  pinMode(TxD,OUTPUT);
}

void loop() {
  // Read from HC-05 and send to serial monitor
  if (mSerial.available()) {
    c = mSerial.read();
    Serial.write(c);
  }

  // Read from serial monitor and send to HC-05
  if (Serial.available()) {
    c = Serial.read();

    Serial.write(c);
    mSerial.write(c);
  }
}
