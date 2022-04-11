#include <SoftwareSerial.h>  //Se incluye la librería de "SoftwareSerial"
SoftwareSerial sim900(7, 8); // Se define los pines para la comunicación serial
void setup()
{

  sim900.begin(19200); // Configuración de la velocidad en baudios del módulo SIM900
  Serial.begin(19200); // Configuración de la velocidad en baudios del monitor serie (Arduino)
}

void loop()
{
  if (Serial.available() > 0)
  {
    switch (Serial.read())
    {
    case 's': // Si hay algo en el monitor serie, si es una letra "s" se ejecutara los comando AT que se definen en la funcion "envio_sms"
      envio_sms();
      break;
    case 'c': // Pero si una letra "c" se ejecutara los comando AT que se definen en la función "hacer_llamada"
      hacer_llamada();
      break;
    case 'i':
      intesidad_senhal();
      break;
    }
  }

  if (sim900.available() > 0)
    Serial.write(sim900.read()); // Imprime los datos recopilados del puerto serie
}

void envio_sms()
{
  Serial.println("Enviado sms...");
  sim900.print("AT+CMGF=1\r"); // Establecer en modo envió de sms
  delay(100);
  /* Se le asigna el numero, debes cambiar la clave de acuerdo al país si eres de México
  solo agrega el numero al que enviaras el sms */
  sim900.print("AT+CMGS=\"+595983742895\"\r");
  delay(200);
  sim900.print("Mensaje de prueba"); // Contenido que llevara el sms
  sim900.print("\r");
  delay(500);
  sim900.print((char)26);
  delay(100);
  sim900.println();
  Serial.println("SMS Enviado...");
  delay(500);
}
void intesidad_senhal()
{
  sim900.println("AT+CSQ"); // CANTIDAD DE SEÑAL RECIBIDA
  delay(1000);
}
void hacer_llamada()
{
  /* Se marca al numero, debes cambiar la clave de acuerdo al país si eres de México
  solo agrega el numero al que llamaras */
  sim900.println("ATD+52155.........;");
  delay(100);
  sim900.println();
}