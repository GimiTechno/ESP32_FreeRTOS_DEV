#include "app_main.h"

// Taskハンドル
TaskHandle_t AppMainTaskHandle;
TaskHandle_t AppWiFiTaskHandle;
TaskHandle_t AppBLETaskHandle;
TaskHandle_t AppPMTaskHandle;
TaskHandle_t AppSensorTaskHandle;
TaskHandle_t AppPWMTaskHandle;

// TaskHandle_t AppDebugTaskHandle;

// タイマハンドル
TimerHandle_t Timer_125us_Handle;
TimerHandle_t Timer_250us_Handle;
TimerHandle_t Timer_500us_Handle;
TimerHandle_t Timer_1ms_Handle;
TimerHandle_t Timer_2ms_Handle;
TimerHandle_t Timer_4ms_Handle;
TimerHandle_t Timer_8ms_Handle;
TimerHandle_t Timer_10ms_Handle;
TimerHandle_t Timer_100ms_Handle;
TimerHandle_t Timer_1s_Handle;

// メッセージキューハンドル
QueueHandle_t  QueueHandle;

// セマフォハンドル
SemaphoreHandle_t RF_Semphr_Handler;

// イベントハンドル
EventGroupHandle_t WiFi_Event_Handler;      /* WiFi */
EventGroupHandle_t BLE_Event_Handler;       /* BLE */
EventGroupHandle_t PM_Event_Handler;        /* PM */
EventGroupHandle_t Sensor_Event_Handler;    /* Sensor */
EventGroupHandle_t PWM_Event_Handler;       /* PWM */

static void app_task_list(void);
static void Timer_1ms_Handler( void *param );
static void Timer_2ms_Handler( void *param );
static void Timer_4ms_Handler( void *param );
static void Timer_8ms_Handler( void *param );
static void Timer_10ms_Handler( void *param );
static void Timer_100ms_Handler( void *param );
static void Timer_1s_Handler( void *param );
static void Timer_Create(void);
static void APP_Main(void);

static void APP_Main(void)
{
    
}

static void app_task_list(void)
{
    // char* p_tasklist_buf;

    // p_tasklist_buf = (char *)calloc(0x01,TASK_LIST_HEAP_SIZE);

    // vTaskList(p_tasklist_buf);
    printf("--------------- Heap:%u ---------------------\n", esp_get_free_heap_size());

    printf("Task Info : %d Task Running \n",uxTaskGetNumberOfTasks());
    // printf("%s", p_tasklist_buf);
    printf("----------------------------------------------\r\n");

    // free(p_tasklist_buf);
}

/**
 * @brief 1ms周期ハンドラ
 * 
 * @param param 
 */
static void Timer_1ms_Handler( void *param )
{
#if 0
    // 超音波センサイベント発行
    xEventGroupSetBits( Sensor_Event_Handler,
                        EVENT_SENSOR_9_ULRS );
#endif
}

/**
 * @brief 2ms周期ハンドラ
 * 
 * @param param 
 */
static void Timer_2ms_Handler( void *param )
{
#if 0
    // IMUセンサイベント発行
    xEventGroupSetBits( Sensor_Event_Handler,
                        EVENT_SENSOR_3_IMU );
#endif
}

/**
 * @brief 4ms周期ハンドラ
 * 
 * @param param 
 */
static void Timer_4ms_Handler( void *param )
{
    // 
}

/**
 * @brief 8ms周期ハンドラ
 * 
 * @param param 
 */
static void Timer_8ms_Handler( void *param )
{
    // 
}

/**
 * @brief 10ms周期ハンドラ
 * 
 * @param param 
 */
static void Timer_10ms_Handler( void *param )
{
    // 
}

/**
 * @brief 100ms周期ハンドラ
 * 
 * @param param 
 */
static void Timer_100ms_Handler( void *param )
{
    // 
}

/**
 * @brief 1s周期ハンドラ
 * 
 * @param param 
 */
static void Timer_1s_Handler( void *param )
{
#if 0
    // WiFi NTP取得イベント発行
    xEventGroupSetBits( WiFi_Event_Handler,
                        EVENT_WIFI_10_NTP );
#endif
}

/**
 * @brief タイマ生成
 * 
 */
static void Timer_Create(void)
{
    /* タイマ生成 */
    // 1ms周期タイマ
    Timer_1ms_Handle = xTimerCreate( "TIM_1MS",                 /* タイマの名称 */
                                      1,                        /* 1ms周期 */
                                      pdTRUE,                   /* 自動繰り返しの有無 */
                                      NULL,                     /* ID変数のポインタ */
                                      Timer_1ms_Handler );      /* タイマハンドラの関数名 */

    // 2ms周期タイマ
    Timer_2ms_Handle = xTimerCreate( "TIM_2MS",                 /* タイマの名称 */
                                      2,                        /* 1ms周期 */
                                      pdTRUE,                   /* 自動繰り返しの有無 */
                                      NULL,                     /* ID変数のポインタ */
                                      Timer_2ms_Handler );      /* タイマハンドラの関数名 */

    // 4ms周期タイマ
    Timer_4ms_Handle = xTimerCreate( "TIM_4MS",                 /* タイマの名称 */
                                      4,                        /* 1ms周期 */
                                      pdTRUE,                   /* 自動繰り返しの有無 */
                                      NULL,                     /* ID変数のポインタ */
                                      Timer_4ms_Handler );      /* タイマハンドラの関数名 */

    // 8ms周期タイマ
    Timer_8ms_Handle = xTimerCreate( "TIM_8MS",                 /* タイマの名称 */
                                      8,                        /* 1ms周期 */
                                      pdTRUE,                   /* 自動繰り返しの有無 */
                                      NULL,                     /* ID変数のポインタ */
                                      Timer_8ms_Handler );      /* タイマハンドラの関数名 */    // 10ms周期タイマ

    // 10ms周期タイマ
    Timer_10ms_Handle = xTimerCreate( "TIM_10MS",               /* タイマの名称 */
                                        10,                     /* 10ms周期 */
                                        pdTRUE,                 /* 自動繰り返しの有無 */
                                        NULL,                   /* ID変数のポインタ */
                                        Timer_10ms_Handler );   /* タイマハンドラの関数名 */

    // 100ms周期タイマ
    Timer_100ms_Handle = xTimerCreate( "TIM_100MS",             /* タイマの名称 */
                                        100,                    /* 10ms周期 */
                                        pdTRUE,                 /* 自動繰り返しの有無 */
                                        NULL,                   /* ID変数のポインタ */
                                        Timer_100ms_Handler );  /* タイマハンドラの関数名 */

    // 1s周期タイマ
    Timer_1s_Handle = xTimerCreate( "TIM_1S",                   /* タイマの名称 */
                                    1000,                       /* 10ms周期 */
                                    pdTRUE,                     /* 自動繰り返しの有無 */
                                    NULL,                       /* ID変数のポインタ */
                                    Timer_1s_Handler );         /* タイマハンドラの関数名 */

    /* タイマの開始 */
    xTimerStart( Timer_1ms_Handle, 0 );
    xTimerStart( Timer_2ms_Handle, 0 );
    xTimerStart( Timer_4ms_Handle, 0 );
    xTimerStart( Timer_8ms_Handle, 0 );
    xTimerStart( Timer_10ms_Handle, 0 );
    xTimerStart( Timer_100ms_Handle, 0 );
    xTimerStart( Timer_1s_Handle, 0 );
}

/**
 * @brief メインタスク
 * 
 * @param pvParameters 
 */
void App_Main_Task(void *pvParameters)
{
    BaseType_t ret;
    // msgque_t que_buf[MSG_MAX];
    msgque_t que_buf;

    printf("APP Main Task (Run Core%d)\n",xPortGetCoreID());

    for(;;)
    {
        // メッセージ受信
        ret = xQueueReceive( QueueHandle, &que_buf, portMAX_DELAY );

        // メッセージ取得
        if(ret == pdPASS)
        {
            // タスク毎にメッセージ処理
            switch(que_buf.TaskID)
            {
                 // WiFiタスクからのメッセージ
                case APP_WIFI_MAIN_TASK :
                    switch(que_buf.p_MsgData->QDataKind)
                    {
                        case Q_DATA_KIND_INIT :
                            Serial.println("[APP Main Task] : WiFi Init MSG For WiFi Task" );

                            // WiFi NTP取得イベント発行
                            xEventGroupSetBits( WiFi_Event_Handler,
                                                EVENT_WIFI_10_NTP );
                            break;

                        case Q_DATA_KIND_OTA :
                            Serial.println("[APP Main Task] : OTA MSG For WiFi Task" );
                            break;

                        case Q_DATA_KIND_NTP :
                            // NTP表示
                            Serial.println("[APP Main Task] : NTP MSG For WiFi Task" );
                            Serial.println(que_buf.p_MsgData->p_QData);
                            break;

                        default:
                            break;
                    }
                    break;

                 // BLEタスクからのメッセージ
                case APP_BLE_MAIN_TASK :
                    switch(que_buf.p_MsgData->QDataKind)
                    {
                        case Q_DATA_KIND_INIT :
                            Serial.println("[APP Main Task] : BLE Init MSG For BLE Task" );
                            break;

                        case Q_DATA_KIND_BLE_UART :
                            Serial.println("[APP Main Task] : BLE UART MSG For BLE Task" );
                            break;

                        default:
                            break;
                    }
                    break;

                 // PMタスクからのメッセージ
                case APP_PM_MAIN_TASK :
                    switch(que_buf.p_MsgData->QDataKind)
                    {
                        // Init
                        case Q_DATA_KIND_INIT :
                            Serial.println("[APP Main Task] : Init MSG For PM Task" );
                            break;

                        case Q_DATA_KIND_DEEPSLEEP :
                            Serial.println("[APP Main Task] : DeepSleep MSG For PM Task" );
                            break;

                        default:
                            break;
                    }
                    break;

                 // センサタスクからのメッセージ
                case APP_SENSOR_MAIN_TASK :
                    switch(que_buf.p_MsgData->QDataKind)
                    {
                        // Init
                        case Q_DATA_KIND_INIT :
                            Serial.println("[APP Main Task] : Init MSG For Sensor Task" );
                            break;

                        // IMU
                        case Q_DATA_KIND_IMU :
                            Serial.println("[APP Main Task] : IMU Sensor MSG For Sensor Task" );
                            // IMU表示
                            printf("%s",que_buf.p_MsgData->p_QData);
                            break;

                        // 超音波センサ
                        case Q_DATA_KIND_ULRS :
                            Serial.println("[APP Main Task] : ULRS MSG For Sensor Task" );
                            // 超音波センサのから取得した距離
                            printf("%s",que_buf.p_MsgData->p_QData);
                            break;

                        // 湿温度センサ
                        case Q_DATA_KIND_TEMP :
                            Serial.println("[APP Main Task] : Temp Sensor MSG For Sensor Task" );
                            break;

                        // 外付けRTC
                        case Q_DATA_KIND_EXT_RTC :
                            Serial.println("[APP Main Task] : Ext RTC MSG For Sensor Task" );
                            break;

                        default:
                            break;
                    }
                    break;

                 // PWMタスクからのメッセージ
                case APP_PWM_MAIN_TASK :
                    switch(que_buf.p_MsgData->QDataKind)
                    {
                        // Init
                        case Q_DATA_KIND_INIT :
                            Serial.println("[APP Main Task] : Init MSG For PWM Task" );
                            break;

                        case Q_DATA_KIND_MOTOR_PWM :
                            Serial.println("[APP Main Task] : Mortor PWM For PWM Task" );
                            break;

                        case Q_DATA_KIND_MOTOR_TEST :
                            Serial.println("[APP Main Task] : Mortor TEST For PWM Task" );

                            // (DEBUG)
                            xEventGroupSetBits( PWM_Event_Handler,
                                                EVENT_PWM_15_MORTOR_TEST );
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }else{
            // 
        }
    }
    // Kill Own Task（絶対来ない）
    vTaskDelete(NULL);
}

/**
 * @brief アプリ初期化
 * 
 */
void App_Init(void)
{
    Serial.begin(115200);
    // Wait UART Init
    // delay(1000);

#ifdef ___DEBUG___

#ifdef PSRAM_ENABLE
    Serial.printf("Total Heap %dByte, Free Heap %dByte",
                    ESP.getHeapSize(), ESP.getFreeHeap());
    Serial.println("");

    Serial.printf("PSRAM Total Heap %dByte, PSRAM Free Heap %dByte",
                    ESP.getPsramSize(), ESP.getFreePsram());
    Serial.println("");
#endif
    Serial.printf("Flash Size %dByte, Flash Speed %dMHz",
                    ESP.getFlashChipSize(), (ESP.getFlashChipSpeed() / 1000000));
    Serial.println("");

    Serial.printf("ChipRev.%d, Freq %dMHz, SDK Ver.%s",
                    ESP.getChipRevision(), ESP.getCpuFreqMHz(), ESP.getSdkVersion());
    Serial.println("");

    lib_env_info();
    lib_math_accuracy();
    app_task_list();
#endif
    // セマフォ生成
    RF_Semphr_Handler = xSemaphoreCreateBinary();
    xSemaphoreGive( RF_Semphr_Handler );

    // メッセージキュー生成
    QueueHandle = xQueueCreate( MSG_MAX,            // 最大メッセージ数
                                MSG_SIZE );         // メッセージサイズ

    // イベントグループ生成
    WiFi_Event_Handler      = xEventGroupCreate();
    BLE_Event_Handler       = xEventGroupCreate();
    PM_Event_Handler        = xEventGroupCreate();
    Sensor_Event_Handler    = xEventGroupCreate();
    PWM_Event_Handler       = xEventGroupCreate();

    // App Main Task
    xTaskCreateUniversal(App_Main_Task,             // タスク関数
                        "App_Main_Task",            // タスク名
                        4096,                       // スタック
                        NULL,                       // 起動パラメータ
                        RTOS_PRIORITY_MAXIMUM,      // 優先度
                        &AppMainTaskHandle,         // タスクハンドラ
                        __APP_CPU__                 // 実行するコア
                        );

    // アプリ WiFi Main Task
    xTaskCreateUniversal(App_WiFi_Main_Task,        // タスク関数
                        "App_WiFi_Main_Task",       // タスク名
                        8192,                       // スタック
                        NULL,                       // 起動パラメータ
                        RTOS_PRIORITY_HIGH,         // 優先度
                        &AppWiFiTaskHandle,         // タスクハンドラ
                        __APP_CPU__                 // 実行するコア
                        );

    // アプリ BLE Main Task
    xTaskCreateUniversal(App_BLE_Main_Task,          // タスク関数
                        "App_BLE_Main_Task",         // タスク名
                        8192,                        // スタック
                        NULL,                        // 起動パラメータ
                        RTOS_PRIORITY_MIDDLE_LOW,    // 優先度
                        &AppBLETaskHandle,           // タスクハンドラ
                        __APP_CPU__                  // 実行するコア
                        );

    // アプリ PM Main Task
    xTaskCreateUniversal(App_PM_Main_Task,           // タスク関数
                        "App_PM_Main_Task",          // タスク名
                        2048,                        // スタック
                        NULL,                        // 起動パラメータ
                        RTOS_PRIORITY_MINIMUM,       // 優先度
                        &AppPMTaskHandle,            // タスクハンドラ
                        __APP_CPU__                  // 実行するコア
                        );

    // アプリ センサ Main Task
    xTaskCreateUniversal(App_Sensor_Main_Task,       // タスク関数
                        "App_Sensor_Main_Task",      // タスク名
                        2048,                        // スタック
                        NULL,                        // 起動パラメータ
                        RTOS_PRIORITY_MIDDLE_HIGH,   // 優先度
                        &AppSensorTaskHandle,        // タスクハンドラ
                        __APP_CPU__                  // 実行するコア
                        );

    // アプリ PWM Main Task
    xTaskCreateUniversal(App_PWM_Main_Task,          // タスク関数
                        "App_PWM_Main_Task",         // タスク名
                        2048,                        // スタック
                        NULL,                        // 起動パラメータ
                        RTOS_PRIORITY_MIDDLE_HIGH,   // 優先度
                        &AppPWMTaskHandle,           // タスクハンドラ
                        __APP_CPU__                  // 実行するコア
                        );

    /****** (DEBUG) ******/
    // Initイベント発行
    xEventGroupSetBits( BLE_Event_Handler,
                        EVENT_BLE_0_INIT );
    xEventGroupSetBits( WiFi_Event_Handler,
                        EVENT_WIFI_0_INIT );


    xEventGroupSetBits( PM_Event_Handler,
                        EVENT_PM_0_INIT );

    xEventGroupSetBits( Sensor_Event_Handler,
                        EVENT_SENSOR_0_INIT );

    xEventGroupSetBits( PWM_Event_Handler,
                        EVENT_PWM_0_INIT );

#if 1
    // (DEBUG)
    xEventGroupSetBits( PWM_Event_Handler,
                        EVENT_PWM_15_MORTOR_TEST );
#endif

    // Timer Create
    Timer_Create();

}
