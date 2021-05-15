#include "showqrcode.h"


U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 35, /* dc=*/ 26, /* reset=*/ 25);	// Arduboy (Production, Kickstarter Edition)
//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 35, /* dc=*/ 26, /* reset=*/ 25);
typedef u8g2_uint_t u8g_uint_t;
void u8g2Init(){
  u8g2.setBusClock(8000000);
  u8g2.begin();
  u8g2.enableUTF8Print();		// enable UTF8 support for the Arduino print() function
  u8g2.setFont(u8g2_font_unifont_t_chinese2);  // use chinese2 for all the glyphs of "你好世界"
  //u8g2.setFont(u8g2_font_b10_t_japanese1);  // all the glyphs of "こんにちは世界" are already included in japanese1: Lerning Level 1-6
  u8g2.setFontDirection(0);

}

void showqrcode(char *qrdata,float temp){
  
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];

  qrcode_initText(&qrcode, qrcodeData, 3 , ECC_LOW, qrdata);

  u8g2.clearBuffer();
  delay(50);
  u8g2.sendBuffer();
  delay(50);

  // start draw
  u8g2.firstPage();
  do {
    // get the draw starting point,128 and 64 is screen size
    uint8_t x0 = -35+(128 - qrcode.size * 2) / 2;
    uint8_t y0 = (64 - qrcode.size * 2) / 2;
    
    // get QR code pixels in a loop
    for (uint8_t y = 0; y < qrcode.size; y++) {
      for (uint8_t x = 0; x < qrcode.size; x++) {
        // Check this point is black or white
        if (qrcode_getModule(&qrcode, x, y)) {
          u8g2.setColorIndex(1);
        } else {
          u8g2.setColorIndex(0);
        }
        // Double the QR code pixels
        u8g2.drawPixel(x0 + x * 2, y0 + y * 2);
        u8g2.drawPixel(x0 + 1 + x * 2, y0 + y * 2);
        u8g2.drawPixel(x0 + x * 2, y0  + 1 + y * 2);
        u8g2.drawPixel(x0 + 1 + x * 2, y0 + 1 + y * 2);
      }
    }
    u8g2.setColorIndex(1);
    u8g2.setCursor(128-48-6,16);
    u8g2.print("请扫码");
    delay(50);
    u8g2.setCursor(128-48-6,36);
    u8g2.print(temp);
    delay(50);


  } while ( u8g2.nextPage() );

}

void showstr(char *strdata,uint8_t x,uint8_t y)
{
    u8g2.clearBuffer();
    delay(50);
    u8g2.sendBuffer();
    delay(50);
    u8g2.firstPage();
    do {
    u8g2.setColorIndex(1);
    delay(50);
    u8g2.setCursor(x,y);
    u8g2.print(strdata);
  } while ( u8g2.nextPage() );
}
