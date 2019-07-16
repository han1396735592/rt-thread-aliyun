#include "ali-led.h"

uint8_t ledid  = 1;
extern void   *pclient;

void prinf_common_message_arrive_info(iotx_mqtt_event_msg_pt msg){
	 iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt) msg->msg;
 /* print topic name and topic message */
  
		EXAMPLE_TRACE("---------------------------------------------------------------------");
	
    EXAMPLE_TRACE("packetId: %d", ptopic_info->packet_id);
    EXAMPLE_TRACE("Topic: '%.*s' (Length: %d)",
                  ptopic_info->topic_len,
                  ptopic_info->ptopic,
                  ptopic_info->topic_len);
    EXAMPLE_TRACE("Payload: '%.*s' (Length: %d)",
                  ptopic_info->payload_len,
                  ptopic_info->payload,
                  ptopic_info->payload_len);
    EXAMPLE_TRACE("---------------------------------------------------------------------");	
}





static void LED_BlinkOn_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
	iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt) msg->msg;
		prinf_common_message_arrive_info(msg);
		#ifndef UR_USING_LED
		cJSON * root = NULL;
    cJSON * param = NULL;
		cJSON * temp  = NULL;
		root =cJSON_Parse(ptopic_info->payload);
		if(root){
			param = cJSON_GetObjectItem(root,"params");
		}else{
			rt_kprintf("root is null");
		}
		
		if(param){	
			
			int BrightTiem,OffTiem;
			temp = cJSON_GetObjectItem(param,"BrightTiem");
			
			if(temp){
				BrightTiem = temp->valueint;
			}
			
			temp = cJSON_GetObjectItem(param,"OffTiem");
			
			if(temp){
				OffTiem = temp->valueint;
			}
			
			uint8_t code = LED_DeltBlinkOn(ledid,BrightTiem,OffTiem);
			
			if(SDK_RECEIVE_OK ==code){
				rt_kprintf("LED_DeltBlinkOn ok\n");
			}else{
				rt_kprintf("LED_DeltBlinkOn err code :%d\n",code);
			}
		
		}else{
			rt_kprintf("patam is null");
		}
		if(root){
			cJSON_Delete(root);
		}
		#endif	
}

static void LED_BlinkOff_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
   iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt) msg->msg;
		prinf_common_message_arrive_info(msg);
		#ifndef UR_USING_LED
		cJSON * root = NULL;
    cJSON * param = NULL;	
		cJSON * temp = NULL;
	
		root =cJSON_Parse(ptopic_info->payload);
		if(root){
			param = cJSON_GetObjectItem(root,"params");
		}else{
			rt_kprintf("root is null");
		}
		
		if(param){	
			
			
			uint8_t code = 	LED_DeltBlinkOff(ledid);			
			if(SDK_RECEIVE_OK ==code){
				rt_kprintf("LED_DeltBlinkOff ok\n");
			}else{
				rt_kprintf("LED_DeltBlinkOff err code :%d\n",code);
			}
	
				
		}else{
			rt_kprintf("patam is null");
		}
		if(root){
			cJSON_Delete(root);
		}
		#endif	
}


static void LED_Reset_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
   iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt) msg->msg;
		prinf_common_message_arrive_info(msg);
		#ifndef UR_USING_LED
		cJSON * root = NULL;
    cJSON * param = NULL;
		root =cJSON_Parse(ptopic_info->payload);
		if(root){
			param = cJSON_GetObjectItem(root,"params");
		}else{
			rt_kprintf("root is null");
		}
		
		if(param){		
				
		}else{
			rt_kprintf("patam is null");
		}
		if(root){
			cJSON_Delete(root);
		}
		#endif	
}

static void LED_SetAlign_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
   iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt) msg->msg;
		prinf_common_message_arrive_info(msg);
		#ifndef UR_USING_LED
		cJSON * root = NULL;
    cJSON * param = NULL;
		cJSON * temp  = NULL;
		root =cJSON_Parse(ptopic_info->payload);
		if(root){
			param = cJSON_GetObjectItem(root,"params");
		}else{
			rt_kprintf("root is null");
		}
		
		if(param){	
			
			int align;
			temp = cJSON_GetObjectItem(param,"BrightTiem");
			
		
			temp = cJSON_GetObjectItem(param,"align");
			
			if(temp){
				align = temp->valueint;
			}
			
			uint8_t code = LED_SetAlign(ledid,align);
			
			if(SDK_RECEIVE_OK ==code){
				rt_kprintf("LED_SetAlign ok\n");
			}else{
				rt_kprintf("LED_SetAlign err code :%d\n",code);
			}
		
		}else{
			rt_kprintf("patam is null");
		}
		if(root){
			cJSON_Delete(root);
		}
		#endif	
}

static void LED_SetAlignLine_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
   iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt) msg->msg;
		prinf_common_message_arrive_info(msg);
		#ifndef UR_USING_LED
		cJSON * root = NULL;
    cJSON * param = NULL;
		cJSON * temp  = NULL;
		root =cJSON_Parse(ptopic_info->payload);
		if(root){
			param = cJSON_GetObjectItem(root,"params");
		}else{
			rt_kprintf("root is null");
		}
		
		if(param){	
			
			int align,lineNo;
			temp = cJSON_GetObjectItem(param,"BrightTiem");
			
		
			temp = cJSON_GetObjectItem(param,"align");
			
			if(temp){
				align = temp->valueint;
			}
			temp = cJSON_GetObjectItem(param,"lineNo");
			
			if(temp){
				lineNo = temp->valueint;
			}
			
			uint8_t code = LED_SetAlignLine(ledid,lineNo,align);
			
			if(SDK_RECEIVE_OK ==code){
				rt_kprintf("LED_SetAlignLine ok\n");
			}else{
				rt_kprintf("LED_SetAlignLine err code :%d\n",code);
			}
		
		}else{
			rt_kprintf("patam is null");
		}
		if(root){
			cJSON_Delete(root);
		}
		#endif	
}

int ali_led_init(void){
	int rc ;
  rc = IOT_MQTT_Subscribe(pclient, LED_SET_ALIGN_LINE_TOPIC, IOTX_MQTT_QOS1, LED_SetAlignLine_message_arrive, NULL);
	if (rc < 0) 
		return rc;
	rc = IOT_MQTT_Subscribe(pclient, LED_SET_ALIGN_TOPIC, IOTX_MQTT_QOS1, LED_SetAlign_message_arrive, NULL);
	if (rc < 0) 
		return rc;
	rc = IOT_MQTT_Subscribe(pclient, LED_RESET_TOPIC, IOTX_MQTT_QOS1, LED_Reset_message_arrive, NULL);
	if (rc < 0) 
		return rc;
	rc = IOT_MQTT_Subscribe(pclient, LED_BLINK_OFF_TOPIC, IOTX_MQTT_QOS1, LED_BlinkOff_message_arrive, NULL);
	if (rc < 0) 
		return rc;
	rc = IOT_MQTT_Subscribe(pclient, LED_BLINK_ON_TOPIC, IOTX_MQTT_QOS1, LED_BlinkOn_message_arrive, NULL);
	if (rc < 0) 
		return rc;
	return rc;
}
