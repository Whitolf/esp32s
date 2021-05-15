#ifndef __ATSEND_H__
#define __ATSEND_H__

#include <HardwareSerial.h>


int AT_send_cmd(char *cmd,int waittime,char *reply);
int AT_check_cmd(char *replystr,int waittime);
void AT_Init();

int N58available();
int N58read();
size_t N58print(char *str);

#endif