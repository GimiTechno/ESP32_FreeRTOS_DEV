#include "app_ntp.h"

struct tm g_timeInfo;//時刻を格納するオブジェクト
char g_ntp_buf[64] = {0};//文字格納用

/**
 * @brief APP NTP Init
 * 
 */
void APP_NTP_Init(void)
{
    configTime(JST, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");//NTPの設定
}

/**
 * @brief APP NTP Main
 * 
 */
char* APP_NTP_Main(void)
{
    // NTP Get Time
    getLocalTime(&g_timeInfo);

    sprintf(g_ntp_buf, "[NTP]:%04d/%d/%d %d:%d:%d",
            g_timeInfo.tm_year + 1900, g_timeInfo.tm_mon + 1, g_timeInfo.tm_mday,
            g_timeInfo.tm_hour, g_timeInfo.tm_min, g_timeInfo.tm_sec);//人間が読める形式に変換

    return g_ntp_buf;
}