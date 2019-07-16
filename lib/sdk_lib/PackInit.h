#ifndef __PACKINIT_H_INCLUDED
#define __PACKINIT_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief 对SDK 数据包初始化函数的定义
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

#include "GPL/GPL-string.h"
#include "LEDSDK.h"

#ifdef SH_C1X
#include "model/SH-C1X.h"
typedef  C1X_Pack_t LED_Pack_t;
#define LED_RCVSIZE C1X_RCVSIZE
#endif // SH_C1X

#ifdef SH_C1T
#include "model/SH-C1X.h"
typedef  C1T_Pack_t LED_Pack_t;
#define LED_RCVSIZE C1X_RCVSIZE
#endif // SH_C1T

#ifdef SH_C1P
#include "model/SH-C1P.h"
typedef  Modbus_ADU LED_Pack_t;
#define LED_RCVSIZE LEDResPack_Size
#endif // SH_C1P



/** \brief 调用SDK初始化数据包，设置LED画笔颜色。(后面命令显示文字的颜色，不改变现在显示的内容)
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param ledcolour 颜色值。指定颜色值：
    - 1 ：红色。
    - 2 ：绿色。
    - 3 ：黄色。
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetBrushColour(LED_Pack_t *Buf,uint8_t ledid,unsigned char ledcolour);

/** \brief 调用SDK初始化数据包，设置LED开机时,画笔颜色(开机后调用 @ref LED_SetBrushColour 改变颜色)
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param ledcolour 颜色值。指定颜色值：
    - 1 ：红色。
    - 2 ：绿色。
    - 3 ：黄色。
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_DeltBrushColour(LED_Pack_t *Buf,uint8_t ledid,unsigned char ledcolour);

/** \brief 调用SDK初始化数据包，显示GBK编码的文字
 *
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 要显示的行号
 * \param str 要显示的字符串
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_ShowGBK(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const char *str);

/** \brief 调用SDK初始化数据包，设置GBK编码的开机默认文字
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param str 要设置的字符串
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_SetBootGBK(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const char *str);

/** \brief 调用SDK初始化数据包，显示unicode编码的文字
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 要显示的行号
 * \param wstr 要显示的字符串
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_ShowUnicode(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief 调用SDK初始化数据包，设置GBK编码的应急信息
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param str 要设置的字符串
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_SetEmergGBK(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const char *str);

/** \brief 调用SDK初始化数据包，设置unicode编码的应急信息
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param wstr 要设置的字符串
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_SetEmergUnicode(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief 调用SDK初始化数据包，设置unicode编码的开机默认文字
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 要设置的行号
 * \param wstr 要设置的字符串
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 * \note 如果要改变字体颜色请先调用 @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_SetBootUnicode(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief 调用SDK初始化数据包，设置LED亮度
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param brigth 亮度值 (详见 @ref LED_BRIGTH_e )
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetBrigth(LED_Pack_t *Buf,uint8_t ledid,unsigned char brigth);

/** \brief 调用SDK初始化数据包，设置LED恢复出厂设置
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_FactoryReset(LED_Pack_t *Buf,uint8_t ledid);


/** \brief 调用SDK初始化数据包，执行清屏操作
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_ClearScreen(LED_Pack_t *Buf,uint8_t ledid);

/** \brief 调用SDK初始化数据包，清指定行的内容
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 要清除的行号
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_ClearLine(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo);

/** \brief 调用SDK初始化数据包，重启LED
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_Reset(LED_Pack_t *Buf,uint8_t ledid);

/** \brief 调用SDK初始化数据包，设置LED开机时默认文字对齐方式
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param align 对齐方式。 详见 @ref LED_ALIGN_e
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetDeltAlign(LED_Pack_t *Buf,uint8_t ledid,unsigned char align);

/** \brief 调用SDK初始化数据包，设置指定行开机时默认文字对齐方式
* \param Buf 数据包缓存指针
* \param ledid LED地址(id)
* \param lineNo 要设置的行号
* \param align 对齐方式。 详见 @ref LED_ALIGN_e
* \return 数据包有效数据长度，返回值为0表示初始化失败
*
*/
uint8_t PackInit_SetDeltAlignLine(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,unsigned char align);

/** \brief 调用SDK初始化数据包，设置文字对齐方式
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param align 对齐方式。 详见 @ref LED_ALIGN_e
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetAlign(LED_Pack_t *Buf,uint8_t ledid,unsigned char align);

/** \brief 调用SDK初始化数据包，设置指定行文字对齐方式
* \param Buf 数据包缓存指针
* \param ledid LED地址(id)
* \param lineNo 要设置的行号
* \param align 对齐方式。 详见 @ref LED_ALIGN_e
* \return 数据包有效数据长度，返回值为0表示初始化失败
*
*/
uint8_t PackInit_SetAlignLine(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,unsigned char align);

/** \brief 调用SDK初始化数据包，打开闪烁功能
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param BrightTiem LED亮的时间(ms)
 * \param OffTiem LED灭的时间(ms)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_BlinkOn(LED_Pack_t *Buf,uint8_t ledid,uint16_t BrightTiem,uint16_t OffTiem);

/** \brief 调用SDK初始化数据包，关闭闪烁功能
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_BlinkOff(LED_Pack_t *Buf,uint8_t ledid);

/** \brief 调用SDK初始化数据包，打开开机默认闪烁功能
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param BrightTiem LED亮的时间(ms)
 * \param OffTiem LED灭的时间(ms)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_DeltBlinkOn(LED_Pack_t *Buf,uint8_t ledid,uint16_t BrightTiem,uint16_t OffTiem);

/** \brief 调用SDK初始化数据包，关闭开机默认闪烁功能
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_DeltBlinkOff(LED_Pack_t *Buf,uint8_t ledid);

/** \brief 调用SDK初始化数据包，设置滚动时间
 * \note 当 MoveTime 和 PauseTime 都为0时表示不滚动。
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param MoveTime 滚动速度(ms)
 * \param PauseTime 停留时间(ms)
 * \param StageTime 段落时间(ms)(一行显示多段信息时使用),不使用时传入0
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetScrollTime(LED_Pack_t *Buf,uint8_t ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime);

/** \brief 调用SDK初始化数据包，设置开机默认滚动时间
 * \note 当 MoveTime 和 PauseTime 都为0时表示不滚动。
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param MoveTime 滚动速度(ms)
 * \param PauseTime 停留时间(ms)
 * \param StageTime 段落时间(ms)(一行显示多段信息时使用),不使用时传入0
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_DeltScrollTime(LED_Pack_t *Buf,uint8_t ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime);

/** \brief 调用SDK初始化数据包，设置滚动风格
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param scrollStyle 样式，详见 @ref LED_ScrollStyle_t
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetScrollStyle(LED_Pack_t *Buf,uint8_t ledid,uint32_t scrollStyle);

/** \brief 调用SDK初始化数据包，设置开机默认滚动风格
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param scrollStyle 样式，详见 @ref LED_ScrollStyle_t
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_DeltScrollStyle(LED_Pack_t *Buf,uint8_t ledid,uint32_t scrollStyle);

/** \brief 调用SDK初始化数据包，设置LED像素大小
 * \note 像素的宽和高都不能超过LED所支持的像素
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param Width LED宽(像素点)
 * \param Height LED高(像素点)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetPixelSize(LED_Pack_t *Buf,uint8_t ledid,uint16_t Width,uint16_t Height);

/** \brief 调用SDK初始化数据包，设置LED扫描方式
 * \note 设置LED扫描方式和数据信号极性。
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param ledpolar 数据信号结构体指针。  @ref LED_ScanMode_t
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetScanMode(LED_Pack_t *Buf,uint8_t ledid,const LED_ScanMode_t *ledpolar);

/** \brief 调用SDK初始化数据包，按模组名称设置LED扫描方式
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param moduleName 模组名称。
 * \return 数据包有效数据长度，返回值为0表示初始化失败
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
uint8_t PackInit_SetModule(LED_Pack_t *Buf,uint8_t ledid,const char *moduleName);

/** \brief 调用SDK初始化数据包，设置开机自检
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param showTime 自检显示时间(单位:秒),设置为0，表示不进行开机自检
 * \param isShowID 是否显示ID（如果协议支持ID）
 * \param isShowVer 是否显示固件版本号
 * \param IsShowMsg 开机后是否显示 "开机默认信息"
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetSelfCheck(LED_Pack_t *Buf,uint8_t ledid,uint8_t showTime,bool isShowID,bool isShowVer,bool IsShowMsg);

/** \brief 调用SDK初始化数据包，修改LED ID（如果LED协议ID可用）
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id) （旧ID）
 * \param newid 新ID
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_ChangeID(LED_Pack_t *Buf,uint8_t ledid,unsigned char newid);

/** \brief 调用SDK初始化数据包，使LED进入下载模式。
 * \note 下载波特率过低传输时间过长。波特率过高容易传输出错。大文件可设置为345600,小文件设置为 115200 。  \n
 进入下载模式后只能对LED下载数据（字体或图片），其它操作无效。 \n 要退出下载模式可手动重启LED设备。
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param uintBaudrate: 下载时使用的波特率。
 * \param strProtocol: 下载时数据位与校验位及停止位设置。通常选 "8N1"
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_EnterDownMode(LED_Pack_t *Buf,uint8_t ledid,unsigned int uintBaudrate,const char *strProtocol);

/** \brief 调用SDK初始化数据包，设置指定行开机时显示图片
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param imageAddr 图片地址
 * \param Width 要显示的宽度，宽度为0时，显示整幅图片或按LED宽度来显示
 * \param Height 要显示的高度，高度为0时，显示整幅图片或按LED高度来显示
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetBootImage(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief 调用SDK初始化数据包，设置指定行应急信息时显示图片
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param imageAddr 图片地址
 * \param Width 要显示的宽度，宽度为0时，显示整幅图片或按LED宽度来显示
 * \param Height 要显示的高度，高度为0时，显示整幅图片或按LED高度来显示
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetEmergImage(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief 调用SDK初始化数据包，设置指定行显示图片
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param imageAddr 图片地址
 * \param Width 要显示的宽度，宽度为0时，显示整幅图片或按LED宽度来显示
 * \param Height 要显示的高度，高度为0时，显示整幅图片或按LED高度来显示
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_ShowImage(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief 调SDK初始化数据包，设置指定行字体
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param Width 字体宽度
 * \param Height 字体高度
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_SetLineFont(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint16_t Width,uint16_t Height);

/** \brief 调用SDK初始化数据包，设置指定行开机默认字体
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param lineNo 指定的行号
 * \param Width 字体宽度
 * \param Height 字体高度
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_DeltLineFont(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint16_t Width,uint16_t Height);

/** \brief 调用SDK初始化数据包，发送自定义命令
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param customcmd 自定义命令的字符串(16进制)
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_Custom(LED_Pack_t *Buf,uint8_t ledid,const char *customcmd);

 #if (defined SH_C1X)||(defined SH_C1T)
/** \brief 调SDK初始化数据包，快速写缓存地址
 * \param Buf 数据包缓存指针
 * \param ledid LED地址(id)
 * \param Xpos X坐标
 * \param Ypos Y坐标
 * \param Pixel 要写入的像素点数
 * \param PixelBuf 要写入的像素值
 * \return 数据包有效数据长度，返回值为0表示初始化失败
 *
 */
uint8_t PackInit_QuickWriteDisp(LED_Pack_t *Buf,uint8_t ledid,uint16_t Xpos,uint16_t Ypos,uint16_t Pixel,const uint8_t *PixelBuf);

#endif

/** \brief 调用SDK，将LED返回数据转换为SDK统一定义的定义的返回值
 *
 * \param *pData LED返回数据缓存
 * \param dataSize LED返回数据大小
 * \return SDK统一定义的定义的返回值
 *
 */
int8_t PackInit_RCVData2SDK(const unsigned char *pData,uint8_t dataSize);


#ifdef __cplusplus
}
#endif

#endif // __LEDSDK_H_INCLUDED
