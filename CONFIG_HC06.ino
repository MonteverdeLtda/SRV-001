/*
#########################################################
#  File:              CONFIG_HC06.ino                                             
#  Processor:         Arduino UNO, MEGA ou Teensy++ 2.0
#  Language:          Wiring / C /Processing /Fritzing / Arduino IDE          
#  Objectives:        Watering System - Irrigation Modular
#  Author:            Andres Felipe Gomez Maya
#  Date:              13/10/2019
#  Place:             Medellin, Colombia
#########################################################
*/
#include <Wire.h>
#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales

int pinForceAT = 11;    // pin 11 para forzar modo AT de configuración
int pinTX = 10;         // pin 10 como TX
int pinRX = 9;          // pin 9 como RX
int pinVCC_BT = 8;      // pin 8 como alimentacion 3.3V para modulo BT1
SoftwareSerial BT1(pinRX, pinTX);  // Crear BT1 - pin 10 como RX, pin 11 como TX

// system status
const char *system_status_list[] =
{
  "Developer by FelipheGomez",
  "Levantando el modulo HC-06",
  "Listo para recibir desde AT",
  "",
};
const String system_status;

void setup(){
  setStatus(0);
  setStatus(1);
  pinMode(pinForceAT, OUTPUT);        // Al poner/2 en HIGH forzaremos el modo AT
  pinMode(pinVCC_BT, OUTPUT);         // cuando se alimente de aqui
  digitalWrite(pinForceAT, HIGH);   //  Forzar AT para configuracion BT - CAMBIAR POR PULSADOR
  delay(500);                          // Espera antes de encender el modulo
  Wire.begin(); // Se inicial la interfaz I2c
  Serial.begin(9600);                 // comunicacion de monitor serial a 9600 bps
  digitalWrite(pinVCC_BT, HIGH);     // Enciende el modulo BT
  BT1.begin(38400);                  // comunicacion serie entre Arduino y el modulo a 38400 bps
  setStatus(2);
}

void setStatus(int statusInt){
  if(statusInt > 0){
    system_status = system_status_list[statusInt];
    mostrarDatos("*z" + system_status + "*"); // escribe en el monitor el nuevo estado
  }
}

void loop(){
  if (BT1.available()){ recibeInfo(BT1.readString()); } // si hay informacion disponible desde modulo
  if (Serial.available()){ recibeInfo(Serial.readString()); } // si hay informacion disponible desde el monitor serial
}

void recibeInfo(String infoRecibe){
  if(infoRecibe == "none"){} else {
      mostrarDatos("Recibido: ");
      mostrarDatos(infoRecibe);
  }
}

void mostrarDatos(String message){
    Serial.println(message);
    BT1.println(message);
}
