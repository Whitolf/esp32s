#ifndef __SHOWQRCODE__H__
#define __SHOWQRCODE__H__

#include <Arduino.h>
#include "U8g2lib.h"
#include "qrcode.h"
#include <SPI.h>

//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 10, /* dc=*/ 26, /* reset=*/ 25);

void u8g2Init();

void showqrcode(char *qrdata,float temp );
void showstr(char *strdata, uint8_t x, uint8_t y);
void cleandisplay();

#endif