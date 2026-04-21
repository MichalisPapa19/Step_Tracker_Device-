#include <18F57Q43.h>

#device  ADC=10

#FUSES   NOWDT , NOBROWNOUT               //No Watch Dog Timer

#FUSES RSTOSC_HFINTRC_64MHZ

#use delay(internal=32MHz)

#use i2c(master, scl=PIN_b1, sda=PIN_b2 ,FAST)   // i2c for oled lcd
 
#use rs232(uart3, baud=9600,xmit=PIN_a3,rcv=PIN_a4,bits=8, errors )  // WORK EXTERNAL COM3







