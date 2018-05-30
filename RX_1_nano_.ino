#include <VirtualWire.h>
#include <VirtualWire_Config.h>

//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
const int pinecho = 2;
const int pintrigger = 3;
unsigned int tiempo, distancia;

void setup()
{
vw_set_ptt_inverted(true); // Required for DR3100
vw_set_rx_pin(8);
vw_setup(4000); // Bits per sec
//sensor de distancia del cinturon
pinMode(pinecho, INPUT);
pinMode(pintrigger, OUTPUT);

//pin del sensor derecho
pinMode(7, OUTPUT);
//pin del sensor izquierdo
pinMode(6,OUTPUT);
//pin del sensor del cinturon
pinMode(5,OUTPUT);
Serial.begin(9600);

vw_rx_start(); // Start the receiver PLL running
}
void loop()
{
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

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

// recepción de los sensores izquierdo y derecho
if (vw_get_message(buf, &buflen)){
//primer emisor
if(buf[0]=='1'&&buf[1]=='1'){
//Serial.println(buf[0]);
digitalWrite(7,1);
delay(500);
digitalWrite(7,0);
}
if(buf[0]=='2'&&buf[1]=='1'){
//Serial.println(buf[0]);
digitalWrite(6,1);
delay(500);
digitalWrite(6,0);
}
}// recepción de los sensores izquierdo y derecho

// sensor del cinturón
else if(distancia <= 50){
  digitalWrite(5,1);
  delay(500);
  digitalWrite(5,0);
}//
// sensor del cinturón


}
