#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"

#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_task_wdt.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
#define CHIP_NAME "ESP32-S2 Beta"
#endif

#define __WDT_ENABLE__  0x01
#define ___DEBUG___     0x01

#ifdef  WDT_ENABLE
#define WDT_TGL_FUNC    esp_task_wdt_reset()
#else
#define WDT_TGL_FUNC    __asm__ __volatile__ ("nop")
#endif

#define WDT_TGL         WDT_TGL_FUNC

#define TRUE            0x01
#define FALSE           0x00
// CPU種別
#define __PRO_CPU__     0x00    /* 下位層CPU (CPU#0) */
#define __APP_CPU__     0x01    /* 上位層CPU (CPU#1) */

// RTOS優先度（0～25）
typedef enum _e_rtos_priority
{
    RTOS_PRIORITY_DEAD          = 0,     /* 最低（使わない） */
    RTOS_PRIORITY_MINIMUM       = 1,     /* 最低(実質) */
    RTOS_PRIORITY_LOW           = 4,     /* 下 */
    RTOS_PRIORITY_MIDDLE_LOW    = 8,     /* 中の下 */
    RTOS_PRIORITY_MIDDLE        = 12,    /* 中 */
    RTOS_PRIORITY_MIDDLE_HIGH   = 16,    /* 中の上 */
    RTOS_PRIORITY_HIGH          = 20,    /* 上 */
    RTOS_PRIORITY_MAXIMUM       = 24     /* 最高優先度 */
} e_rtos_priority;


// タスクリスト関数（vTaskList(char *)）に渡すバッファサイズ
// ※PSRAMからヒープで確保する
#define TASK_LIST_HEAP_SIZE 4096
// タスクリスト関数（vTaskList(char *)）を使うためのマクロ
#ifndef configUSE_TRACE_FACILITY
// #undef configUSE_TRACE_FACILITY
#define configUSE_TRACE_FACILITY		        1
#endif

#ifndef configUSE_STATS_FORMATTING_FUNCTIONS
// #undef configUSE_STATS_FORMATTING_FUNCTIONS
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
#endif

#endif /* _COMMON_H_ */