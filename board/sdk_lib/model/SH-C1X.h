#ifndef __SH_C1X_H_INCLUDED
#define __SH_C1X_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief SH-C1X、SH-C1T 函数及宏定义。(源文件模式使用)
  *******************************************************************************
  * @note 本文件及对应的源文件(SH-C1X.c)供SDK源文件模式时使用，如果使用DLL模式无需关注此文件。 \n
  本文件及对应的源文件适用于 Windows 平台与单片机项目中。 \n
  如果选用了不带ID的协议(如SH-C1X)，SDK函数调用需要ledid参数时，任意传入一个数字。
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SH_C1T
#   ifndef USE_PACT_ID
#       define USE_PACT_ID
#   endif // USE_PACT_ID
#   define LEDPack_Min     (7) /**< 完整数据包最小长度，SH-C1T为7，SH-C1X为6 */

#   if (LEDPack_Size<=(LEDPack_Min))
#       error  "LEDPack_Size can not be less than 8 "
#   endif
#endif // SH_C1T

#ifdef SH_C1X
#   define LEDPack_Min     (6) /**< 完整数据包最小长度，SH-C1T为7，SH-C1X为6 */
#   if (LEDPack_Size<=(LEDPack_Min))
#       error  "LEDPack_Size can not be less than 7 "
#   endif
#endif // SH_C1T

typedef struct C1T_LineCmd_t
{
    /** @brief  行号 */
    uint8_t LineNo;
    /** @brief  行指令 */
    uint8_t LineCMD;

    /** @brief  行数据数组 */
    uint8_t LineParam[LEDPack_Size-LEDPack_Min];
}
C1T_LineCmd_t;


/** @brief SH-C1T 数据包结构体 -- 最大256个字节 */
typedef struct C1T_Pack_t
{
    /** @brief 数据包头 */
    uint8_t Head;
    /** @brief 数据包长度 */
    uint8_t Length;
    /** @brief 数据包长度校验 */
    uint8_t LenCheck;
    /** @brief 机号 */
    uint8_t id;
    /** @brief 命令(指令编码) */
    uint8_t CMD;

    /** @brief 指令参数数组 */
    uint8_t Param[LEDPack_Size-7+2];
}
C1T_Pack_t;

/** @brief  SH-C1X 数据包结构体 -- 最大256个字节 */
typedef struct C1X_Pack_t
{
    /** @brief 数据包头 */
    uint8_t Head;
    /** @brief 数据包长度 */
    uint8_t Length;
    /** @brief 数据包长度校验 */
    uint8_t LenCheck;
    /** @brief 命令(指令编码) */
    uint8_t CMD;
    /** @brief 指令参数数组 */
    uint8_t Param[LEDPack_Size-6+2];

}
C1X_Pack_t;

#define C1X_RCVSIZE         (1) /**< LED数据包返回值大小 */




#define C1X_WriteKey(_buf,_bytecount)   { \
                                            _buf[(_bytecount)] = 0x14; \
                                            _buf[(_bytecount)+1] = 0xB4; \
                                            _buf[(_bytecount)+2] = 0xf8; \
                                            _buf[(_bytecount)+3] = 0x94; \
                                        }


/** @brief LED指令编码 枚举 */
enum
{
    C1XCMD_BRUSHCOLOR = 0x56,                   /**< 画笔颜色 */
    C1XCMD_DELTBRUSH = 0x80+C1XCMD_BRUSHCOLOR,  /**< 开机时默认画笔颜色 */
    C1XCMD_LINE = 0x5c,                         /**< LED行指令 */
    C1XCMD_BRIGTH = 0x43,                       /**< 亮度设置 */
    C1XLINE_SHOWGBK = 0x01,                     /**< 行命令--显示GBK编码 */
    C1XLINE_SHOWUNICODE = 0x02,                 /**< 行命令--显示UNICODE编码 */
    C1XLINE_BOOTGBK = 0x20,                     /**< 行命令--设置开机时显示GBK编码文字 */
    C1XLINE_BOOTUNICODE = 0x21,                 /**< 行命令--设置开机时显示UNICODE编码文字 */
    C1XLINE_EMOGBK = 0x30,                      /**< 行命令--应急信息时显示GBK编码文字 */
    C1XLINE_EMOUNICODE = 0x31,                  /**< 行命令--应急信息时显示UNICODE编码文字 */
    C1XLINE_SHOWIMAGE = 0x08,                   /**< 行命令--显示图片  */
    C1XLINE_BOOTIMAGE = 0x28,                   /**< 行命令--开机时显示图片  */
    C1XLINE_EMOIMAGE = 0x38,                    /**< 行命令--应急信息时显示图片  */

    C1XCMD_FACTORYRESET = 0x9e,                 /**< 恢复出厂设置 */
    C1XCMD_RESET = 0x99,                        /**< 重启控制卡 */
    C1XCMD_CLEARCREEN = 0x63,                   /**< 清屏 */
    C1XCMD_CHANGEID = 0x21,                     /**< 修改机号 */

    C1XCMD_SETALIGN = 0x6a,                     /**< 对齐方式设置 */
    C1XCMD_DELTALIGN = 0x80+C1XCMD_SETALIGN,    /**< 开机默认对齐方式设置 */

    C1XCMD_SETBLINK = 0x61,                     /**< 闪烁设置 */
    C1XCMD_DELTBLINK = 0x80+C1XCMD_SETBLINK,    /**< 开机默认闪烁设置 */

    C1XCMD_SETPIXELSIZE = 0x9c,                 /**< 屏像素大小设置 */
    C1XCMD_SETSCANMODE = 0x9d,                  /**< 设置扫描方式 */
    C1XCMD_SETSELFCHECK = 0x9f,                 /**< 开机自检设置 */

    C1XCMD_SETSCROLLTIME = 0x65,                /**< 滚动设置时间 */
    C1XCMD_DELTSCROLLTIME =
        0x80+C1XCMD_SETSCROLLTIME,              /**< 开机默认滚动设置时间*/

    C1XCMD_SETSCROLLSTYLE = 0x66,               /**< 滚动设置风格 */
    C1XCMD_DELTSCROLLSTYLE =
        0x80+C1XCMD_SETSCROLLSTYLE,             /**< 开机默认滚动设置风格*/

    C1XCMD_SETLINEFONT = 0x69,                  /**< 设定指定行的字体 */
    C1XCMD_DELTLINEFONT =
        0x80+C1XCMD_SETLINEFONT,                /**< 设定指定行开机默认字体 */

    C1XCMD_ENTERDOWNMODE = 0x58,                /**< 进入下载模式 */
    C1XCMD_VOICE = 0x56,                        /**< 语音命令 */
    C1XCMD_VOTEXT = 0x71,                       /**< 读语音并显示出来 */


    C1XCMD_QUICKWRITEDISPMEM = 0x80,    /**< 显存快速写入 */

};

/** @brief LED返回值 枚举 */
enum
{
    C1X_TREACT_OK           = 0x0f, /**< LED返回值，操作成功 */
    C1X_ERROR_CHECK         = 0xf0, /**< LED返回值，校验错误 */
    C1X_ERROR_UNCMD         = 0xf1, /**< LED返回值，未定义的命令 */
    C1X_ERROR_LINETH        = 0xf2, /**< LED返回值，数据包长度错误 */
    C1X_ERROR_DATA          = 0xf3, /**< LED返回值，数据包数据错误 */
};


#ifdef __cplusplus
}
#endif



#endif // __SH-C1X_H_INCLUDED
