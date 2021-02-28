#ifndef __APP_NTP_H__
#define __APP_NTP_H__

#include "app_wifi.h"

// タイムゾーン(JST)
#define JST         3600* 9

void APP_NTP_Init(void);
char* APP_NTP_Main(void);

#endif /* __APP_NTP_H__ */