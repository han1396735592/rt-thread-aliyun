/**
  ******************************************************************************
  * @file
  * @author     SPING
  * @version    V0.0.1
  * @date       2017-01-14
  * @copyright  sping520@gmail.com
  * @brief
  ******************************************************************************
  * @note
  * @attention
  * <P style="FONT-SIZE:13px;"><center>&copy; COPYRIGHT 2013 SPING </center></P>
  *******************************************************************************
  */


#include "LEDLIB.h"
#define BROADCAST_ID            (0x00) /**< 广播ID */


static uint8_t Calculating(LED_Pack_t *Buf,uint8_t ledid,size_t ParaSize)
{
    uint16_t Checksum;
    uint8_t *CRC16 = (((uint8_t *)Buf)+ParaSize-2);
    if (ParaSize> LEDPack_Size || ParaSize<MBADU_MINSIZE)
        return 0;
    Buf->Addr = ledid;
    Checksum = CRC16_Modbus((const uint8_t *)Buf,ParaSize-2);
    *CRC16 ++ = Checksum;
    *CRC16  = Checksum>>8;
    return ParaSize;
}

uint8_t PackInit_SetBrushColour(LED_Pack_t *Buf,uint8_t ledid,uint8_t ledcolour)
{

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_BRUSHCOLOR>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_BRUSHCOLOR;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_BRUSHCOLOR/2;
    Buf->req.MultW.ByteCount = C1PBYTE_BRUSHCOLOR;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = ledcolour;
    return Calculating(Buf,ledid,C1PBYTE_BRUSHCOLOR+MODBUS_MULTW_MINBYTE);

}

uint8_t PackInit_DeltBrushColour(LED_Pack_t *Buf,uint8_t ledid,uint8_t ledcolour)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_DELTBRUSH>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_DELTBRUSH;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_DELTBRUSH/2;
    Buf->req.MultW.ByteCount = C1PBYTE_DELTBRUSH;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = ledcolour;
    return Calculating(Buf,ledid,C1PBYTE_DELTBRUSH+MODBUS_MULTW_MINBYTE);
}


uint8_t PackInit_ShowGBK(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const char *str)
{
    int n  = strlen(str);
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_SHOWGBK;

    if(n>sizeof(Line->LineParam))
        n = sizeof(Line->LineParam);
    if (n)
        memcpy(Line->LineParam,str,n);
    if (n&0x01)
    {
        Line->LineParam[n++] = 0;
    }
    n += (int) (&Line->LineParam)-(int)(&Line->LineNo);

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_ShowUnicode(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const wchar_t *wstr)
{
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
		int n  = wcslen(wstr)*2;
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_SHOWUNICODE;
	
    if(n>sizeof(Line->LineParam))
        n = sizeof(Line->LineParam);
    if (n)
        memcpy(Line->LineParam,wstr,n);
    n += (int) (&Line->LineParam)-(int)(&Line->LineNo);

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetBootGBK(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const char *str)
{
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
		int n  = strlen(str);
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_BOOTGBK;

    if(n>sizeof(Line->LineParam))
        n = sizeof(Line->LineParam);
    if (n)
        memcpy(Line->LineParam,str,n);
    if (n&0x01)
    {
        Line->LineParam[n++] = 0;
    }
    n += (int) (&Line->LineParam)-(int)(&Line->LineNo);

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);

}

uint8_t PackInit_SetBootUnicode(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const wchar_t *wstr)
{
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
	  int n  = wcslen(wstr)*2;
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_BOOTUNICODE;

    
    if(n>sizeof(Line->LineParam))
        n = sizeof(Line->LineParam);
    if (n)
        memcpy(Line->LineParam,wstr,n);
    n += (int) (&Line->LineParam)-(int)(&Line->LineNo);

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_ShowImage(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
    int n  = 10;	
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_SHOWIMAGE;

    Line->LineParam[0] = imageAddr>>24;
    Line->LineParam[1] = imageAddr>>16;
    Line->LineParam[2] = imageAddr>>8;
    Line->LineParam[3] = imageAddr;
    Line->LineParam[4] = Width>>8;
    Line->LineParam[5] = Width;
    Line->LineParam[6] = Height>>8;
    Line->LineParam[7] = Height;

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetBootImage(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
	  int n  = 10;
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_BOOTIMAGE;
    
    Line->LineParam[0] = imageAddr>>24;
    Line->LineParam[1] = imageAddr>>16;
    Line->LineParam[2] = imageAddr>>8;
    Line->LineParam[3] = imageAddr;
    Line->LineParam[4] = Width>>8;
    Line->LineParam[5] = Width;
    Line->LineParam[6] = Height>>8;
    Line->LineParam[7] = Height;

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetEmergImage(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
    int n  = 10;
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_EMOIMAGE;
    Line->LineParam[0] = imageAddr>>24;
    Line->LineParam[1] = imageAddr>>16;
    Line->LineParam[2] = imageAddr>>8;
    Line->LineParam[3] = imageAddr;
    Line->LineParam[4] = Width>>8;
    Line->LineParam[5] = Width;
    Line->LineParam[6] = Height>>8;
    Line->LineParam[7] = Height;

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetEmergGBK(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const char *str)
{
    int n  = strlen(str);
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_EMOGBK;

    if(n>sizeof(Line->LineParam))
        n = sizeof(Line->LineParam);
    if (n)
        memcpy(Line->LineParam,str,n);
    if (n&0x01)
    {
        Line->LineParam[n++] = 0;
    }
    n += (int) (&Line->LineParam)-(int)(&Line->LineNo);

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);

}

uint8_t PackInit_SetEmergUnicode(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const wchar_t *wstr)
{
    int n  = wcslen(wstr)*2;
    C1P_LineCmd_t *Line = (C1P_LineCmd_t *)Buf->req.MultW.Data;
    Line->LineNo = lineNo;
    Line->LineCMD = C1PLINE_EMOUNICODE;
    if(n>sizeof(Line->LineParam))
        n = sizeof(Line->LineParam);
    if (n)
        memcpy(Line->LineParam,wstr,n);
    n += (int) (&Line->LineParam)-(int)(&Line->LineNo);

    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_LINE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_LINE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = n/2;
    Buf->req.MultW.ByteCount = n;
    return Calculating(Buf,ledid,n+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetBrigth(LED_Pack_t *Buf,uint8_t ledid,uint8_t brigth)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_BRIGTH>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_BRIGTH;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_BRIGTH/2;
    Buf->req.MultW.ByteCount = C1PBYTE_BRIGTH;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = brigth;
    return Calculating(Buf,ledid,C1PBYTE_BRIGTH+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_FactoryReset(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_FACTORYRESET>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_FACTORYRESET;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_FACTORYRESET/2;
    Buf->req.MultW.ByteCount = C1PBYTE_FACTORYRESET;
    C1X_WriteKey(Buf->req.MultW.Data,0);
    return Calculating(Buf,ledid,C1PBYTE_FACTORYRESET+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_ClearScreen(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_CLEARCREEN>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_CLEARCREEN;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_CLEARCREEN/2;
    Buf->req.MultW.ByteCount = C1PBYTE_CLEARCREEN;
    C1X_WriteKey(Buf->req.MultW.Data,0);
    return Calculating(Buf,ledid,C1PBYTE_CLEARCREEN+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_ClearLine(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo)
{
    return PackInit_ShowGBK(Buf,ledid,lineNo," ");
}

uint8_t PackInit_Reset(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_RESET>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_RESET;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_RESET/2;
    Buf->req.MultW.ByteCount = C1PBYTE_RESET;
    C1X_WriteKey(Buf->req.MultW.Data,0);
    return Calculating(Buf,ledid,C1PBYTE_RESET+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_ChangeID(LED_Pack_t *Buf,uint8_t ledid,uint8_t newid)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_CHANGEID>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_CHANGEID;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_CHANGEID/2;
    Buf->req.MultW.ByteCount = C1PBYTE_CHANGEID;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = newid;
    return Calculating(Buf,ledid,C1PBYTE_CHANGEID+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetAlign(LED_Pack_t *Buf,uint8_t ledid,uint8_t align)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETALIGN>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETALIGN;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETALIGN/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETALIGN;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = align;
    return Calculating(Buf,ledid,C1PBYTE_SETALIGN+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetAlignLine(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint8_t align)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETALIGN>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETALIGN;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETALIGN/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETALIGN;
    Buf->req.MultW.Data[0] = lineNo;
    Buf->req.MultW.Data[1] = align;
    return Calculating(Buf,ledid,C1PBYTE_SETALIGN+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetDeltAlignLine(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint8_t align)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_DELTALIGN>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_DELTALIGN;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_DELTALIGN/2;
    Buf->req.MultW.ByteCount = C1PBYTE_DELTALIGN;
    Buf->req.MultW.Data[0] = lineNo;
    Buf->req.MultW.Data[1] = align;
    return Calculating(Buf,ledid,C1PBYTE_DELTALIGN+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetDeltAlign(LED_Pack_t *Buf,uint8_t ledid,uint8_t align)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_DELTALIGN>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_DELTALIGN;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_DELTALIGN/2;
    Buf->req.MultW.ByteCount = C1PBYTE_DELTALIGN;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = align;
    return Calculating(Buf,ledid,C1PBYTE_DELTALIGN+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_BlinkOn(LED_Pack_t *Buf,uint8_t ledid,uint16_t BrightFrame,uint16_t OffFrame)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETBLINK>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETBLINK;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETBLINK/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETBLINK;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = 1;
    Buf->req.MultW.Data[2] = BrightFrame>>8;
    Buf->req.MultW.Data[3] = BrightFrame;
    Buf->req.MultW.Data[4] = OffFrame>>8;
    Buf->req.MultW.Data[5] = OffFrame;
    return Calculating(Buf,ledid,C1PBYTE_SETBLINK+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_BlinkOff(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETBLINK>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETBLINK;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETBLINK/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETBLINK;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = 0;
    Buf->req.MultW.Data[2] = 0;
    Buf->req.MultW.Data[3] = 0;
    Buf->req.MultW.Data[4] = 0;
    Buf->req.MultW.Data[5] = 0;
    return Calculating(Buf,ledid,C1PBYTE_SETBLINK+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_DeltBlinkOn(LED_Pack_t *Buf,uint8_t ledid,uint16_t BrightFrame,uint16_t OffFrame)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_DELTBLINK>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_DELTBLINK;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_DELTBLINK/2;
    Buf->req.MultW.ByteCount = C1PBYTE_DELTBLINK;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = 1;
    Buf->req.MultW.Data[2] = BrightFrame>>8;
    Buf->req.MultW.Data[3] = BrightFrame;
    Buf->req.MultW.Data[4] = OffFrame>>8;
    Buf->req.MultW.Data[5] = OffFrame;
    return Calculating(Buf,ledid,C1PBYTE_DELTBLINK+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_DeltBlinkOff(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_DELTBLINK>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_DELTBLINK;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_DELTBLINK/2;
    Buf->req.MultW.ByteCount = C1PBYTE_DELTBLINK;
    Buf->req.MultW.Data[0] = 0;
    Buf->req.MultW.Data[1] = 0;
    Buf->req.MultW.Data[2] = 0;
    Buf->req.MultW.Data[3] = 0;
    Buf->req.MultW.Data[4] = 0;
    Buf->req.MultW.Data[5] = 0;
    return Calculating(Buf,ledid,C1PBYTE_DELTBLINK+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetScrollTime(LED_Pack_t *Buf,uint8_t ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETSCROLLTIME>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETSCROLLTIME;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETSCROLLTIME/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETSCROLLTIME;
    Buf->req.MultW.Data[0] = PauseTime>>8;;
    Buf->req.MultW.Data[1] = PauseTime;
    Buf->req.MultW.Data[2] = MoveTime>>8;
    Buf->req.MultW.Data[3] = MoveTime;
    Buf->req.MultW.Data[4] = StageTime>>24;
    Buf->req.MultW.Data[5] = StageTime>>16;
    Buf->req.MultW.Data[6] = StageTime>>8;
    Buf->req.MultW.Data[7] = StageTime;
    return Calculating(Buf,ledid,C1PBYTE_SETSCROLLTIME+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_DeltScrollTime(LED_Pack_t *Buf,uint8_t ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_DELTSCROLLTIME>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_DELTSCROLLTIME;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_DELTSCROLLTIME/2;
    Buf->req.MultW.ByteCount = C1PBYTE_DELTSCROLLTIME;
    Buf->req.MultW.Data[0] = PauseTime>>8;;
    Buf->req.MultW.Data[1] = PauseTime;
    Buf->req.MultW.Data[2] = MoveTime>>8;
    Buf->req.MultW.Data[3] = MoveTime;
    Buf->req.MultW.Data[4] = StageTime>>24;
    Buf->req.MultW.Data[5] = StageTime>>16;
    Buf->req.MultW.Data[6] = StageTime>>8;
    Buf->req.MultW.Data[7] = StageTime;
    return Calculating(Buf,ledid,C1PBYTE_DELTSCROLLTIME+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetScrollStyle(LED_Pack_t *Buf,uint8_t ledid,uint32_t scrollStyle)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETSCROLLSTYLE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETSCROLLSTYLE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETSCROLLSTYLE/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETSCROLLSTYLE;
    Buf->req.MultW.Data[3] = scrollStyle>>24;
    Buf->req.MultW.Data[2] = scrollStyle>>16;
    Buf->req.MultW.Data[1] = scrollStyle>>8;
    Buf->req.MultW.Data[0] = scrollStyle;
    return Calculating(Buf,ledid,C1PBYTE_SETSCROLLSTYLE+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_DeltScrollStyle(LED_Pack_t *Buf,uint8_t ledid,uint32_t scrollStyle)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_DELTSCROLLSTYLE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_DELTSCROLLSTYLE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_DELTSCROLLSTYLE/2;
    Buf->req.MultW.ByteCount = C1PBYTE_DELTSCROLLSTYLE;
    Buf->req.MultW.Data[3] = scrollStyle>>24;
    Buf->req.MultW.Data[2] = scrollStyle>>16;
    Buf->req.MultW.Data[1] = scrollStyle>>8;
    Buf->req.MultW.Data[0] = scrollStyle;
    return Calculating(Buf,ledid,C1PBYTE_DELTSCROLLSTYLE+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetPixelSize(LED_Pack_t *Buf,uint8_t ledid,uint16_t Width,uint16_t Height)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETPIXELSIZE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETPIXELSIZE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETPIXELSIZE/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETPIXELSIZE;
    C1X_WriteKey(Buf->req.MultW.Data,0);
    Buf->req.MultW.Data[4] = Width>>8;
    Buf->req.MultW.Data[5] = Width;
    Buf->req.MultW.Data[6] = Height>>8;
    Buf->req.MultW.Data[7] = Height;
    return Calculating(Buf,ledid,C1PBYTE_SETPIXELSIZE+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetLineFont(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint16_t Width,uint16_t Height)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETLINEFONT>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETLINEFONT;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETLINEFONT/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETLINEFONT;
    C1X_WriteKey(Buf->req.MultW.Data,0);
    Buf->req.MultW.Data[4] = lineNo>>8;
    Buf->req.MultW.Data[5] = lineNo;
    Buf->req.MultW.Data[6] = Width>>8;
    Buf->req.MultW.Data[7] = Width;
    Buf->req.MultW.Data[8] = Height>>8;
    Buf->req.MultW.Data[9] = Height;
    return Calculating(Buf,ledid,C1PBYTE_SETLINEFONT+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_DeltLineFont(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint16_t Width,uint16_t Height)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_DELTLINEFONT>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_DELTLINEFONT;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_DELTLINEFONT/2;
    Buf->req.MultW.ByteCount = C1PBYTE_DELTLINEFONT;
    C1X_WriteKey(Buf->req.MultW.Data,0);
    Buf->req.MultW.Data[4] = lineNo>>8;
    Buf->req.MultW.Data[5] = lineNo;
    Buf->req.MultW.Data[6] = Width>>8;
    Buf->req.MultW.Data[7] = Width;
    Buf->req.MultW.Data[8] = Height>>8;
    Buf->req.MultW.Data[9] = Height;
    return Calculating(Buf,ledid,C1PBYTE_DELTLINEFONT+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetSelfCheck(LED_Pack_t *Buf,uint8_t ledid,uint8_t showTime,bool isShowID,bool isShowVer,bool IsShowMsg)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETSELFCHECK>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETSELFCHECK;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETSELFCHECK/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETSELFCHECK;
    C1X_WriteKey(Buf->req.MultW.Data,0);
    Buf->req.MultW.Data[4] = showTime;
    Buf->req.MultW.Data[5] = isShowID;
    Buf->req.MultW.Data[6] = isShowVer;
    Buf->req.MultW.Data[7] = IsShowMsg;
    return Calculating(Buf,ledid,C1PBYTE_SETSELFCHECK+MODBUS_MULTW_MINBYTE);
}

uint8_t PackInit_SetScanMode(LED_Pack_t *Buf,uint8_t ledid,const LED_ScanMode_t *ledpolar)
{
    Buf->req.function_code = MODBUS_WRITE_MULTHOLD_REGISTER;
    Buf->req.MultW.AddrHi = C1PCMD_SETSCANMODE>>8;
    Buf->req.MultW.AddrLi = (uint8_t)C1PCMD_SETSCANMODE;
    Buf->req.MultW.QuantityHi = 0;
    Buf->req.MultW.QuantityLi = C1PBYTE_SETSCANMODE/2;
    Buf->req.MultW.ByteCount = C1PBYTE_SETSCANMODE;
    C1X_WriteKey(Buf->req.MultW.Data,0);
    memcpy(&Buf->req.MultW.Data[4],ledpolar,sizeof(LED_ScanMode_t));
    return Calculating(Buf,ledid,C1PBYTE_SETSCANMODE+MODBUS_MULTW_MINBYTE);
}

int8_t PackInit_RCVData2SDK(const unsigned char *pData,uint8_t dataSize)
{
    const Modbus_Excep *packet = (const Modbus_Excep *)pData;
		uint16_t crc16;
    if (dataSize<=MBADU_MINSIZE)
        return SDK_RECEIVE_LENGTHERROR;
    crc16 = *(pData+dataSize-2);
    crc16 += *(pData+dataSize-1)<<8;
    if (crc16 != CRC16_Modbus(pData,dataSize-2))
    {
        return SDK_RECEIVE_CHECKERROR;
    }
    if (packet->esp.function_code >= 0x80)
    {
        switch (packet->esp.exception_code)
        {
        case MBEC_INVALIDADDRESS:
            return SDK_RECEIVE_ADDRESSERROR;
            break;
        case MBEC_INVALIDFUNCTION:
            return SDK_RECEIVE_FUNCTIONUNDEFINED;
            break;
        case MBEC_INVALIDDATA:
            return SDK_RECEIVE_DATAERROR;
            break;
        default:
            return SDK_RECEIVE_UNKNOWN;
            break;
        }
    }
    else
    {
        return SDK_RECEIVE_OK;
    }
    return SDK_RECEIVE_UNKNOWN;
}


uint16_t CRC16_Modbus(const uint8_t *ptr,uint8_t len)
{
    uint16_t crc = 0xFFFF;
    uint8_t i;
    while(len--)
    {
        crc ^= *ptr;
        for(i=0; i<8; i++)
        {
            if(crc&1)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
        ptr++;
    }
    return(crc);
}

