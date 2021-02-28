/**
 * @file （ファイル名） : lib_mcu.h
 * @brief （概要） : MCUライブラリ
 * @author （作成者） : F.Y
 * @date （作成日） : 2021/01/14
 * @details （詳細な説明） : 
*/
#include "lib_math.h"
#include "lib_mcu.h"

lib_mcu_t type_size;

void lib_esp32__info( void )
{
    // uint32_t tmp;
    // uint8_t *p_psram_heap;
    esp_chip_info_t chip_info;

    /* Print chip information */
    esp_chip_info(&chip_info);
    printf("%s(WiFi%s%s Soc)\n",
        SoC_NAME,
        (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
        (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("CPU Core %d, Chip Rev.%d\n",
            chip_info.cores, chip_info.revision);

    printf("Flash %dMB (%s Flash)\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "Embedded" : "Ext SPI");

#ifdef PSRAM_ENABLE
    //  PSPRAM全ての容量を確保
    p_psram_heap = (uint8_t*) calloc( ESP32_PSRAM_HEAP_MAX , sizeof(uint8_t) );

    if(p_psram_heap != NULL)
    {
        printf("PSRAM Heap Get OK\r\n");
    }else{
        printf("ERR:PSRAM Heap Get Error\r\n");
    }

    //1バイト毎に値が書き込めるかチェック
    tmp = 0;
    while ( tmp < ESP32_PSRAM_HEAP_MAX )
    {
        p_psram_heap[tmp] = (uint8_t)tmp; //値を書き込む

        if ( p_psram_heap[tmp] != (uint8_t)tmp )  //値が合っているかチェック
        {
            // printf("ERR:PSRAM Heap Verify Error at %d\n", tmp);
            tmp--;
            break;
        }else{
            tmp++;
        }
    }

    // printf("PSRAM Heap %d Bytes Verify OK\n", tmp);
    free(p_psram_heap); //メモリの解放

    printf("PSRAM Heap %d Bytes\n", tmp);
#endif
}

void lib_type_size( void )
{
    type_size.float_size        = sizeof(float);
    type_size.double_size       = sizeof(double);
    type_size.long_double_size  = sizeof(long double);

    // double 型判定
    if(type_size.float_size == type_size.double_size)
    {
        type_size.core_type_flg = CORE_8BIT;
    }

    // 倍精度判定
    if(type_size.double_size != type_size.long_double_size)
    {
        type_size.core_type_flg = ARM_CORTEX_M;
    }else{
        type_size.core_type_flg = ARM_CORTEX_A;
    }
}

void lib_env_info( void )
{
    uint8_t tmp;

    lib_type_size();
    lib_esp32__info();

    printf("Pi = %.10f \n",math_pi());

    tmp = type_size.float_size;
    printf("float size(Byte) = %d \n",tmp);

    tmp = type_size.double_size;
    printf("double size(Byte) = %d \n",tmp);

    // double 型判定
    if(type_size.core_type_flg == CORE_8BIT)
    {
        printf("※8bit CPU(AVR or PIC)\r\n");
    }

    tmp = type_size.long_double_size;
    printf("long double size(Byte) = %d \n",tmp);

    // 倍精度判定
    if(type_size.core_type_flg != ARM_CORTEX_A)
    {
        printf("※倍精度\r\n");
    }else{
        printf("※単精度\r\n");
    }
}

void lib_MCU_Reset( void )
{
    fflush(stdout);
    esp_restart();
}

