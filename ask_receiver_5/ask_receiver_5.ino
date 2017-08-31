#include <SD.h>
#include <VirtualWire.h>

#define Arquivo "imculog0.txt"

File arquivoTXT;

int gyroX, gyroY, gyroZ;
byte counter = 0;

void getGyro(){
  uint8_t message[VW_MAX_MESSAGE_LEN];    
  uint8_t msgLength = VW_MAX_MESSAGE_LEN; 
  if (vw_get_message(message, &msgLength)){ // Non-blocking
    // digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(".");
    //Serial.write(message, msgLength);
    //Serial.println();
    //sscanf (message,"%d %d %d",&gyroX,&gyroY,&gyroZ);
    arquivoTXT.write(message, msgLength);
    arquivoTXT.println();
    if (counter == 255) {
      arquivoTXT.flush();
      Serial.println("Flush");
    }
    // digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup(void) {
  Serial.begin(9600);
  Serial.println("commencing receiver init");
  vw_set_rx_pin(5);           // Define o pino 5 do Arduino como entrada
  vw_setup(2000);             // Bits por segundo
  vw_rx_start();              // Inicializa o receptor

  // pino conectado ao CS do modulo
  SD.begin(10);
  Serial.print("Commencing SD..."); 
  arquivoTXT = SD.open(Arquivo, FILE_WRITE);
  if (arquivoTXT) {
    Serial.println("OK");
    arquivoTXT.println("Teste de arquivos TXT em SD no Arduino");
    arquivoTXT.print("Micael Pimentel - ");
    arquivoTXT.println(Arquivo);
    arquivoTXT.println();
    // arquivoTXT.close();
  } else {
    Serial.println("Error");
  }
}

void loop(void) {
  getGyro();
  counter++;
}
