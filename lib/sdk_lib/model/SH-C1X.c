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

#define BROADCAST_ID            (0xff) /**< 广播ID */
#define C1X_KEYWORD_HEAD        (0xa1) //包头关键字
#define C1X_KEYWORD_TAIL        (0x51)//包尾关键字

#ifdef USE_PACT_ID
#define SetLdeID(ledid)     Buf->id = ((ledid==SDK_BROADCAST)||(ledid==SDK_BROADCAST_OLD))?BROADCAST_ID:ledid
#else
#define SetLdeID(id)
#endif // USE_PACT_ID


static uint8_t Calculating(LED_Pack_t *Buf,uint8_t ledid,const uint8_t *Param,uint8_t ParaSize)
{
    uint8_t *pCheck;
    uint8_t Checksum = 0;
    uint8_t CheckSize;
    if ((uint16_t)ParaSize+LEDPack_Min > LEDPack_Size)
        return 0;

    SetLdeID(ledid);

    Buf->Head = C1X_KEYWORD_HEAD;

    Buf->Length = ParaSize+LEDPack_Min;
    Buf->LenCheck = ~Buf->Length;

    if (Param && ParaSize)
        memcpy(Buf->Param,Param,ParaSize);

    CheckSize = Buf->Length-2;
    pCheck = &Buf->Head;
    while(CheckSize--)
    {
        Checksum += *pCheck++;
    }
    *pCheck++ = Checksum; //写入校验和
    *pCheck = C1X_KEYWORD_TAIL;

    return Buf->Length;
}

uint8_t PackInit_SetBrushColour(LED_Pack_t *Buf,uint8_t ledid,uint8_t ledcolour)
{
    Buf->CMD = C1XCMD_BRUSHCOLOR;
    return Calculating(Buf,ledid,(const uint8_t *)&ledcolour,1);
}

uint8_t PackInit_DeltBrushColour(LED_Pack_t *Buf,uint8_t ledid,uint8_t ledcolour)
{
    Buf->CMD = C1XCMD_DELTBRUSH;
    return Calculating(Buf,ledid,(const uint8_t *)&ledcolour,1);
}



uint8_t PackInit_ShowGBK(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const char *str)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;
    int n  = strlen(str);

    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_SHOWGBK;
    if (n)
        memcpy(linecmd->LineParam,str,n);
    n += (int)(&linecmd->LineParam)-(int)(&linecmd->LineNo);
    return Calculating(Buf,ledid,0,n);
}

uint8_t PackInit_ShowUnicode(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const wchar_t *wstr)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;
    int n  = wcslen(wstr)*2;

    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_SHOWUNICODE;
    if (n)
        memcpy(linecmd->LineParam,wstr,n);
    n += (int) (&linecmd->LineParam)-(int)(&linecmd->LineNo);
    return Calculating(Buf,ledid,0,n);
}

uint8_t PackInit_SetBootGBK(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const char *str)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;
    int n  = strlen(str);

    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_BOOTGBK;
    if (n)
        memcpy(linecmd->LineParam,str,n);
    n += (int)(&linecmd->LineParam)-(int)(&linecmd->LineNo);
    return Calculating(Buf,ledid,0,n);
}

uint8_t PackInit_SetBootUnicode(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const wchar_t *wstr)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;
    int n  = wcslen(wstr)*2;

    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_BOOTUNICODE;
    if (n) memcpy(linecmd->LineParam,wstr,n);
    n += (int) (&linecmd->LineParam)-(int)(&linecmd->LineNo);
    return Calculating(Buf,ledid,0,n);
}

uint8_t PackInit_ShowImage(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;

    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_SHOWIMAGE;
    linecmd->LineParam[0] = imageAddr;
    linecmd->LineParam[1] = imageAddr>>8;
    linecmd->LineParam[2] = imageAddr>>16;
    linecmd->LineParam[3] = imageAddr>>24;
    linecmd->LineParam[4] = Width;
    linecmd->LineParam[5] = Width>>8;
    linecmd->LineParam[6] = Height;
    linecmd->LineParam[7] = Height>>8;
    return Calculating(Buf,ledid,0,8+(int)(&linecmd->LineParam)-(int)(&linecmd->LineNo));
}

uint8_t PackInit_SetBootImage(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;

    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_BOOTIMAGE;

    linecmd->LineParam[0] = imageAddr;
    linecmd->LineParam[1] = imageAddr>>8;
    linecmd->LineParam[2] = imageAddr>>16;
    linecmd->LineParam[3] = imageAddr>>24;
    linecmd->LineParam[4] = Width;
    linecmd->LineParam[5] = Width>>8;
    linecmd->LineParam[6] = Height;
    linecmd->LineParam[7] = Height>>8;

    return Calculating(Buf,ledid,0,8+(int)(&linecmd->LineParam)-(int)(&linecmd->LineNo));
}

uint8_t PackInit_QuickWriteDisp(LED_Pack_t *Buf,uint8_t ledid,uint16_t Xpos,uint16_t Ypos,uint16_t Pixel,const uint8_t *PixelBuf)
{
    uint8_t DatatSize = (Pixel+7)/8;
    Buf->CMD = C1XCMD_QUICKWRITEDISPMEM;
    Buf->Param[0] = Xpos;
    Buf->Param[1] = Xpos>>8;
    Buf->Param[2] = Ypos;
    Buf->Param[3] = Ypos>>8;
    Buf->Param[4] = Pixel;
    Buf->Param[5] = Pixel>>8;
    memcpy(&Buf->Param[6],PixelBuf,DatatSize);
    return Calculating(Buf,ledid,0,DatatSize+6);
}


uint8_t PackInit_SetEmergImage(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;

    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_EMOIMAGE;

    linecmd->LineParam[0] = imageAddr;
    linecmd->LineParam[1] = imageAddr>>8;
    linecmd->LineParam[2] = imageAddr>>16;
    linecmd->LineParam[3] = imageAddr>>24;
    linecmd->LineParam[4] = Width;
    linecmd->LineParam[5] = Width>>8;
    linecmd->LineParam[6] = Height;
    linecmd->LineParam[7] = Height>>8;

    return Calculating(Buf,ledid,0,8+(int)(&linecmd->LineParam)-(int)(&linecmd->LineNo));
}

uint8_t PackInit_SetEmergGBK(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const char *str)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;
    int n  = strlen(str);
    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_EMOGBK;
    if (n) memcpy(linecmd->LineParam,str,n);
    n += (int)(&linecmd->LineParam)-(int)(&linecmd->LineNo);
    return Calculating(Buf,ledid,0,n);
}

uint8_t PackInit_SetEmergUnicode(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,const wchar_t *wstr)
{
    C1T_LineCmd_t *linecmd = (C1T_LineCmd_t *)Buf->Param;
    int n  = wcslen(wstr)*2;
    Buf->CMD = C1XCMD_LINE;
    linecmd->LineNo = lineNo;
    linecmd->LineCMD = C1XLINE_EMOUNICODE;
    if (n) memcpy(linecmd->LineParam,wstr,n);
    n += (int) (&linecmd->LineParam)-(int)(&linecmd->LineNo);
    return Calculating(Buf,ledid,0,n);
}

uint8_t PackInit_SetBrigth(LED_Pack_t *Buf,uint8_t ledid,uint8_t brigth)
{
    Buf->CMD = C1XCMD_BRIGTH;
    return Calculating(Buf,ledid,(const uint8_t *)&brigth,1);
}

uint8_t PackInit_FactoryReset(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->CMD = C1XCMD_FACTORYRESET;
    C1X_WriteKey(Buf->Param,0);
    return Calculating(Buf,ledid,0,4);
}

uint8_t PackInit_ClearScreen(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->CMD = C1XCMD_CLEARCREEN;
    return Calculating(Buf,ledid,0,0);
}

uint8_t PackInit_ClearLine(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo)
{
    return PackInit_ShowGBK(Buf,ledid,lineNo," ");
}

uint8_t PackInit_Reset(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->CMD = C1XCMD_RESET;
    return Calculating(Buf,ledid,0,0);
}

uint8_t PackInit_ChangeID(LED_Pack_t *Buf,uint8_t ledid,uint8_t newid)
{
    Buf->CMD = C1XCMD_CHANGEID;
    return Calculating(Buf,ledid,(const uint8_t *)&newid,1);
}

uint8_t PackInit_SetAlign(LED_Pack_t *Buf,uint8_t ledid,uint8_t align)
{
    Buf->CMD = C1XCMD_SETALIGN;
    return Calculating(Buf,ledid,(const uint8_t *)&align,1);
}

uint8_t PackInit_SetAlignLine(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint8_t align)
{
    Buf->CMD = C1XCMD_SETALIGN;
    Buf->Param[0] = lineNo;
    Buf->Param[1] = align;
    return Calculating(Buf,ledid,0,2);
}

uint8_t PackInit_SetDeltAlignLine(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint8_t align)
{
    Buf->CMD = C1XCMD_DELTALIGN;
    Buf->Param[0] = lineNo;
    Buf->Param[1] = align;
    return Calculating(Buf,ledid,0,2);
}

uint8_t PackInit_SetDeltAlign(LED_Pack_t *Buf,uint8_t ledid,uint8_t align)
{
    Buf->CMD = C1XCMD_DELTALIGN;
    return Calculating(Buf,ledid,(const uint8_t *)&align,1);
}

uint8_t PackInit_BlinkOn(LED_Pack_t *Buf,uint8_t ledid,uint16_t BrightFrame,uint16_t OffFrame)
{
    Buf->CMD = C1XCMD_SETBLINK;
    Buf->Param[0] = 1;
    Buf->Param[1] = BrightFrame;
    Buf->Param[2] = BrightFrame>>8;
    Buf->Param[3] = OffFrame;
    Buf->Param[4] = OffFrame>>8;
    return Calculating(Buf,ledid,0,5);
}

uint8_t PackInit_BlinkOff(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->CMD = C1XCMD_SETBLINK;
    ZeroMemory(Buf->Param,5);
    return Calculating(Buf,ledid,0,5);
}

uint8_t PackInit_DeltBlinkOn(LED_Pack_t *Buf,uint8_t ledid,uint16_t BrightFrame,uint16_t OffFrame)
{
    Buf->CMD = C1XCMD_DELTBLINK;
    Buf->Param[0] = 1;
    Buf->Param[1] = BrightFrame;
    Buf->Param[2] = BrightFrame>>8;
    Buf->Param[3] = OffFrame;
    Buf->Param[4] = OffFrame>>8;
    return Calculating(Buf,ledid,0,5);
}

uint8_t PackInit_DeltBlinkOff(LED_Pack_t *Buf,uint8_t ledid)
{
    Buf->CMD = C1XCMD_DELTBLINK;
    ZeroMemory(Buf->Param,5);
    return Calculating(Buf,ledid,0,5);
}

uint8_t PackInit_SetScrollTime(LED_Pack_t *Buf,uint8_t ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime)
{
    Buf->CMD = C1XCMD_SETSCROLLTIME;
    Buf->Param[0] = PauseTime;
    Buf->Param[1] = PauseTime>>8;
    Buf->Param[2] = MoveTime;
    Buf->Param[3] = MoveTime>>8;
    Buf->Param[4] = StageTime;
    Buf->Param[5] = StageTime>>8;
    Buf->Param[6] = StageTime>>16;
    Buf->Param[7] = StageTime>>24;
    return Calculating(Buf,ledid,0,8);
}

uint8_t PackInit_DeltScrollTime(LED_Pack_t *Buf,uint8_t ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime)
{
    Buf->CMD = C1XCMD_DELTSCROLLTIME;
    Buf->Param[0] = PauseTime;
    Buf->Param[1] = PauseTime>>8;
    Buf->Param[2] = MoveTime;
    Buf->Param[3] = MoveTime>>8;
    Buf->Param[4] = StageTime;
    Buf->Param[5] = StageTime>>8;
    Buf->Param[6] = StageTime>>16;
    Buf->Param[7] = StageTime>>24;
    return Calculating(Buf,ledid,0,8);
}

uint8_t PackInit_SetScrollStyle(LED_Pack_t *Buf,uint8_t ledid,uint32_t scrollStyle)
{
    Buf->CMD = C1XCMD_SETSCROLLSTYLE;
    Buf->Param[0] = scrollStyle;
    Buf->Param[1] = scrollStyle>>8;
    Buf->Param[2] = scrollStyle>>16;
    Buf->Param[3] = scrollStyle>>24;
    return Calculating(Buf,ledid,0,4);
}

uint8_t PackInit_DeltScrollStyle(LED_Pack_t *Buf,uint8_t ledid,uint32_t scrollStyle)
{
    Buf->CMD = C1XCMD_DELTSCROLLSTYLE;
    Buf->Param[0] = scrollStyle;
    Buf->Param[1] = scrollStyle>>8;
    Buf->Param[2] = scrollStyle>>16;
    Buf->Param[3] = scrollStyle>>24;
    return Calculating(Buf,ledid,0,4);
}

uint8_t PackInit_SetPixelSize(LED_Pack_t *Buf,uint8_t ledid,uint16_t Width,uint16_t Height)
{
    Buf->CMD = C1XCMD_SETPIXELSIZE;
    C1X_WriteKey(Buf->Param,0);
    Buf->Param[4] = Width;
    Buf->Param[5] = Width>>8;
    Buf->Param[6] = Height;
    Buf->Param[7] = Height>>8;
    return Calculating(Buf,ledid,0,8);
}


uint8_t PackInit_SetLineFont(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint16_t Width,uint16_t Height)
{
    Buf->CMD = C1XCMD_SETLINEFONT;
    C1X_WriteKey(Buf->Param,0);
    Buf->Param[4] = lineNo;
    Buf->Param[5] = Width;
    Buf->Param[6] = Width>>8;
    Buf->Param[7] = Height;
    Buf->Param[8] = Height>>8;
    return Calculating(Buf,ledid,0,9);
}

uint8_t PackInit_DeltLineFont(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint16_t Width,uint16_t Height)
{
    Buf->CMD = C1XCMD_DELTLINEFONT;
    C1X_WriteKey(Buf->Param,0);
    Buf->Param[4] = lineNo;
    Buf->Param[5] = Width;
    Buf->Param[6] = Width>>8;
    Buf->Param[7] = Height;
    Buf->Param[8] = Height>>8;
    return Calculating(Buf,ledid,0,9);
}

uint8_t PackInit_SetSelfCheck(LED_Pack_t *Buf,uint8_t ledid,uint8_t showTime,bool isShowID,bool isShowVer,bool IsShowMsg)
{
    Buf->CMD = C1XCMD_SETSELFCHECK;
    C1X_WriteKey(Buf->Param,0);
    Buf->Param[4] = showTime;
    Buf->Param[5] = isShowID;
    Buf->Param[6] = isShowVer;
    Buf->Param[7] = IsShowMsg;
    return Calculating(Buf,ledid,0,8);
}

uint8_t PackInit_SetScanMode(LED_Pack_t *Buf,uint8_t ledid,const LED_ScanMode_t *ledpolar)
{
    Buf->CMD = C1XCMD_SETSCANMODE;
    C1X_WriteKey(Buf->Param,0);
    memcpy(&Buf->Param[4],ledpolar,sizeof(LED_ScanMode_t));
    return Calculating(Buf,ledid,0,sizeof(LED_ScanMode_t)+4);
}

int8_t PackInit_RCVData2SDK(const unsigned char *pData,uint8_t dataSize)
{
    switch((uint8_t)*pData)
    {
    case C1X_ERROR_UNCMD:
        return SDK_RECEIVE_FUNCTIONUNDEFINED;
        break;
    case C1X_ERROR_CHECK:
        return SDK_RECEIVE_CHECKERROR;
        break;
    case C1X_TREACT_OK:
        return SDK_RECEIVE_OK;
        break;
    case C1X_ERROR_LINETH:
        return SDK_RECEIVE_LENGTHERROR;
        break;
    case C1X_ERROR_DATA:
        return SDK_RECEIVE_DATAERROR;
        break;
    default:
        return SDK_RECEIVE_UNKNOWN;
        break;
    }
    return SDK_RECEIVE_UNKNOWN;
}

