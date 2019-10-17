/*
#########################################################################
#  File:              HC05_Conf.ino                                     #
#  Processor:         Arduino UNO, MEGA ou Teensy++ 2.0                 #
#  Language:          Wiring / C /Processing /Fritzing / Arduino IDE    #
#  Author:            Andres Felipe Gomez Maya                          #
#  Date:              13/10/2019                                        #
#  place:             Medellin, Colombia                                #
#########################################################################
  1 - 13 - BT: PIN_STATE - ARD: PIN_13
  2 - 12 - BT: PIN_RX - ARD: PIN_11=TX
  3 - 11 - BT: PIN_TX - ARD: PIN_12=RX
  4 - 10 - BT: NULL - ARD: NULL
  5 - 09 - BT: NULL - ARD: PIN_9=F_AT
  6 - 08 - BT: PIN_VCC - ARD: PIN_8=VCC
*/
#include <SoftwareSerial.h>

int pinForceAT = 9;     // pin 12 para forzar modo AT de configuración
int pinTX = 12;          // pin 11 como TX
int pinRX = 11;          // pin 10 como RX
int pinVCC_BT = 8;       // pin 9 como alimentacion 3.3V para modulo BT

SoftwareSerial BT1(pinRX, pinTX);  // Crear BT1

void setup()
{
  Serial.begin(9600);
  Serial.println("Powered by FelipheGomez.");
  Serial.println("Configurando F_AT.");
  pinMode(pinForceAT, OUTPUT);  // 
  Serial.println("Configurando VCC.");
  pinMode(pinVCC_BT, OUTPUT);  // 
  Serial.println("Activando F_AT.");
  digitalWrite(pinForceAT, HIGH);
  Serial.println("Corriente activada.");
  delay(500);
  Serial.println("Sincronizando Velocidades BT 9600x38400.");
  digitalWrite(pinVCC_BT, HIGH);

  Serial.println("  ** Test de comunicación:");
  Serial.println("  $ AT ");
  Serial.println("");
  Serial.println("** Cambiar nombre de nuestro módulo:");
  Serial.println("  $ AT+NAME=<Nombre>");
  Serial.println("");
  Serial.println("** Cambiar Código de Vinculación");
  Serial.println("  $ AT+PSWD=<\"Pin\">");
  Serial.println("");
  Serial.println("** Configurar la velocidad de comunicación: ");
  Serial.println("La velocidad por defecto es de 9600 baudios, con Stop bit =0 (1 bit de parada), y sin Paridad, para cambiar estos parámetros, se hace uso del siguiente comando AT:");
  Serial.println("  <Baud> equivale a una velocidad, los valores pueden ser: 4800, 9600, 19200, 38400, 57600, 115200, 23400, 460800, 921600 o 1382400.");
  Serial.println("  <StopBit> es el Bit de parada, puede ser 0 o 1, para 1 bit o 2 bits de parada respectivamente, Para aplicaciones comunes se trabaja con 1 bit por lo que este parámetro normalmente se lo deja en 0.");
  // Serial.println("  <Parity> Es la paridad, puede ser 0 (Sin Paridad), 1 (Paridad impar) o 2 (Paridad par). Para aplicaciones comunes no se usa paridad, por lo que se recomienda dejar este parámetro en 0.");
  // Serial.println("");
  // Serial.println("  $ AT+UART=9600,0,0");
  // Serial.println("");
  // Serial.println("** Configurar el Role: para que trabaje como Maestro o Esclavo ");
  // Serial.println("Por defecto nuestro HC-05 viene como esclavo, el Siguiente comando nos permite cambiar esto)");
  // Serial.println("  $ AT+ROLE=<Role> Ejm: AT+ROLE=0");
  // Serial.println("    0 -> Esclavo");
  // Serial.println("    1 -> Maestro");
  // Serial.println("");
  // Serial.println("** Configurar el modo de conexión (cuando se trabaja como maestro)");
  // Serial.println("Esta configuración aplica para cuando el modulo está trabajando como maestro, el modulo necesita saber si se va a conectar con un dispositivo en particular o con cualquiera que esté disponible.");
  // Serial.println("  $ AT+CMODE=<Mode>  Ejm: AT+CMODE=1");
  // Serial.println("    0 -> Conectarse a un dispositivo con la dirección especificada(Se utiliza otro comando AT para especificar esta dirección).");
  // Serial.println("    1 -> conectar el módulo a cualquier dirección disponible(aleatorio).");
  // Serial.println("");
  // Serial.println("** Especificar la dirección del dispositivo al cual nos vamos a conectar");
  // Serial.println("Esta configuración aplica cunado nuestro modulo está configurado como maestro, y a la vez el modo de conexión está en 0  (CMODE=0) el cual indica que nos vamos a conectar al dispositivo esclavo en particular. Para especificar la dirección al cual nos vamos a conectar se usa el siguiente comando AT");
  // Serial.println("  $ AT+BIND=<Address>");
  // Serial.println("    < Address > Es la dirección del dispositivo al cual nos vamos a conectar, la dirección se envía de la siguiente forma: 1234,56,ABCDEF la cual equivale a la dirección 12:34:56:AB:CD:EF");
  // Serial.println("      $ AT+BIND=E668,46,9277F2");
  // Serial.println("");
  // Serial.println("** Obtener la versión del firmware:");
  // Serial.println("  $ AT+VERSION?");
  // Serial.println("");
  // Serial.println("** Obtener la dirección de nuestro modulo bluetooth");
  // Serial.println("  $ AT+ADDR?");
  // Serial.println("");
  // Serial.println("** Resetear nuestro Modulo, después de hacer TODO salimos del MODO AT");
  // Serial.println("  $ AT+RESET");
  // Serial.println("");
  // Serial.println("** Restablecer valores por defecto.");
  // Serial.println("  $ AT+ORGL");
  // Serial.println("    *Al hacer esto todos los parámetros del módulo se restablecen, a los valores por defecto de fábrica. En algunas versiones la velocidad cambia a 38400 baudios y en otros a 9600.");
  // Serial.println("");
  Serial.println("Ingrese Comandos AT o pruebe el BT.");
  BT1.begin(38400);
}

void loop(){
  if (BT1.available()){ Serial.write(BT1.read()); } // si hay informacion disponible desde modulo
  if (Serial.available()){ BT1.write(Serial.read()); } // si hay informacion disponible desde el monitor serial
}
