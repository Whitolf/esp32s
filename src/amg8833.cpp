#include "amg8833.h"
Adafruit_AMG88xx amg;
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int AMG8833Init(){

    bool status;
    int ret;
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("wiring!");
        ret = 0;
        while (1);
    }
    ret = 1;
    Serial.println("-- Pixels Test --");
    Serial.println();
    delay(100); // let sensor boot up
    return ret;
}

float AMG8833Read(){
    amg.readPixels(pixels);
    /**
     * Serial.print("[");
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      Serial.print(pixels[i-1]);
      Serial.print(", ");
      if( i%8 == 0 ) Serial.println();
    }
    Serial.println("]");
    Serial.println();**/

    //delay a second
    
    float curMax, curMin;
    curMax = pixels[0];
    curMin = pixels[0];

    
        for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++)
        {
            if (curMax<=pixels[i-1])
            {
                curMax = pixels[i - 1];
            }
            if (curMin>=pixels[i-1])
            {
                curMin = pixels[i - 1];
            }
            
        }
        
      char temp[7];
      memset(temp, 0, sizeof(temp));
      sprintf(temp, "%0.2f", curMax);
      //Serial.println(temp);
      memset(temp, 0, sizeof(temp));
      sprintf(temp, "%0.2f", curMin);
      //Serial.println(temp);
      delay(50);
      return curMax;
}