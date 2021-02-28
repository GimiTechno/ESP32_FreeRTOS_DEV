#include "app_wifi.h"
#include "app_ota.h"
#include "app_ntp.h"

#include "app_main.h"

// セマフォハンドル
extern SemaphoreHandle_t RF_Semphr_Handler;
// メッセージキューハンドル
extern QueueHandle_t  QueueHandle;
// イベントハンドル
extern EventGroupHandle_t WiFi_Event_Handler;

static void wifi_init( void );

const char* p_ssid     = "HomeAP";
const char* p_password = "kr8-4-yung";

static void wifi_init( void )
{
    // Connect to WiFi network
    WiFi.begin(p_ssid, p_password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(p_ssid);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void App_WiFi_Main_Task(void *pvParameters)
{
    uint8_t ret;
    EventBits_t  evt_bit;
    msgque_t msg_q;
    msgque_data_t q_data;
    char* p_ntp_data;

    printf("APP WiFi Task (Run Core%d)\n",xPortGetCoreID());

    for(;;)
    {
        // イベント待ち
        evt_bit = xEventGroupWaitBits( WiFi_Event_Handler,      // イベントグループハンドラ
                                        WIFI_TASK_EVENT_WAIT,   // 待ちイベント
                                        pdTRUE,
                                        pdFALSE,
                                        portMAX_DELAY );

        if(evt_bit > 0)
        {
            // RFセマフォ取得待ち（RFはBLEと排他）
            ret = xSemaphoreTake( RF_Semphr_Handler,
                                portMAX_DELAY );

            // セマフォが取れたのでWiFi処理
            if(ret != pdFALSE)
            {

                // WiFi Initイベント
                if((evt_bit & EVENT_WIFI_0_INIT) != 0)
                {
                    // (DEBUG)
                    Serial.println("[APP WiFi Task] : Init Event");
                    wifi_init();

                    // メッセージ作成
                    q_data.QDataKind = Q_DATA_KIND_INIT;
                    q_data.p_QData = NULL;
                    msg_q.TaskID = APP_WIFI_MAIN_TASK;
                    msg_q.p_MsgData = &q_data;

                    // キューにメッセージ送信
                    ret = xQueueSend( QueueHandle, &msg_q, 0 );
                }

                // NTPイベント
                if((evt_bit & EVENT_WIFI_10_NTP) != 0)
                {
                    APP_NTP_Init();

                    // (DEBUG)
                    Serial.println("[APP WiFi Task] : NTP Get Event");

                    p_ntp_data = APP_NTP_Main();

                    // メッセージ作成
                    q_data.QDataKind = Q_DATA_KIND_NTP;
                    q_data.p_QData = p_ntp_data;
                    msg_q.TaskID = APP_WIFI_MAIN_TASK;
                    msg_q.p_MsgData = &q_data;

                    // キューにメッセージ送信
                    ret = xQueueSend( QueueHandle, &msg_q, 0 );
                }

                // OTAイベント
                if((evt_bit & EVENT_WIFI_13_OTA) != 0)
                {
                    APP_OTA_Init();
                    // (DEBUG)
                    Serial.println("[APP WiFi Task] : OTA Proc Event");
                    APP_OTA_Req_Catch();
                }

                // RFセマフォ解放
                xSemaphoreGive( RF_Semphr_Handler );
            }
        }
    }
}