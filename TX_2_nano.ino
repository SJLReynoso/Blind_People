#include <VirtualWire.h>
#include <VirtualWire_Config.h>

//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
char *controller;
const int pinecho = 2;
const int pintrigger = 3;
unsigned int tiempo, distancia;
 int tones[ ] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440,466, 494};
void setup() {
Serial.begin(9600);
pinMode(pinecho, INPUT);
pinMode(pintrigger, OUTPUT);
pinMode(7, OUTPUT);
vw_set_ptt_inverted(true); //
vw_set_tx_pin(8);
vw_setup(4000);// speed of data transfer Kbps
}

void loop(){
// ENVIAR PULSO DE DISPARO EN EL PIN "TRIGGER"
  digitalWrite(pintrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger, HIGH);
  // EL PULSO DURA AL MENOS 10 uS EN ESTADO ALTO
  delayMicroseconds(10);
  digitalWrite(pintrigger, LOW);

  // MEDIR EL TIEMPO EN ESTADO ALTO DEL PIN "ECHO" EL PULSO ES PROPORCIONAL A LA DISTANCIA MEDIDA
  tiempo = pulseIn(pinecho, HIGH);

  // LA VELOCIDAD DEL SONIDO ES DE 340 M/S O 29 MICROSEGUNDOS POR CENTIMETRO
  // DIVIDIMOS EL TIEMPO DEL PULSO ENTRE 58, TIEMPO QUE TARDA RECORRER IDA Y VUELTA UN CENTIMETRO LA ONDA SONORA
  distancia = tiempo / 58;

  // ENVIAR EL RESULTADO AL MONITOR SERIAL
  Serial.print(distancia);
  Serial.println(" cm");
  //delay(100);
if (distancia <= 50) {
controller="21";
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
/*
digitalWrite(7,1);
delay(500);
digitalWrite(7,0);*/
tone(7, tones[277]);
delay(50);
noTone(7);
}
/*
else {
controller="20" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
digitalWrite(7,0);
delay(2000);
}*/

}
