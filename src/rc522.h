#ifndef __RC522__H__
#define __RC522__H__

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         34           // Configurable, see typical pin layout above
#define SS_PIN          5          // Configurable, see typical pin layout above

void RC522Init();
unsigned int RC522Read();
#endif