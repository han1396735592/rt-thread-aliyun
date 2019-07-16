#include "vs-10.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
//VS10XX??????
_vs10xx_obj vsset=
{
	220,	//??:220
	6,		//???? 60Hz
	15,		//???? 15dB	
	10,		//???? 10Khz	
	15,		//???? 10.5dB
	0,		//????	
	1,		//????????.
};


////////////////////////////////////////////////////////////////////////////////
//???????
//data:??????
//???:?????
uint8_t VS_SPI_ReadWriteByte(uint8_t data)
{			  	 
	///return SPI1_ReadWriteByte(data);	  
}
//SD???????,????
void VS_SPI_SpeedLow(void)
{								 
	//SPI1_SetSpeed(((uint16_t)0x0020));//???????	
}
//SD????????,?????
void VS_SPI_SpeedHigh(void)
{						  
	//SPI1_SetSpeed(((uint16_t)0x0010));//???????		 
}


/****************************************************************************
* Function Name  : VS_Config
* Description    : ?VS10XX?????IO??SPI?????.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void VS_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB
	//	|RCC_AHB1Periph_GPIOE
	//	|RCC_AHB1Periph_GPIOG
	//	|RCC_AHB1Periph_GPIOB, ENABLE);
	
	/* VS10XX_CS ? PE6 */
	GPIO_InitStructure.Pin = GPIO_PIN_6;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//100MHz
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	
	
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* VS10XX_RESET ? PG8,S10xx_XDCS ? PG6*/
	GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_8;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	/* VS10XX_DREQ ?PB15 */
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//FLASH_CS
	GPIO_InitStructure.Pin = GPIO_PIN_14;//PB14
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;//??

	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//100MHz
	GPIO_InitStructure.Pull = GPIO_PULLUP;//??
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);//???
	//GPIO_SetBits(GPIOB,GPIO_PIN_14);
	
	//NRF24L01_CS
	GPIO_InitStructure.Pin = GPIO_PIN_7;//PG7
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);//???
//	GPIO_SetBits(GPIOG,GPIO_PIN_7);
	
	/* ???SPI1 */
	//SPI1_Init();
}

////////////////////////////////////////////////////////////////////////////////	 	  
//???VS10XX
void VS_Soft_Reset(void)
{	 
	uint8_t retry=0;  				   
	while(rt_pin_read(VS_XCS_PIN)==0); 					//????????	   
	VS_SPI_ReadWriteByte(0Xff);			//????
	retry=0;
	while(VS_RD_Reg(SPI_MODE)!=0x0800)	// ????,???  
	{
		VS_WR_Cmd(SPI_MODE,0x0804);		// ????,???	    
		rt_thread_mdelay(2);//????1.35ms 
		if(retry++>100)break; 	    
	}	 		 
	while(rt_pin_read(VS_XCS_PIN)==0);//????????	 
	retry=0;
	while(VS_RD_Reg(SPI_CLOCKF)!=0X9800)//??VS10XX???,3?? ,1.5xADD 
	{
		VS_WR_Cmd(SPI_CLOCKF,0X9800);	//??VS10XX???,3?? ,1.5xADD
		if(retry++>100)break; 	    
	}	 
	rt_thread_mdelay(20);
} 
//???MP3
//??1:????;0:????	   
uint8_t VS_HD_Reset(void)
{
	uint8_t retry=0;
	 rt_pin_write(VS_RST_PIN, PIN_LOW);
	rt_thread_mdelay(20);
	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH);//??????
	rt_pin_write(VS_XCS_PIN, PIN_HIGH);//??????

	rt_pin_write(VS_RST_PIN, PIN_HIGH)	;
	while(rt_pin_read(VS_XCS_PIN)==0&&retry<200)//??DREQ??
	{
		retry++;
		//delay_us(50);
	};
	rt_thread_mdelay(20);	
	if(retry>=200)return 1;
	else return 0;	    		 
}
//???? 
void VS_Sine_Test(void)
{											    
	VS_HD_Reset();	 
	VS_WR_Cmd(0x0b,0X2020);	  //????	 
 	VS_WR_Cmd(SPI_MODE,0x0820);//??VS10XX?????     
	while(rt_pin_read(VS_XCS_PIN)==0);     //??DREQ??
	//printf("mode sin:%x\n",VS_RD_Reg(SPI_MODE));
 	//?VS10XX????????:0x53 0xef 0x6e n 0x00 0x00 0x00 0x00
 	//??n = 0x24, ??VS10XX???????????,???????VS10XX?datasheet
  	VS_SPI_SpeedLow();//?? 
	rt_pin_write(VS_XDCS_PIN, PIN_LOW);//??????
	VS_SPI_ReadWriteByte(0x53);
	VS_SPI_ReadWriteByte(0xef);
	VS_SPI_ReadWriteByte(0x6e);
	VS_SPI_ReadWriteByte(0x24);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	rt_thread_mdelay(100);
	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH); 
    //??????
    rt_pin_write(VS_XDCS_PIN, PIN_LOW);//??????
	VS_SPI_ReadWriteByte(0x45);
	VS_SPI_ReadWriteByte(0x78);
	VS_SPI_ReadWriteByte(0x69);
	VS_SPI_ReadWriteByte(0x74);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	rt_thread_mdelay(100);
	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH);		 

    //???????????n??0x44,???????????????
    rt_pin_write(VS_XDCS_PIN, PIN_LOW);//??????      
	VS_SPI_ReadWriteByte(0x53);
	VS_SPI_ReadWriteByte(0xef);
	VS_SPI_ReadWriteByte(0x6e);
	VS_SPI_ReadWriteByte(0x44);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	rt_thread_mdelay(100);
 	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH);
    //??????
    rt_pin_write(VS_XDCS_PIN, PIN_LOW);//??????
	VS_SPI_ReadWriteByte(0x45);
	VS_SPI_ReadWriteByte(0x78);
	VS_SPI_ReadWriteByte(0x69);
	VS_SPI_ReadWriteByte(0x74);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	rt_thread_mdelay(100);
	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH);	 
}	 
//ram ?? 
//???:RAM????
// VS1003???????0x807F,?????;VS1053?0X83FF.																				 
uint16_t VS_Ram_Test(void)
{ 
	VS_HD_Reset();     
 	VS_WR_Cmd(SPI_MODE,0x0820);// ??VS10XX?????
	while (rt_pin_read(VS_XCS_PIN)==0); // ??DREQ??			   
 	VS_SPI_SpeedLow();//?? 
	rt_pin_write(VS_XDCS_PIN, PIN_LOW);	       		    // xDCS = 1,??VS10XX?????
	VS_SPI_ReadWriteByte(0x4d);
	VS_SPI_ReadWriteByte(0xea);
	VS_SPI_ReadWriteByte(0x6d);
	VS_SPI_ReadWriteByte(0x54);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	VS_SPI_ReadWriteByte(0x00);
	rt_thread_mdelay(150);  
	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH);
	return VS_RD_Reg(SPI_HDAT0);// VS1003???????0x807F,?????;VS1053?0X83FF.;       
}     					   
//?VS10XX???
//address:????
//data:????
void VS_WR_Cmd(uint8_t address,uint16_t data)
{  
	while(rt_pin_read(VS_XCS_PIN)==0);//????		  
	VS_SPI_SpeedLow();//?? 	   
	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH); 	 
	 rt_pin_write(VS_XCS_PIN, PIN_LOW);	 
	VS_SPI_ReadWriteByte(VS_WRITE_COMMAND);//??VS10XX????
	VS_SPI_ReadWriteByte(address); 	//??
	VS_SPI_ReadWriteByte(data>>8); 	//?????
	VS_SPI_ReadWriteByte(data);	 	//???
	 rt_pin_write(VS_XCS_PIN, PIN_HIGH);          
	VS_SPI_SpeedHigh();				//??	   
} 
//?VS10XX???
//data:??????
void VS_WR_Data(uint8_t data)
{
	VS_SPI_SpeedHigh();//??,?VS1003B,???????36.864/4Mhz,?????9M 
	 rt_pin_write(VS_XDCS_PIN, PIN_LOW); 
	VS_SPI_ReadWriteByte(data);
	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH);    
}         
//?VS10XX????           
//address:?????
//???:????
//?????????,???
uint16_t VS_RD_Reg(uint8_t address)
{ 
	uint16_t temp=0;    	 
    while(rt_pin_read(VS_XCS_PIN)==0);//??????? 		  
	VS_SPI_SpeedLow();//?? 
	 rt_pin_write(VS_XDCS_PIN, PIN_HIGH);     
	 rt_pin_write(VS_XCS_PIN, PIN_LOW);       
	VS_SPI_ReadWriteByte(VS_READ_COMMAND);	//??VS10XX????
	VS_SPI_ReadWriteByte(address);       	//??
	temp=VS_SPI_ReadWriteByte(0xff); 		//?????
	temp=temp<<8;
	temp+=VS_SPI_ReadWriteByte(0xff); 		//?????
	 rt_pin_write(VS_XCS_PIN, PIN_HIGH);    
	VS_SPI_SpeedHigh();//??	  
   return temp; 
}  
//??VS10xx?RAM
//addr:RAM??
//???:????
uint16_t VS_WRAM_Read(uint16_t addr) 
{ 
	uint16_t res;			   	  
 	VS_WR_Cmd(SPI_WRAMADDR, addr); 
	res=VS_RD_Reg(SPI_WRAM);  
 	return res;
} 
//?VS10xx?RAM
//addr:RAM??
//val:????? 
void VS_WRAM_Write(uint16_t addr,uint16_t val) 
{  		   	  
 	VS_WR_Cmd(SPI_WRAMADDR,addr);	//?RAM?? 
	while(rt_pin_read(VS_XCS_PIN)==0); 				//????	   
	VS_WR_Cmd(SPI_WRAM,val); 		//?RAM? 
} 
//??????(?VS1053??) 
//t:0,1,????;2,2???;3,3???;4,4??;????
void VS_Set_Speed(uint8_t t)
{
	VS_WRAM_Write(0X1E04,t);		//?????? 
}
//FOR WAV HEAD0 :0X7761 HEAD1:0X7665    
//FOR MIDI HEAD0 :other info HEAD1:0X4D54
//FOR WMA HEAD0 :data speed HEAD1:0X574D
//FOR MP3 HEAD0 :data speed HEAD1:ID
//??????,??III
const uint16_t bitrate[2][16]=
{ 
{0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,0}, 
{0,32,40,48,56,64,80,96,112,128,160,192,224,256,320,0}
};
//??Kbps???
//???:?????
uint16_t VS_Get_HeadInfo(void)
{
	unsigned int HEAD0;
	unsigned int HEAD1;  
 	HEAD0=VS_RD_Reg(SPI_HDAT0); 
    HEAD1=VS_RD_Reg(SPI_HDAT1);
  	//printf("(H0,H1):%x,%x\n",HEAD0,HEAD1);
    switch(HEAD1)
    {        
        case 0x7665://WAV??
        case 0X4D54://MIDI?? 
		case 0X4154://AAC_ADTS
		case 0X4144://AAC_ADIF
		case 0X4D34://AAC_MP4/M4A
		case 0X4F67://OGG
        case 0X574D://WMA??
		case 0X664C://FLAC??
        {
			////printf("HEAD0:%d\n",HEAD0);
            HEAD1=HEAD0*2/25;//???*8/100
            if((HEAD1%10)>5)return HEAD1/10+1;//???????????
            else return HEAD1/10;
        }
        default://MP3??,?????III??
        {
            HEAD1>>=3;
            HEAD1=HEAD1&0x03; 
            if(HEAD1==3)HEAD1=1;
            else HEAD1=0;
            return bitrate[HEAD1][HEAD0>>12];
        }
    }  
}
//???????
//???:???????
uint32_t VS_Get_ByteRate(void)
{
	return VS_WRAM_Read(0X1E05);//????
}
//?????????
//???:???????
uint16_t VS_Get_EndFillByte(void)
{
	return VS_WRAM_Read(0X1E06);//????
}  
//????????
//???32??
//???:0,????
//		 1,VS10xx????,?????????    
uint8_t VS_Send_MusicData(uint8_t* buf)
{
	uint8_t n;
	if(rt_pin_read(VS_XCS_PIN)!=0)  //????VS10XX
	{			   	 
		 rt_pin_write(VS_XDCS_PIN, PIN_LOW);
        for(n=0;n<32;n++)
		{
			VS_SPI_ReadWriteByte(buf[n]);	 			
		}
		 rt_pin_write(VS_XDCS_PIN, PIN_HIGH);   				   
	}else return 1;
	return 0;//?????
}
//??
//???????,??????“??”				
void VS_Restart_Play(void)
{
	uint16_t temp;
	uint16_t i;
	uint8_t n;	  
	uint8_t vsbuf[32];
	for(n=0;n<32;n++)vsbuf[n]=0;//??
	temp=VS_RD_Reg(SPI_MODE);	//??SPI_MODE???
	temp|=1<<3;					//??SM_CANCEL?
	temp|=1<<2;					//??SM_LAYER12?,????MP1,MP2
	VS_WR_Cmd(SPI_MODE,temp);	//??????????
	for(i=0;i<2048;)			//??2048?0,????SM_CANCEL?.???0,????????????
	{
		if(VS_Send_MusicData(vsbuf)==0)//???32????????
		{
			i+=32;						//???32???
   			temp=VS_RD_Reg(SPI_MODE);	//??SPI_MODE???
 			if((temp&(1<<3))==0)break;	//?????
		}	
	}
	if(i<2048)//SM_CANCEL??
	{
		temp=VS_Get_EndFillByte()&0xff;//??????
		for(n=0;n<32;n++)vsbuf[n]=temp;//????????
		for(i=0;i<2052;)
		{
			if(VS_Send_MusicData(vsbuf)==0)i+=32;//??	  
		}   	
	}else VS_Soft_Reset();  	//SM_CANCEL???,???,????? 	  
	temp=VS_RD_Reg(SPI_HDAT0); 
    temp+=VS_RD_Reg(SPI_HDAT1);
	if(temp)					//???,????????,????,???
	{
		VS_HD_Reset();		   	//???
		VS_Soft_Reset();  		//??? 
	} 
}
//??????                          
void VS_Reset_DecodeTime(void)
{
	VS_WR_Cmd(SPI_DECODE_TIME,0x0000);
	VS_WR_Cmd(SPI_DECODE_TIME,0x0000);//????
}
//??mp3?????n sec
//???:????
uint16_t VS_Get_DecodeTime(void)
{ 		
	uint16_t dt=0;	 
	dt=VS_RD_Reg(SPI_DECODE_TIME);      
 	return dt;
} 	    					  
//vs10xx??patch.
//patch:patch???
//len:patch??
void VS_Load_Patch(uint16_t *patch,uint16_t len) 
{
	uint16_t i; 
	uint16_t addr, n, val; 	  			   
	for(i=0;i<len;) 
	{ 
		addr = patch[i++]; 
		n    = patch[i++]; 
		if(n & 0x8000U) //RLE run, replicate n samples 
		{ 
			n  &= 0x7FFF; 
			val = patch[i++]; 
			while(n--)VS_WR_Cmd(addr, val);  
		}else //copy run, copy n sample 
		{ 
			while(n--) 
			{ 
				val = patch[i++]; 
				VS_WR_Cmd(addr, val); 
			} 
		} 
	} 	
} 		  	  
//??VS10XX?????????
//volx:????(0~254)
void VS_Set_Vol(uint8_t volx)
{
    uint16_t volt=0; 			//?????
    volt=254-volx;			//????,?????,??????? 
	volt<<=8;
    volt+=254-volx;			//?????????
    VS_WR_Cmd(SPI_VOL,volt);//??? 
}
//???????
//bfreq:??????	2~15(??:10Hz)
//bass:????			0~15(??:1dB)
//tfreq:?????? 	1~15(??:Khz)
//treble:????  	 	0~15(??:1.5dB,??9??????)
void VS_Set_Bass(uint8_t bfreq,uint8_t bass,uint8_t tfreq,uint8_t treble)
{
    uint16_t bass_set=0; //????????
    signed char temp=0;   	 
	if(treble==0)temp=0;	   		//??
	else if(treble>8)temp=treble-8;
 	else temp=treble-9;  
	bass_set=temp&0X0F;				//????
	bass_set<<=4;
	bass_set+=tfreq&0xf;			//??????
	bass_set<<=4;
	bass_set+=bass&0xf;				//????
	bass_set<<=4;
	bass_set+=bfreq&0xf;			//????    
	VS_WR_Cmd(SPI_BASS,bass_set);	//BASS 
}
//????
//eft:0,??;1,??;2,??;3,??.
void VS_Set_Effect(uint8_t eft)
{
	uint16_t temp;	 
	temp=VS_RD_Reg(SPI_MODE);	//??SPI_MODE???
	if(eft&0X01)temp|=1<<4;		//??LO
	else temp&=~(1<<5);			//??LO
	if(eft&0X02)temp|=1<<7;		//??HO
	else temp&=~(1<<7);			//??HO						   
	VS_WR_Cmd(SPI_MODE,temp);	//????    
}	 
//?????/?????.
//sw:0,??;1,??.
void VS_SPK_Set(uint8_t sw)
{
	VS_WRAM_Write(GPIO_DDR,1<<4);	//VS1053?GPIO4?????
	VS_WRAM_Write(GPIO_ODATA,sw<<4);//??VS1053?GPIO4???(0/1)
} 
///////////////////////////////////////////////////////////////////////////////
//????,???.
void VS_Set_All(void) 				
{			 
	VS_Set_Vol(vsset.mvol);			//????
	VS_Set_Bass(vsset.bflimit,vsset.bass,vsset.tflimit,vsset.treble);  
	VS_Set_Effect(vsset.effect);	//??????
	VS_SPK_Set(vsset.speakersw);	//???????? 
}


