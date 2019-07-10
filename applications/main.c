/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "LEDLIB.h"

static rt_device_t serial;   

#define LED0_PIN    GET_PIN(F, 9)
uint16_t LED_SendData(const uint8_t *pBuf,size_t BufSize)
{
 
		if(serial){
				rt_kprintf("send data to serial \n");
				return rt_device_write(serial,0, pBuf, BufSize);
		}
		else
			return -1;
}

int LED_ReceiveData(uint16_t outtime) // ???,?????????
{
		
		uint8_t RxBuf[LED_RCVSIZE];
    uint8_t RxCount = 0;

    while(outtime--)
    {
			char ch;
			if(rt_device_read(serial, -1, &ch, 1) == 1){
				RxBuf[RxCount++] =ch;
			}
			if (RxCount >= LED_RCVSIZE){
         return PackInit_RCVData2SDK(RxBuf,RxCount);
      }
			rt_thread_mdelay(1);
    }
	
    return SDK_RECEIVE_OUTTIME;
}

#include "iot_export.h"
static void init_led(int argc, char **argv){
	char * SAMPLE_UART_NAME = NULL;
	if(argc==2){
		SAMPLE_UART_NAME     =  argv[1];
	}else{
		SAMPLE_UART_NAME  =    "uart3" ; 
	}

	struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT; 
	serial = rt_device_find(SAMPLE_UART_NAME);
	if(serial!=RT_NULL){
		rt_device_open(serial, RT_DEVICE_FLAG_STREAM);
		config.baud_rate = BAUD_RATE_9600;
		rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);
		rt_kprintf("init_led on %s ok",RT_DEVICE_FLAG_STREAM);
		
	}else{
		rt_kprintf("init_led err");
	}
}

static int led_test(int argc, char **argv){
	
	if(argc==2){
			char * str = argv[1];
			uint8_t ledid = 1;
		
			rt_kprintf(" str = %s\n",str);
			LED_ShowGBK(ledid,0,str); //ÏÔÊ¾ÎÄ×Ö
	}
	
	return 1;

} 



int main(void)
{
    int count = 1;
   
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
	

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(init_led, init_led);
MSH_CMD_EXPORT(led_test, led_test);