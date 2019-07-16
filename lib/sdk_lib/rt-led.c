#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "LEDLIB.h"
#include "rt-led.h"
static  uint8_t ledid = 1;

static rt_device_t serial;   
uint16_t LED_SendData(const uint8_t *pBuf,size_t BufSize)
{
 
		if(serial){
				int i = 0;
				rt_kprintf("\nsend hex cmd ( ");
				for(;i<BufSize;i++){
					rt_kprintf("%x ",pBuf[i]);
				}
				rt_kprintf(" )\n");
				return rt_device_write(serial,0, pBuf, BufSize);
		}
		else
			return -1;
}

int LED_ReceiveData(uint16_t outtime) // ???,?????????
{
		
		uint8_t RxBuf[LED_RCVSIZE];
    //uint8_t RxBuf[8];
	uint8_t RxCount = 0;
		

    while(outtime--)
    {
			char ch;
			if(rt_device_read(serial, -1, &ch, 1) == 1){
				RxBuf[RxCount++] =ch;
			}
			//rt_kprintf("%x ,%d,%d",ch,RxCount,LED_RCVSIZE);
			if (RxCount >= LED_RCVSIZE){
			//if (RxCount >= 8){
				
				int i = 0;
				rt_kprintf("\nReceiveData hex  ( ");
				for(;i<RxCount;i++){
					rt_kprintf("%x ",RxBuf[i]);
				}
				rt_kprintf(" )\n");
				
         return PackInit_RCVData2SDK(RxBuf,RxCount);
      }
			//rt_kprintf(" time have = %d\n",outtime);
			rt_thread_mdelay(1);
    }
	
    return SDK_RECEIVE_OUTTIME;
}

static void init_led(int argc, char **argv){
	struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT; 
	serial = rt_device_find(RT_LED_USEING_UART_NAME);
	if(serial!=RT_NULL){
		rt_device_open(serial, RT_DEVICE_FLAG_STREAM);
		config.baud_rate = BAUD_RATE_9600;
		rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);
		rt_kprintf("init_led on %s ok\n",RT_LED_USEING_UART_NAME);
		LED_SetReceiveTimeout(200);
	}else{
		rt_kprintf("init_led err\n");
	}
}

static int led_test(int argc, char **argv){
	
	
	if(argc==1){
		const char *str = "测试";
		rt_kprintf(" str = %s\n",str);
		LED_ShowGBK(ledid,0,str); //显示文字
	}else
	if(argc==2){
			char * str = argv[1];
			rt_kprintf(" str = %s\n",str);
			LED_ShowGBK(ledid,0,str); //显示文字
	}	
	return 1;
}

INIT_DEVICE_EXPORT(init_led);
MSH_CMD_EXPORT(init_led, init_led);
MSH_CMD_EXPORT(led_test, led_test);
