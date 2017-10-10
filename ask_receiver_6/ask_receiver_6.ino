#include <SD.h>
#include <VirtualWire.h>
#include <SoftwareSerial.h>

#define RxD 9    // Connect the HC-05 TX
#define TxD 8    // Connect the HC-05 RX via voltage divider
#define RxRF 5   // Connect the RF receiver TX
#define Arquivo "IMCU001.log"        // Log data filename

SoftwareSerial mSerial(RxD,TxD);
File arquivoTXT;
char string[50];
String pid;
byte counter = 0;

void logData(uint8_t* message, uint8_t msgLength) {
  //Serial.write(message, msgLength);
  //Serial.println();
  
  arquivoTXT.write(message, msgLength);
  arquivoTXT.println();
  
  if (counter == 255) {
    arquivoTXT.flush();
    Serial.println("Flush");
  }
  
  counter++;
}

void getReceiver(uint8_t* message, uint8_t* msgLength){
  //uint8_t message[VW_MAX_MESSAGE_LEN];    
  //uint8_t msgLength = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(message, msgLength)){ // Non-blocking
    logData(message,msgLength);
    Serial.print(".");
  }
}

void getOBD() {
  char c = ' ';
  *string = ' ';
  while (mSerial.available()) {
    c = mSerial.read();
    strcat(*string,c);
    Serial.write(c);
    Serial.println();
  }
  Serial.println("result " + *string);
  //logData(string.toCharArray(),string.length());
}

void sendCod(char cod) {
  // Read from serial monitor and send to HC-05
  if (cod=='1') //RPM
    pid = "010C";
  else if(cod=='2') // Velocidade
    pid = "010D";
  else if(cod=='3') // Pos Acelerador
    pid = "0111";
  else 
    pid = "";
    
  if(pid!=""){
    Serial.println(pid);
    mSerial.println(pid);
  }
  
}

void setup(void) {
  Serial.begin(38400);
  Serial.println("commencing receiver init");

  /* Configura module RF receiver */
  vw_set_rx_pin(RxRF);        // Define o pino para entrada de de RF receiver
  vw_setup(2000);
  vw_rx_start();
  
  Serial.print("Commencing SD..."); 
  
  /* Configura SD */
  SD.begin(10);               // pino conectado ao CS do modulo SD
  arquivoTXT = SD.open(Arquivo, FILE_WRITE);
  if (arquivoTXT) {
    Serial.println("OK");
    arquivoTXT.println("******************");
    // arquivoTXT.close();
  } else {
    Serial.println("Error");
  }

  Serial.print("Commencing HC-05..."); 

  /* Configura a conexao com HC-05 */
  mSerial.begin(38400);

  pinMode(RxD,INPUT);
  pinMode(TxD,OUTPUT);
}

void loop(void) {
  uint8_t rfMessage[VW_MAX_MESSAGE_LEN];    
  uint8_t rfMsgLen = VW_MAX_MESSAGE_LEN;
  
  getOBD();
  getReceiver(rfMessage, &rfMsgLen);
  
  sendCod('1');
  getOBD();
  
  sendCod('2');
  getOBD();

  sendCod('3');
  getOBD();
}
