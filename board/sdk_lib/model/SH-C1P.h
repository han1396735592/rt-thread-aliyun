#ifndef __SH_C1P_H_INCLUDED
#define __SH_C1P_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief SH-C1P 函数及宏定义。(源文件模式使用)
  *******************************************************************************
  * @note 本文件及对应的源文件(SH-C1P.c)供SDK源文件模式时使用，如果使用DLL模式无需关注此文件。 \n
  本文件及对应的源文件适用于 Windows 平台与单片机项目中。
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

#include "LEDSDK.h"
#include "..\GPL\Modbus_RTU.h"

//#define C1X_RCVSIZE         (1)

#ifndef LEDResPack_Size
#define LEDResPack_Size     (LEDPack_Size) /**< LED响应数据包大小 */
#endif // LEDResPack_Size




#define C1X_WriteKey(_buf,_bytecount)   { \
                                            _buf[(_bytecount)] = 0x14; \
                                            _buf[(_bytecount)+1] = 0xB4; \
                                            _buf[(_bytecount)+2] = 0xf8; \
                                            _buf[(_bytecount)+3] = 0x94; \
                                        }

typedef struct C1P_LineCmd_t
{
    /** @brief  行号 */
    uint8_t LineNo;
    /** @brief  行指令 */
    uint8_t LineCMD;

    /** @brief  行数据数组 */
    uint8_t LineParam[250];
}
C1P_LineCmd_t;


enum
{
    C1PCMD_SETSCANMODE    = 0x2328, /**< 设置扫描方式 */
    C1PCMD_SETPIXELSIZE    = 0x2338, /**< 设置屏像素大小 */
    C1PCMD_FACTORYRESET    = 0x270A, /**< 恢复出厂设置 */
    C1PCMD_RESET    = 0x2706, /**< 软件重启LED */
    C1PCMD_SETSELFCHECK    = 0x2348, /**< 设置开机自检 */
    C1PCMD_ENTERDOWNMODE    = 0x2358, /**< 进入字体或图片下载模式 */
    C1PCMD_BRIGTH    = 0x2368, /**< 亮度设置 */
    C1PCMD_CHANGEID    = 0x236C, /**< 机号(地址)设置 */
    C1PCMD_BRUSHCOLOR    = 0x2370, /**< 缓存画笔颜色 */
    C1PCMD_DELTBRUSH    = 0x2372, /**< 开机默认画笔颜色 */
    C1PCMD_SETLINEFONT    = 0x2380, /**< 文字缓存字体设置 */
    C1PCMD_DELTLINEFONT    = 0x2390, /**< 文字开机默认字体设置 */
    C1PCMD_SETALIGN    = 0x2376, /**< 图片或文本缓存对齐方式 */
    C1PCMD_DELTALIGN    = 0x2378, /**< 图片或文本默认对齐方式 */
    C1PCMD_SETBLINK    = 0x23A0, /**< 闪烁设置（缓存） */
    C1PCMD_DELTBLINK    = 0x23A8, /**< 闪烁设置（开机默认） */
    C1PCMD_SETSCROLLTIME    = 0x23B8, /**< 滚动时间设置（缓存） */
    C1PCMD_DELTSCROLLTIME    = 0x23C0, /**< 滚动时间设置（开机默认） */
    C1PCMD_SETSCROLLSTYLE    = 0x23D0, /**< 滚动样式设置（缓存） */
    C1PCMD_DELTSCROLLSTYLE    = 0x23D8, /**< 滚动样式设置（开机默认） */
    C1PCMD_CLEARCREEN    = 0x23E8, /**< 清屏指令 */
    C1PCMD_LINE    = 0x2428, /**< 多行显示命令集 */
};

enum
{
    C1PLINE_SHOWGBK = 0x01,                     /**< 行命令--显示GBK编码 */
    C1PLINE_SHOWUNICODE = 0x02,                 /**< 行命令--显示UNICODE编码 */
    C1PLINE_BOOTGBK = 0x20,                     /**< 行命令--设置开机时显示GBK编码文字 */
    C1PLINE_BOOTUNICODE = 0x21,                 /**< 行命令--设置开机时显示UNICODE编码文字 */
    C1PLINE_EMOGBK = 0x30,                      /**< 行命令--应急信息时显示GBK编码文字 */
    C1PLINE_EMOUNICODE = 0x31,                  /**< 行命令--应急信息时显示UNICODE编码文字 */
    C1PLINE_SHOWIMAGE = 0x08,                   /**< 行命令--显示图片  */
    C1PLINE_BOOTIMAGE = 0x28,                   /**< 行命令--开机时显示图片  */
    C1PLINE_EMOIMAGE = 0x38,                    /**< 行命令--应急信息时显示图片  */
};


extern uint16_t CRC16_Modbus(const uint8_t *ptr,uint8_t len);

#define C1PBYTE_SETALIGN    (2)                     /**< 对齐方式设置 */
#define C1PBYTE_DELTALIGN   (2)   /**< 开机默认对齐方式设置 */
#define C1PBYTE_BRUSHCOLOR      (2)     /**< 画笔颜色 */
#define C1PBYTE_DELTBRUSH       (2)     /**< 开机时默认画笔颜色 */
#define C1PBYTE_SETPIXELSIZE    (8)     /**< 屏像素大小设置 */
#define C1PBYTE_SETSCANMODE     (10)    /**< 设置扫描方式 */
#define C1PBYTE_FACTORYRESET    (4)     /**< 恢复出厂设置 */
#define C1PBYTE_RESET           (4)     /**< 重启控制卡 */
#define C1PBYTE_SETSELFCHECK    (8)     /**< 开机自检设置 */
#define C1PBYTE_ENTERDOWNMODE   (8)     /**< 进入下载模式 */
#define C1PBYTE_BRIGTH          (2)     /**< 亮度设置 */
#define C1PBYTE_CHANGEID        (2)     /**< 修改机号 */

#define C1PBYTE_SETLINEFONT     (10)            /**< 设定指定行的字体 */
#define C1PBYTE_DELTLINEFONT    (10)            /**< 设定指定行开机默认字体 */
#define C1PBYTE_SETBLINK        (6)             /**< 闪烁设置 */
#define C1PBYTE_DELTBLINK       (6)             /**< 开机默认闪烁设置 */
#define C1PBYTE_SETSCROLLTIME   (8)             /**< 滚动设置时间 */
#define C1PBYTE_DELTSCROLLTIME  (8)             /**< 开机默认滚动设置时间*/
#define C1PBYTE_CLEARCREEN      (4)           /**< 清屏 */
#define C1PBYTE_SETSCROLLSTYLE  (4)            /**< 滚动设置风格 */
#define C1PBYTE_DELTSCROLLSTYLE (4)            /**< 开机默认滚动设置风格*/


#ifdef __cplusplus
}
#endif



#endif // __SH-C1X_H_INCLUDED
