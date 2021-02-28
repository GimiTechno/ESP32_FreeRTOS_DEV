#include "app_pm.h"
#include "app_main.h"

// イベントハンドル
extern EventGroupHandle_t PM_Event_Handler;        /* PM */
// メッセージキューハンドル
extern QueueHandle_t  QueueHandle;

static void PM_Deep_Sleep(uint32_t sleep_time);
static void PM_Deep_Sleep_Get_WakeUp(void);

static void PM_Deep_Sleep_Get_WakeUp(void)
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    // スリープ起床要因取得
    wakeup_reason = esp_sleep_get_wakeup_cause();

    // 起用要因毎に処理
    switch(wakeup_reason)
    {
        case ESP_SLEEP_WAKEUP_EXT0 :
            Serial.printf("外部割り込み(RTC_IO)で起動\n");
            break;

        case ESP_SLEEP_WAKEUP_EXT1 :
            Serial.printf("外部割り込み(RTC_CNTL)で起動 IO=%llX\n", esp_sleep_get_ext1_wakeup_status());
            break;

        case ESP_SLEEP_WAKEUP_TIMER :
            Serial.printf("タイマー割り込みで起動\n");
            break;

        case ESP_SLEEP_WAKEUP_TOUCHPAD :
            Serial.printf("タッチ割り込みで起動 PAD=%d\n", esp_sleep_get_touchpad_wakeup_status());
            break;

        case ESP_SLEEP_WAKEUP_ULP :
            Serial.printf("ULPプログラムで起動\n");
            break;

        case ESP_SLEEP_WAKEUP_GPIO :
            Serial.printf("ライトスリープからGPIO割り込みで起動\n");
            break;

        case ESP_SLEEP_WAKEUP_UART :
            Serial.printf("ライトスリープからUART割り込みで起動\n");
            break;

        default :
            break;
    }

    Serial.println("");
}

static void PM_Deep_Sleep(uint32_t sleep_time_sec)
{
    esp_sleep_enable_timer_wakeup(sleep_time_sec * SLEEP_ERROR); // 引数はusオーダー
    esp_deep_sleep_start();
}

void App_PM_Main_Task(void *pvParameters)
{
    uint8_t ret;
    EventBits_t  evt_bit;
    msgque_t msg_q;
    msgque_data_t q_data;
    uint32_t sleep_time;

    printf("APP PM Task (Run Core%d)\n",xPortGetCoreID());

    for(;;)
    {
        // イベント待ち
        evt_bit = xEventGroupWaitBits( PM_Event_Handler,      // イベントグループハンドラ
                                        PM_TASK_EVENT_WAIT,   // 待ちイベント
                                        pdTRUE,
                                        pdFALSE,
                                        portMAX_DELAY );

        // Initイベント
        if((evt_bit & EVENT_PM_0_INIT) != 0)
        {
            // (DEBUG)
            Serial.println("[APP PM Task] : Init Event");

            // スリープからの起床調査
            PM_Deep_Sleep_Get_WakeUp();

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_INIT;
            q_data.p_QData = NULL;
            msg_q.TaskID = APP_PM_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }

        // DeepSleepイベント
        if((evt_bit & EVENT_PM_6_DEEPSLEEP) != 0)
        {
            // (DEBUG)
            Serial.println("[APP PM Task] : DeepSleep Event");

            sleep_time = (1 * TIME_MIN) * TIME_US; // DeepSleep 60sec
            printf("[APP PM Task] : DeepSleep Start @%dmin\n",
                    ((sleep_time / TIME_MIN) / TIME_US));
            PM_Deep_Sleep(sleep_time);

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_INIT;
            q_data.p_QData = NULL;
            msg_q.TaskID = APP_PM_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }

    }
}