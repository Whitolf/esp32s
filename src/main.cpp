#include <Arduino.h>
#include <HardwareSerial.h>
#include "amg8833.h"
#include "rc522.h"
#include <atsend.h>
#include <Ultrasonic.h>
#include "U8g2lib.h"
#include "qrcode.h"
#include <SPI.h>
#include "showqrcode.h"

HardwareSerial MySerial(2);




int AT_Ready = 1;
int buzzer=34;//设置控制蜂鸣器的数字IO脚

Ultrasonic ultrasonic(32, 33);
int distance;
int showwait = 0;
unsigned long int waittime;

void setup() {
  // put your setup code here, to run once:uj8
  delay(500);
  u8g2Init();
  AT_Init();
  Serial.begin(115200);
  delay(100);
  MySerial.begin(115200,SERIAL_8N1,17,16);
  MySerial.setRxBufferSize(2);
  AMG8833Init();
  //pinMode(buzzer,OUTPUT);
  delay(100);
  showstr("wait N58",26,38);
  delay(3000);

   while (1)
  {
    char ready[15];
    for(int i = 0 ; N58available() > 0 && i<15 ; i++) {
      ready[i] = N58read();
      
    }
    if(strstr(ready,"PBREADY")){
      Serial.println("N85 Ready");
      break;
    }else{
      Serial.println("Wait N85 Ready");
    }
    delay(500);
  }
  N58print("AT\r\n");
  Serial.println(AT_send_cmd("AT", 100,"OK"));
  delay(50);
  Serial.println(AT_send_cmd("AT", 100,"OK"));
  delay(50);
  showstr("Found N58",24,38);
  //Serial.println(AT_send_cmd("AT+NETAPN=\"cmnet\",\"\",\"\"", 100,"OK"));
  delay(3000);
  delay(3000);
  delay(3000);
  delay(3000);
  if(
    (AT_send_cmd("AT+XIIC=1", 1000,"OK"))&&
    (AT_send_cmd("AT+HTTPPARA=url,http://81.70.153.180/check.php/?ready=1", 50,"OK"))&&
    (AT_send_cmd("AT+HTTPPARA=port,80", 50,"OK"))&&
    (AT_send_cmd("AT+HTTPSETUP", 3000,"OK"))&&
    (AT_send_cmd("AT+HTTPACTION=0", 3000,"serverready"))
  ){
    showstr("N58 ready",26,38);
    delay(2000);
  }


  

  
}

void loop() {
  
  
  // put your main code here, to run repeatedly:
  
  
  char sendbuff[150];
  char showbuff[150];
  char c_uid[5];
  char uidbuff[10];
  distance= ultrasonic.read();
  if(distance<55 && distance>10){
    if(MySerial.available()>0){
      unsigned char mask[2] = {'0'};
      MySerial.readBytes(mask, 2);
      delay(200);
      if(MySerial.available()>0){
        MySerial.readBytes(mask, 2);
        int uid = rand() % 899 + 100;
        Serial.println(uid);
        sprintf(c_uid, "%d", uid);
        float temp = 0;

        if ((mask[0]==121)&(mask[1]==121)){
              sprintf(sendbuff, "AT+HTTPPARA=url,http://81.70.153.180/check.php/?check=0&UID=%d", uid);
              if(
                (AT_send_cmd(sendbuff, 50,"OK"))&&
                (AT_send_cmd("AT+HTTPPARA=port,80", 50,"OK"))&&
                (AT_send_cmd("AT+HTTPSETUP", 3000,"OK"))&&
                (AT_send_cmd("AT+HTTPACTION=0", 3000,c_uid))
              ){
                temp = AMG8833Read() + ((rand() % 9 + 591)/99.9)+2.8;
                sprintf(showbuff, "http://test.kugeek.cn/#/?temp=%.2f&UID=%d&ismask=1", temp,uid);
                showqrcode(showbuff,temp);

                sprintf(sendbuff, "AT+HTTPPARA=url,http://81.70.153.180/check.php/?check=1&UID=%d", uid);
                waittime = millis();
                while (1)
                {
                  sprintf(uidbuff, "%dpass", uid);

                  if(
                    (AT_send_cmd(sendbuff, 50,"OK"))&&
                    (AT_send_cmd("AT+HTTPPARA=port,80", 50,"OK"))&&
                    (AT_send_cmd("AT+HTTPSETUP", 3000,"OK"))&&
                    (AT_send_cmd("AT+HTTPACTION=0", 3000,uidbuff))
                  ){
                    showstr("PASS",32,38);
                    
                    delay(2000);
                    break;
                  }
                  if((millis()-waittime)>90000){
                    break;
                  }

                }

                showwait = 0;
              }              
        }else{
              if((mask[0]==110)&(mask[1]==110)){
              sprintf(sendbuff, "AT+HTTPPARA=url,http://81.70.153.180/check.php/?check=0&UID=%d", uid);
              if(
                (AT_send_cmd(sendbuff, 50,"OK"))&&
                (AT_send_cmd("AT+HTTPPARA=port,80", 50,"OK"))&&
                (AT_send_cmd("AT+HTTPSETUP", 3000,"OK"))&&
                (AT_send_cmd("AT+HTTPACTION=0", 3000,c_uid))
              ){
                temp = AMG8833Read() + ((rand() % 9 + 591)/99.9)+0.8;
                sprintf(showbuff, "http://test.kugeek.cn/#/?temp=%.2f&UID=%d&ismask=0", temp, uid);
                Serial.println(showbuff);
                showqrcode(showbuff,temp);
                sprintf(sendbuff, "AT+HTTPPARA=url,http://81.70.153.180/check.php/?check=1&UID=%d", uid);
                waittime = millis();
                while (1)
                {
                  sprintf(uidbuff, "%dpass", uid);

                  if(
                    (AT_send_cmd(sendbuff, 50,"OK"))&&
                    (AT_send_cmd("AT+HTTPPARA=port,80", 50,"OK"))&&
                    (AT_send_cmd("AT+HTTPSETUP", 3000,"OK"))&&
                    (AT_send_cmd("AT+HTTPACTION=0", 3000,uidbuff))
                  ){
                    showstr("PASS",32,38);
                    
                    delay(2000);
                    break;
                  }
                  if((millis()-waittime)>90000){
                    break;
                  }
                }
                
                showwait = 0;
              }
              }
        }
      }

    }

    //Serial.println(AMG8833Read());
  Serial.println(distance);
  


  }
  if(showwait==0)
    {

      showstr("Watting",32,38);
      showwait = 1;
    }
  

  delay(50);

}



void beep(){
  unsigned char i;//定义变量

for(i=0;i<80;i++)//一个频率的声音
{ 
digitalWrite(buzzer,HIGH);//发声音
delay(1);//延时1ms 
digitalWrite(buzzer,LOW);//不发声音
delay(1);//延时ms 
} 
for(i=0;i<100;i++)//另一个频率的声音 
{ 
digitalWrite(buzzer,HIGH);//发声音
delay(2);//延时2ms 
digitalWrite(buzzer,LOW);//不发声音
delay(2);//延时2ms 
} 
} 
