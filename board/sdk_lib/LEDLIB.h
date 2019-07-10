#ifndef LED_LEDLIB_H_INCLUDED
#define LED_LEDLIB_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief SDK 数据包发送操作库(嵌入式平台)
  ******************************************************************************
  * @note 本文件只适用于 嵌入式平台。 \n
  如果选用了不带ID的协议(如SH-C1X)，SDK函数调用需要ledid参数时，任意传入一个数字。
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------
// 全局宏定义
//---------------------------------------------------------------------



//---------------------------------------------------------------------

#ifndef LEDPack_Size
#   define LEDPack_Size (256)
#endif // LEDPack_Size

#if (defined SH_C1T)//LED 型号
#   if (LEDPack_Size>256)
#       error  "LEDPack_Size can not be greater than 256 "
#   endif
#elif (defined SH_C1X)
#   if (LEDPack_Size>256)
#       error  "LEDPack_Size can not be greater than 256 "
#   endif
#elif (defined SH_C1P)
#   if (LEDPack_Size>256)
#       error  "LEDPack_Size can not be greater than 256 "
#   endif
#   if (LEDPack_Size < 11)
#       error  "LEDPack_Size can not be less than 11 "
#   endif
#else
#    error "LED model is not defined"
#endif


#include "PackInit.h"


/** \brief LED 接收数据函数,该函数需要用户来实现
 *
 * \param outtime 等待超时时间(ms)
 * \return extern int 将LED接收到的数据经过 PackInit_RCVData2SDK 转换 后返回。该值也是 LED命令发送函数的返回值。(LED_*****,@ref LED_SendPack)
 *
 */
extern int LED_ReceiveData(uint16_t outtime);

/** \brief LED 发送数据包,该函数需要用户来实现
 *
 * \param pBuf 要发送的数据包指针
 * \param BufSize 要发送的字节数
 * \return extern 已发送的字节数
 *
 */
extern uint16_t LED_SendData(const uint8_t *pBuf,size_t BufSize);


/** \brief 调用SDK,设置接收超时时间
 * \note 未调用此函数是，默认 接收超时 时间为 100ms。 \n  调用SDK函数发送数据包时（非广播模式时），
 等待LED返回数据，如果在 接收超时 内收到返回数据函数提前返回。如果等待超时函数返回 @ref SDK_RECEIVE_OUTTIME 。 \n
 如果 接收超时 设置为0，表示不接收LED返回数据。数据包发送完成后返回 @ref SDK_SEND_NOTRECEIVE  。
 * \param outtime 超时时间，单位ms。(建议设置大于100)
 */
void DLL_EXPORT LED_SetReceiveTimeout(unsigned int outtime);

/** \brief 调用SDK，发送一个数据包
 *
 * \param ledid LED地址(id)
 * \param pBuf 要发送的数据包指针
 * \param sendByte 数据包中要发送的字节数
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SendPack(unsigned char ledid,const char *pBuf,int sendByte);

/** \brief 调用SDK,设置LED画笔颜色。(后面命令显示文字的颜色，不改变现在显示的内容)
 * \param ledid LED地址(id)
 * \param ledcolour 颜色值。指定颜色值：
    - 1 ：红色。
    - 2 ：绿色。
    - 3 ：黄色。
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetBrushColour(unsigned char ledid,unsigned char ledcolour);

/** \brief 调用SDK,设置LED开机时,画笔颜色(开机后调用 @ref LED_SetBrushColour 改变颜色)
 * \param ledid LED地址(id)
 * \param ledcolour 颜色值。指定颜色值：
    - 1 ：红色。
    - 2 ：绿色。
    - 3 ：黄色。
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltBrushColour(unsigned char ledid,unsigned char ledcolour);

/** \brief 调用SDK,显示GBK编码的文字
 *
 * \param ledid LED地址(id)
 * \param lineNo 要显示的行号
 * \param str 要显示的字符串
 * \return int @ref SDK_RECEIVE_e
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_ShowGBK(unsigned char ledid,unsigned char lineNo,const char *str);


#if (defined SH_C1X)||(defined SH_C1T)

/** \brief 调用SDK,快速写入显存
 *
 * \param ledid LED地址(id)
 * \param Xpos X坐标
 * \param Ypos Y坐标
 * \param Pixel 要写入的像素点数
 * \param PixelBuf 要写入的像素值
 * \return int @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_QuickWriteDisp(uint8_t ledid,uint16_t Xpos,uint16_t Ypos,uint16_t Pixel,const uint8_t *PixelBuf);

#endif


/** \brief 调用SDK,设置GBK编码的开机默认文字
 *
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param str 要设置的字符串
 * \return int @ref SDK_RECEIVE_e
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_SetBootGBK(unsigned char ledid,unsigned char lineNo,const char *str);

/** \brief 调用SDK,显示unicode编码的文字
 *
 * \param ledid LED地址(id)
 * \param lineNo 要显示的行号
 * \param wstr 要显示的字符串
 * \return int @ref SDK_RECEIVE_e
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_ShowUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief 调用SDK,设置GBK编码的应急信息
 *
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param str 要设置的字符串
 * \return int @ref SDK_RECEIVE_e
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_SetEmergGBK(unsigned char ledid,unsigned char lineNo,const char *str);

/** \brief 调用SDK,设置unicode编码的应急信息
 *
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param wstr 要设置的字符串
 * \return int @ref SDK_RECEIVE_e
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_SetEmergUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief 调用SDK,设置unicode编码的开机默认文字
 *
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param wstr 要设置的字符串
 * \return int @ref SDK_RECEIVE_e
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_SetBootUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief 调用SDK,设置LED亮度
 *
 * \param ledid LED地址(id)
 * \param brigth 亮度值 (详见 @ref LED_BRIGTH_e )
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetBrigth(unsigned char ledid,unsigned char brigth);

/** \brief 调用SDK,设置LED恢复出厂设置
 *
 * \param ledid LED地址(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_FactoryReset(unsigned char ledid);


/** \brief 调用SDK，执行清屏操作
 *
 * \param ledid LED地址(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_ClearScreen(unsigned char ledid);

/** \brief 调用SDK，清指定行的内容
 *
 * \param ledid LED地址(id)
 * \param lineNo 要清除的行号
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_ClearLine(unsigned char ledid,unsigned char lineNo);

/** \brief 调用SDK，重启LED
 *
 * \param ledid LED地址(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_Reset(unsigned char ledid);

/** \brief 调用SDK，设置LED开机时默认文字对齐方式
 *
 * \param ledid LED地址(id)
 * \param align 对齐方式。 详见 @ref LED_ALIGN_e
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetDeltAlign(unsigned char ledid,unsigned char align);

 /** \brief 调用SDK，设置指定行开机时默认文字对齐方式
 *
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param align 对齐方式。 详见 @ref LED_ALIGN_e
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetDeltAlignLine(unsigned char ledid,unsigned char lineNo,unsigned char align);

/** \brief 调用SDK，设置文字对齐方式
 *
 * \param ledid LED地址(id)
 * \param align 对齐方式。 详见 @ref LED_ALIGN_e
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetAlign(unsigned char ledid,unsigned char align);

 /** \brief 调用SDK，设置指定行文字对齐方式
 *
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param align 对齐方式。 详见 @ref LED_ALIGN_e
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetAlignLine(unsigned char ledid,unsigned char lineNo,unsigned char align);


/** \brief 调用SDK，打开闪烁功能
 *
 * \param ledid LED地址(id)
 * \param BrightTiem LED亮的时间(ms)
 * \param OffTiem LED灭的时间(ms)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_BlinkOn(unsigned char ledid,uint16_t BrightTiem,uint16_t OffTiem);

/** \brief 调用SDK，关闭闪烁功能
 *
 * \param ledid LED地址(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_BlinkOff(unsigned char ledid);

/** \brief 调用SDK，打开开机默认闪烁功能
 *
 * \param ledid LED地址(id)
 * \param BrightTiem LED亮的时间(ms)
 * \param OffTiem LED灭的时间(ms)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltBlinkOn(unsigned char ledid,uint16_t BrightTiem,uint16_t OffTiem);

/** \brief 调用SDK，关闭开机默认闪烁功能
 *
 * \param ledid LED地址(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltBlinkOff(unsigned char ledid);

/** \brief 调用SDK，设置滚动时间
 * \note 当 MoveTime 和 PauseTime 都为0时表示不滚动。
 * \param ledid LED地址(id)
 * \param MoveTime 滚动速度(ms)
 * \param PauseTime 停留时间(ms)
 * \param StageTime 段落时间(ms)(一行显示多段信息时使用),不使用时传入0
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetScrollTime(unsigned char ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime);

/** \brief 调用SDK，设置开机默认滚动时间
 * \note 当 MoveTime 和 PauseTime 都为0时表示不滚动。
 * \param ledid LED地址(id)
 * \param MoveTime 滚动速度(ms)
 * \param PauseTime 停留时间(ms)
 * \param StageTime 段落时间(ms)(一行显示多段信息时使用),不使用时传入0
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltScrollTime(unsigned char ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime);


/** \brief 调用SDK，设置滚动风格
 *
 * \param ledid LED地址(id)
 * \param scrollStyle 样式，详见 @ref LED_ScrollStyle_t
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetScrollStyle(unsigned char ledid,uint32_t scrollStyle);


/** \brief 调用SDK，设置开机默认滚动风格
 *
 * \param ledid LED地址(id)
 * \param scrollStyle 样式，详见 @ref LED_ScrollStyle_t
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltScrollStyle(unsigned char ledid,uint32_t scrollStyle);


/** \brief 调用SDK，设置LED像素大小
 * \note 像素的宽和高都不能超过LED所支持的像素
 * \param ledid LED地址(id)
 * \param Width LED宽(像素点)
 * \param Height LED高(像素点)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetPixelSize(unsigned char ledid,uint16_t Width,uint16_t Height);

/** \brief 调用SDK，设置LED扫描方式
 * \note 设置LED扫描方式和数据信号极性。
 * \param ledid LED地址(id)
 * \param ledpolar 数据信号结构体指针。  @ref LED_ScanMode_t
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetScanMode(unsigned char ledid,const LED_ScanMode_t *ledpolar);

/** \brief 调用SDK，按模组名称设置LED扫描方式
 * \param ledid LED地址(id)
 * \param moduleName 模组名称。
 * \return int @ref SDK_RECEIVE_e
 * \note  模组名称规则： “P” + “间距” + “颜色” + “扩展” 。如 “P10”，“P3.75D”
    - P ：大写字母 “P” 开头。
    - 间距 ：模组的像素间距(mm)。
    - 颜色：(单红为空)
        -# 双色：大写字母 D
        -# 全彩：大写字母 A
    - 扩展：(可为空)
        -# E：全户外模组。
 *
 */
int DLL_EXPORT LED_SetModule(unsigned char ledid,const char *moduleName);

/** \brief 调用SDK，设置开机自检
 *
 * \param ledid LED地址(id)
 * \param showTime 自检显示时间(单位:秒),设置为0，表示不进行开机自检
 * \param isShowID 是否显示ID（如果协议支持ID）
 * \param isShowVer 是否显示固件版本号
 * \param IsShowMsg 开机后是否显示 "开机默认信息"
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetSelfCheck(unsigned char ledid,uint8_t showTime,bool isShowID,bool isShowVer,bool IsShowMsg);

/** \brief 调用SDK，修改LED ID（如果LED协议ID可用）
 *
 * \param ledid LED地址(id) （旧ID）
 * \param newid 新ID
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_ChangeID(unsigned char ledid,unsigned char newid);

/** \brief 调用SDK,使LED进入下载模式。
 * \note 下载波特率过低传输时间过长。波特率过高容易传输出错。大文件可设置为345600,小文件设置为 115200 。  \n
 进入下载模式后只能对LED下载数据（字体或图片），其它操作无效。 \n 要退出下载模式可手动重启LED设备。
 * \param ledid LED地址(id)
 * \param uintBaudrate: 下载时使用的波特率。
 * \param strProtocol: 下载时数据位与校验位及停止位设置。通常选 "8N1"
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_EnterDownMode(unsigned char ledid,unsigned int uintBaudrate,const char *strProtocol);

/** \brief 调用SDK，设置指定行开机时显示图片
 *
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param imageAddr 图片地址
 * \param Width 要显示的宽度，宽度为0时，显示整幅图片或按LED宽度来显示
 * \param Height 要显示的高度，高度为0时，显示整幅图片或按LED高度来显示
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetBootImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief 调用SDK，设置指定行应急信息时显示图片
 *
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param imageAddr 图片地址
 * \param Width 要显示的宽度，宽度为0时，显示整幅图片或按LED宽度来显示
 * \param Height 要显示的高度，高度为0时，显示整幅图片或按LED高度来显示
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetEmergImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief 调用SDK，设置指定行显示图片
 *
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param imageAddr 图片地址
 * \param Width 要显示的宽度，宽度为0时，显示整幅图片或按LED宽度来显示
 * \param Height 要显示的高度，高度为0时，显示整幅图片或按LED高度来显示
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_ShowImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief 调用SDK，设置指定行字体
 *
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param Width 字体宽度
 * \param Height 字体高度
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetLineFont(unsigned char ledid,uint8_t lineNo,uint16_t Width,uint16_t Height);

/** \brief 调用SDK，设置指定行开机默认字体
 *
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param Width 字体宽度
 * \param Height 字体高度
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltLineFont(unsigned char ledid,uint8_t lineNo,uint16_t Width,uint16_t Height);

/** \brief 调用SDK，发送自定义命令
 *
 * \param ledid LED地址(id)
 * \param customcmd 自定义命令的字符串(16进制)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_Custom(unsigned char ledid,const char *customcmd);

/** \brief 调SDK，对数据包初始化
 *
 * \param func 要对LED进行操作的名称
 * \param packbuf 数据包缓存(缓存大小为数据包结构体的大小,通常是256 Byte)
 * \param ledid LED地址(id)
 * \param argc 数据包参数的数量
 * \param argv[] 数据包参数的数组
 * \return int 初始化成功返回数据包有效长度，初始化失败返回 0
 *
 */
int DLL_EXPORT LED_PackInit(const char *func,void *packbuf,uint8_t ledid,int argc,const char* argv[]);


#ifdef __cplusplus
}
#endif

#endif // LED_SERIALPORT_H_INCLUDED
