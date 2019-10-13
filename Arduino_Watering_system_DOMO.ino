/*
#####################################################################################
#  File:               Arduino_Watering_system_DOMO.ino                                             
#  Processor:          Arduino UNO, MEGA ou Teensy++ 2.0
#  Language:           Wiring / C /Processing /Fritzing / Arduino IDE          
#  Objectives:         Watering System - Irrigation Modular
#     
#   Author:            Andres Felipe Gomez Maya
#   Date:              13/10/2019
#   place:             Medellin, Colombia
#         
##################################################################################### 
*/

#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales

int pinLedSingle = 12;  // pin 13 para led simple de luces
int pinForceAT = 8;     // pin 8 para forzar modo AT de configuración
int pinVCC_BT = 9;      // pin 9 como alimentacion 3.3V para modulo BT
int pinRX = 10;         // pin 10 como RX
int pinTX = 11;         // pin 11 como TX

SoftwareSerial miBT(pinRX, pinTX);  // pin 10 como RX, pin 11 como TX
// system status
const char *system_status_list[] =
{
  "Power by FelipheGomez",
  "Encendido",
  "Stand by",
  "Levantando el modulo HC-06",
  "Listo para recibir desde BT",
  "Configurando Luces",
  "Suelo seco      ",
  "Suelo húmedo    ",
  "Suelo empapado  ",
  "Bomba agua ENC  ",
};
const String system_status;
int power_status = 0;
int state_ledSingle = 0;
int flag = 0;

void setup(){
  setStatus(0);
  pinMode(pinForceAT, OUTPUT);        // Al poner en HIGH forzaremos el modo AT
  pinMode(pinVCC_BT, OUTPUT);         // cuando se alimente de aqui
  // digitalWrite(pinVCC_BT, HIGH);   //  Forzar AT para configuracion BT
  delay(500);                         // Espera antes de encender el modulo
  Serial.begin(9600);                 // comunicacion de monitor serial a 9600 bps
  setStatus(3);
  digitalWrite(pinForceAT, HIGH);     // Enciende el modulo
  setStatus(4);
  miBT.begin(38400);                  // comunicacion serie entre Arduino y el modulo a 38400 bps

  setStatus(5);
  pinMode(pinLedSingle, OUTPUT);      // Establece como salida para el LED simple
  digitalWrite(pinLedSingle, LOW);    // Lo Apaga por default

  setStatus(2);
}

void setStatus(int statusInt){
  if(statusInt > 0){
    system_status = system_status_list[statusInt];
    Serial.println("Nuevo estado: " + system_status); // escribe en el monitor el nuevo estado
    delay(500);
  }
}

void loop(){
  // si hay informacion disponible desde modulo
  if (miBT.available()){ recibeInfo(miBT.readString()); }
  // Serial.write(miBT.read()); // lee Bluetooth y envia a monitor serial de Arduino
  // si hay informacion disponible desde el monitor serial
  if (Serial.available()){ recibeInfo(Serial.readString()); }
  flag=0;
  
  // miBT.write(Serial.read());   // lee monitor serial y envia a Bluetooth
  if(power_status == 1){
    // Serial.println("Arrancando Ciclo.");
  } else {
    // Serial.println("Ciclo Detenido.");
  }

  if(state_ledSingle == 3){ ledParty(); } 
}

void recibeInfo(String infoRecibe){
  if(infoRecibe == "none"){} else {
      mostrarDatos("Comando recibido: " + infoRecibe);
      delay(500);
      if(infoRecibe.indexOf("device_status") >= 0){
        mostrarDatos(system_status);
      } else if(infoRecibe.indexOf("power_on") >= 0){
        power_status = 1;
        setStatus(1);
      } else if(infoRecibe.indexOf("power_off") >= 0){
        power_status = 0;
        setStatus(2);
      } else if(infoRecibe.indexOf("led_on") >= 0){
        state_ledSingle = 1;
        digitalWrite(pinLedSingle, HIGH);
      } else if(infoRecibe.indexOf("led_off") >= 0){
        state_ledSingle = 0;
        digitalWrite(pinLedSingle, LOW);
      } else if(infoRecibe.indexOf("led_status") >= 0){
        mostrarDatos("Estado: " + state_ledSingle);
      }else if(infoRecibe.indexOf("led_party_on") >= 0){
        state_ledSingle = 3;
      }
  }
}

void ledParty(){
  if(state_ledSingle == 3){
    digitalWrite(pinLedSingle, HIGH);
    delay(250);
    digitalWrite(pinLedSingle, LOW);
    delay(250);
  }
}

void mostrarDatos(String message){
    Serial.println(message);
    miBT.println(message);
}
