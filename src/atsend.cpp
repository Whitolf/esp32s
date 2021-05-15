#include <atsend.h>

HardwareSerial N58Serial(1);
void AT_Init(){

 N58Serial.begin(115200,SERIAL_8N1,13,12);
 N58Serial.setRxBufferSize(520);
 
}

int AT_check_cmd(char *replystr,int waittime)
{
	unsigned long time;
  char response[520];
  int ret = 0;
  int i = 0 ;
  time = millis();

  while(1) {
    if (N58Serial.available() > 0 ){
      response[i] = N58Serial.read();
      response[i + 1] = '\0';
      i++;
    }
    if((strstr(response,"ERROR"))||(strstr(response,replystr))||((millis()-time)>waittime)||(i>519))
      break;
  }
  Serial.println(response);
      
  if(strstr(response,replystr)){
    ret=1;
  }else if(strstr(response,"ERROR"))
  {
    ret=0;  
  }
  return ret;
}
  
int AT_send_cmd(char *cmd,int waittime,char *reply)
{

  N58Serial.printf("%s\r\n",cmd);//发送命令
  //得到有效数据
	return AT_check_cmd(reply,waittime);;
} 

int N58available(){
  return N58Serial.available();
}

int N58read(){
  return N58Serial.read();
}

size_t N58print(char *str){
  return N58Serial.print(str);
}