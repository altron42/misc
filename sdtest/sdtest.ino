#include <SD.h>

File arquivoTXT;

#define LED_SINAL 13
#define Arquivo "Arquivo%20de%20teste.txt"

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_SINAL, OUTPUT);
  // para debugging
  Serial.begin(9600);

  // pino conectado ao CS do modulo
  SD.begin(10);
  Serial.print("Commencing SD...");
  digitalWrite(LED_BUILTIN, HIGH);
  arquivoTXT = SD.open(Arquivo, FILE_WRITE);
  if (arquivoTXT) {
    arquivoTXT.println("Teste de arquivos TXT em SD no Arduino");
    arquivoTXT.print("Micael Pimentel - ");
    arquivoTXT.println(Arquivo);
    arquivoTXT.close();
    Serial.println("OK");
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    Serial.println("Error");
    piscar();
  }
  
}

// the loop function runs over and over again forever
void loop() {
  lerArquivo(Arquivo);
  delay(2000);
}

void lerArquivo(String filename) {
  arquivoTXT = SD.open(filename);
  if (arquivoTXT) {
    while (arquivoTXT.available()) {
      Serial.write(arquivoTXT.read());
    }
    arquivoTXT.close();
  } else {
    Serial.println("Error ao abrir arquivo texto.txt");
  }
}

void piscar() {
  while(true) {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN,LOW);
    delay(500);
  }
}

