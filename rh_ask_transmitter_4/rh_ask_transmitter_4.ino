#include <Wire.h>
#include <LSM303.h>
#include <VirtualWire.h>

LSM303 compass;
char report[VW_MAX_MESSAGE_LEN];

void setup()
{
  Serial.begin(9600);
  vw_set_tx_pin(6);  // Porta digital 6 como TX para modulo emissor RF
  vw_setup(2000);   // Bits per sec
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void send (char *message)
{
  digitalWrite(LED_BUILTIN, HIGH);
  vw_send(message, strlen(message));
  vw_wait_tx(); // Aguarda o envio de dados
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  compass.read();

  /*snprintf(report, sizeof(report), "A: %6d %6d %6d    M: %6d %6d %6d",
    compass.a.x, compass.a.y, compass.a.z,
    compass.m.x, compass.m.y, compass.m.z);
  */

  snprintf(report, sizeof(report), "%d %d %d ",
    compass.m.x, compass.m.y, compass.m.z);

  /*
  int numero;
  numero = strlen(report);
  Serial.print("Enviado : ");
  Serial.print(report);
  Serial.print(" - Caracteres : ");
  Serial.println(numero);
  */
  send(report);
}
