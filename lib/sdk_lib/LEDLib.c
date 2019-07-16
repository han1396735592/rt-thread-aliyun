/**
  ******************************************************************************
  * @file
  * @brief SDK 数据包发送操作库(嵌入式平台)
  ******************************************************************************
  * @note 本文件只适用于 嵌入式平台。 \n
  如果选用了不带ID的协议(如SH-C1X)，SDK函数调用需要ledid参数时，任意传入一个数字。
  *******************************************************************************
  */


#include "LEDLIB.h"


static unsigned int ReceiveTimeOut = 100;

#ifdef SH_C1X
#define LED_RCVSIZE C1X_RCVSIZE
#endif



void LED_SetReceiveTimeout(unsigned int outtime)
{
    ReceiveTimeOut = outtime;
}

static int SerialPort_Send(LED_Pack_t *pBuf,uint16_t sendByte,unsigned char ledid)
{
    if (0 == sendByte) return SDK_PARAMETER_ERROR;

    if (LED_SendData((uint8_t *)pBuf,sendByte) != sendByte) return SDK_SERIALPORT_ERROR;
    if (0 == ReceiveTimeOut ) return SDK_SEND_NOTRECEIVE;

#ifdef USE_PACT_ID
    if ((SDK_BROADCAST == ledid) || (SDK_BROADCAST_OLD == ledid)) return SDK_SEND_NOTRECEIVE;
#endif // USE_PACT_ID

#ifdef SH_C1P
    if ((SDK_BROADCAST == ledid)) return SDK_SEND_NOTRECEIVE;
#endif // SH_C1P

    return LED_ReceiveData(ReceiveTimeOut);
}

int LED_SendPack(unsigned char ledid,const char *pBuf,int sendByte)
{
    return SerialPort_Send((LED_Pack_t *)pBuf,sendByte,ledid);
}

 int  LED_SetBrushColour(unsigned char ledid,unsigned char ledcolour)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetBrushColour(&buf,ledid,ledcolour),ledid);
}

int  LED_DeltBrushColour(unsigned char ledid,unsigned char ledcolour)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_DeltBrushColour(&buf,ledid,ledcolour),ledid);
}

int  LED_ShowGBK(unsigned char ledid,unsigned char lineNo,const char *str)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_ShowGBK(&buf,ledid,lineNo,str),ledid);
}

 #if (defined SH_C1X)||(defined SH_C1T)
int LED_QuickWriteDisp(uint8_t ledid,uint16_t Xpos,uint16_t Ypos,uint16_t Pixel,const uint8_t *PixelBuf)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_QuickWriteDisp(&buf,ledid,Xpos,Ypos,Pixel,PixelBuf),ledid);
}
#endif

int  LED_SetBootGBK(unsigned char ledid,unsigned char lineNo,const char *str)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetBootGBK(&buf,ledid,lineNo,str),ledid);
}

int  LED_SetEmergGBK(unsigned char ledid,unsigned char lineNo,const char *str)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetEmergGBK(&buf,ledid,lineNo,str),ledid);
}

int  LED_SetEmergUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetEmergUnicode(&buf,ledid,lineNo,wstr),ledid);
}


int  LED_ChangeID(unsigned char ledid,unsigned char newid)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_ChangeID(&buf,ledid,newid),ledid);
}

int  LED_ShowUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_ShowUnicode(&buf,ledid,lineNo,wstr),ledid);
}

int  LED_SetBootUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetBootUnicode(&buf,ledid,lineNo,wstr),ledid);
}

int  LED_FactoryReset(unsigned char ledid)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_FactoryReset(&buf,ledid),ledid);
}

int  LED_ClearScreen(unsigned char ledid)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_ClearScreen(&buf,ledid),ledid);
}

int  LED_ClearLine(unsigned char ledid,unsigned char lineNo)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_ClearLine(&buf,ledid,lineNo),ledid);
}

int  LED_SetBrigth(unsigned char ledid,unsigned char brigth)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetBrigth(&buf,ledid,brigth),ledid);
}

int  LED_Reset(unsigned char ledid)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_Reset(&buf,ledid),ledid);
}

int  LED_SetDeltAlign(unsigned char ledid,unsigned char align)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetDeltAlign(&buf,ledid,align),ledid);
}

int  LED_SetDeltAlignLine(unsigned char ledid,unsigned char lineNo,unsigned char align)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetDeltAlignLine(&buf,ledid,lineNo,align),ledid);
}

int  LED_SetAlign(unsigned char ledid,unsigned char align)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetAlign(&buf,ledid,align),ledid);
}

int  LED_SetAlignLine(unsigned char ledid,unsigned char lineNo,unsigned char align)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetAlignLine(&buf,ledid,lineNo,align),ledid);
}

int  LED_BlinkOn(unsigned char ledid,uint16_t BrightTiem,uint16_t OffTiem)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_BlinkOn(&buf,ledid,BrightTiem,OffTiem),ledid);
}

int  LED_BlinkOff(unsigned char ledid)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_BlinkOff(&buf,ledid),ledid);
}

int  LED_DeltBlinkOn(unsigned char ledid,uint16_t BrightTiem,uint16_t OffTiem)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_DeltBlinkOn(&buf,ledid,BrightTiem,OffTiem),ledid);
}

int  LED_DeltBlinkOff(unsigned char ledid)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_DeltBlinkOff(&buf,ledid),ledid);
}

int  LED_SetScrollTime(unsigned char ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetScrollTime(&buf,ledid,MoveTime,PauseTime,StageTime),ledid);
}

int  LED_DeltScrollTime(unsigned char ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_DeltScrollTime(&buf,ledid,MoveTime,PauseTime,StageTime),ledid);
}

int  LED_SetScrollStyle(unsigned char ledid,uint32_t scrollStyle)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetScrollStyle(&buf,ledid,scrollStyle),ledid);
}

int  LED_DeltScrollStyle(unsigned char ledid,uint32_t scrollStyle)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_DeltScrollStyle(&buf,ledid,scrollStyle),ledid);
}

int  LED_SetPixelSize(unsigned char ledid,uint16_t Width,uint16_t Height)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetPixelSize(&buf,ledid,Width,Height),ledid);
}

int  LED_SetScanMode(unsigned char ledid,const LED_ScanMode_t *ledpolar)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetScanMode(&buf,ledid,ledpolar),ledid);
}


//-------------------------------------------------------

int  LED_SetSelfCheck(unsigned char ledid,unsigned char showTime,bool isShowID,bool isShowVer,bool IsShowMsg)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetSelfCheck(&buf,ledid,showTime,isShowID,isShowVer,IsShowMsg),ledid);
}



int  LED_SetBootImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetBootImage(&buf,ledid,lineNo,imageAddr,Width,Height),ledid);
}

int  LED_SetEmergImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetEmergImage(&buf,ledid,lineNo,imageAddr,Width,Height),ledid);
}

int  LED_SetLineFont(unsigned char ledid,uint8_t lineNo,uint16_t Width,uint16_t Height)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_SetLineFont(&buf,ledid,lineNo,Width,Height),ledid);
}

int  LED_DeltLineFont(unsigned char ledid,uint8_t lineNo,uint16_t Width,uint16_t Height)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_DeltLineFont(&buf,ledid,lineNo,Width,Height),ledid);
}

int  LED_ShowImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    LED_Pack_t buf;
    return SerialPort_Send(&buf,PackInit_ShowImage(&buf,ledid,lineNo,imageAddr,Width,Height),ledid);
}



