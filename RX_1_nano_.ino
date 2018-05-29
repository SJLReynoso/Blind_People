#include <VirtualWire.h>
#include <VirtualWire_Config.h>

//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
void setup()
{
vw_set_ptt_inverted(true); // Required for DR3100
vw_set_rx_pin(8);
vw_setup(4000); // Bits per sec
pinMode(7, OUTPUT);
pinMode(6,OUTPUT);
Serial.begin(9600);

vw_rx_start(); // Start the receiver PLL running
}
void loop()
{
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

if (vw_get_message(buf, &buflen)) // Non-blocking
{
//primer emisor
if(buf[0]=='1'&&buf[1]=='1'){
Serial.println(buf[0]);
digitalWrite(7,1);
delay(500);
digitalWrite(7,0);
}
if(buf[0]=='2'&&buf[1]=='1'){
Serial.println(buf[0]);
digitalWrite(6,1);
delay(500);
digitalWrite(6,0);
}
}



}
