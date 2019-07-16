#include "iot_import.h"
#include "iot_export.h"
#include "rtthread.h"
#include "cJSON.H"
#include "LEDLIB.H"
#if defined(MQTT_ID2_AUTH) && defined(ON_DAILY)
    #define PRODUCT_KEY             "9rx2yMNV5l0"
    #define DEVICE_NAME             "sh_online_sample_mqtt"
    #define DEVICE_SECRET           "v9mqGzepKEphLhXmAoiaUIR2HZ7XwTky"
#elif defined(ON_DAILY)
    #define PRODUCT_KEY             "gsYfsxQJgeD"
    #define DEVICE_NAME             "DailyEnvDN"
    #define DEVICE_SECRET           "y1vzFkEgcuXnvkAfm627pwarx4HRNikX"
#elif defined(MQTT_ID2_AUTH)
    #define PRODUCT_KEY             "micKUvuzOps"
    #define DEVICE_NAME             "00AAAAAABBBBBB4B645F5800"
    #define DEVICE_SECRET           "v9mqGzepKEphLhXmAoiaUIR2HZ7XwTky"
#else
#ifdef PKG_USING_ALI_IOTKIT_PRODUCT_KEY
    #define PRODUCT_KEY             PKG_USING_ALI_IOTKIT_PRODUCT_KEY
#else
    #define PRODUCT_KEY             "yfTuLfBJTiL"
#endif

#ifdef PKG_USING_ALI_IOTKIT_DEVICE_NAME
    #define DEVICE_NAME             PKG_USING_ALI_IOTKIT_DEVICE_NAME
#else
    #define DEVICE_NAME             "TestDeviceForDemo"
#endif

#ifdef PKG_USING_ALI_IOTKIT_DEVICE_SECRET
    #define DEVICE_SECRET           PKG_USING_ALI_IOTKIT_DEVICE_SECRET
#else
    #define DEVICE_SECRET           "fSCl9Ns5YPnYN8Ocg0VEel1kXFnRlV6c"
#endif
#endif

#define EXAMPLE_TRACE(fmt, ...)  \
    do { \
        HAL_Printf("%s|%03d :: ", __func__, __LINE__); \
        HAL_Printf(fmt, ##__VA_ARGS__); \
        HAL_Printf("%s", "\r\n"); \
    } while(0)

#define LED_SET_ALIGN_TOPIC                     "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/LED_SetAlign"

#define LED_SET_ALIGN_LINE_TOPIC                     "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/LED_SetAlignLine"

#define LED_BLINK_ON_TOPIC                     "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/LED_BlinkOn"

#define LED_BLINK_OFF_TOPIC                     "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/LED_BlinkOff"

#define LED_RESET_TOPIC                     "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/LED_Reset"
		
		
		
void prinf_common_message_arrive_info(iotx_mqtt_event_msg_pt msg);



int  ali_led_init(void);





