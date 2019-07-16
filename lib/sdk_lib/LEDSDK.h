#ifndef __LEDSDK_H_INCLUDED
#define __LEDSDK_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief 对SDK宏定义与函数的定义
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif


/** @brief SDK广播地址0。
在SH-C1X与SH-C1T协议中广播地址为255，为了更好的与Modbus协议对接，建议用户使用地址0。 \n
在广播模式时，部分设置是无效的。(详见通信协议)
*/
#define SDK_BROADCAST       (0)

/** @brief SDK广播地址255。
在SH-C1X与SH-C1T协议中广播地址为255，为了保持兼容性，SDK中定义了广播地址255，在调用SDK函数时，
行参中广播地址0与广播地址255作用是一样的，SDK会根据不同的协议自动转换广播地址。
*/
#define SDK_BROADCAST_OLD   (0xff)

/** \brief SDK 函数返回枚举
如果返回值 >= 0 ,表示函数调用正确。\n
这个返回值，不是LED收到数据包后返回的数据，而是SDK统一定义的值。
SDK根据不同的协议自动把LED返回数据进行转换。
 */
enum SDK_RECEIVE_e
{
    SDK_SEND_NOTRECEIVE = 1,/**< 1:调用SDK函数时不接收LED返回值。函数行参ledid为广播地址，或 接收超时 @ref LED_SetReceiveTimeout 设置为0 */
    SDK_RECEIVE_OK = 0, /**< 0:SDK函数调用成功。LED数据包正常发出，并收到了LED正确的返回值。*/

    SDK_PARAMETER_ERROR = -17,/**< -17:SDK函数调用时行参错误。SDK函数中包含了参数防错检查。 */
    SDK_SERIALPORT_NOTOPEN = -18,/**< -18:串口没有打开。未调用 @ref LED_OpenSerialPort 打开串口，或串口打开未成功。 */
    SDK_SERIALPORT_ERROR = -19,/**< -19:串口错误。由于驱动或硬件的原因，数据包在发送过程中出错。建议先调用 @ref LED_CloseSerialPort 再重新打开串口。 */

    SDK_RECEIVE_OUTTIME = -33,/**< -33:接收超时，在指定的时间内未收到数据返回。请检查通信线是否连接正确，协议是否选对，接收超时 @ref LED_SetReceiveTimeout 是否设置得太短(建议在100ms以上)。 */
    SDK_RECEIVE_UNKNOWN = -34,/**< -34:LED返回未知的数据，收到的数据未定义。检查SDK的版本是否更新到最新。 */
    SDK_RECEIVE_CHECKERROR = -35,/**< -35:LED返回校验错误。数据包中校验数据出错，检查协议是否选对。 */
    SDK_RECEIVE_FUNCTIONUNDEFINED = -36,/**< -36:LED返回功能码未定义，可能LED固件未更新到最新版本。 */
    SDK_RECEIVE_LENGTHERROR = -37,/**< -37:LED返回数据包长度错误。SDK调用函数时参数是否正确。 */
    SDK_RECEIVE_DATAERROR = -38,/**< -38:LED返回数据包中数据错误，参数超出合理范围或固件未更新。 */
    SDK_LED_NOTFUNCTION = -39,/**< -39:LED没有这个功能。对LED的操作SDK中未定义方法。 */
    SDK_RECEIVE_ADDRESSERROR = -40,/**< -39:LED返回数据包中地址错误，地址超出合理范围或固件未更新。 */
};


/** @brief 亮度级别枚举 */
typedef enum LED_BRIGTH_e
{
    LED_BRIGTH_AUTO = 0xff,/**< 自动亮度(根据外接的光敏电阻自动调节) */
    LED_BRIGTH_L1 = 0,/**< 0:亮度级别1 */
    LED_BRIGTH_L2,/**< 1:亮度级别2 */
    LED_BRIGTH_L3,/**< 2:亮度级别3 */
    LED_BRIGTH_L4,/**< 3:亮度级别4 */
    LED_BRIGTH_L5,/**< 4:亮度级别5 */
    LED_BRIGTH_L6,/**< 5:亮度级别6 */
    LED_BRIGTH_L7,/**< 6:亮度级别7 */
    LED_BRIGTH_L8,/**< 7:亮度级别8 */
    LED_BRIGTH_L9,/**< 8:亮度级别9 */
    LED_BRIGTH_L10,/**< 9:亮度级别10 */
    LED_BRIGTH_L11,/**< 10:亮度级别11 */
    LED_BRIGTH_L12,/**< 11:亮度级别12 */
    LED_BRIGTH_L13,/**< 12:亮度级别13 */
    LED_BRIGTH_L14,/**< 13:亮度级别14 */
    LED_BRIGTH_L15,/**< 14:亮度级别15 */
    LED_BRIGTH_L16,/**< 15:亮度级别16 */
}
LED_BRIGTH_e;

/** @brief 对齐方式 */
typedef enum LED_ALIGN_e
{
    ALIGN_NONE = 0,     //!< 0：不指定对齐方式,由LED自动选择
    ALIGN_LEFT = 1,     //!< 1：左对齐
    ALIGN_RIGHT = 2,    //!< 2：右对齐
    ALIGN_CENTER = 4,   //!< 4：居中
}
LED_ALIGN_e;


#define LED_SCOLL_OFFINPULL     (0x01)  /**< 关闭开始滚动时拉幕。详见 @ref LED_ScrollStyle_t */
#define LED_SCOLL_OFFOUTPULL    (0x02)  /**< 关闭完成滚动时拉幕。详见 @ref LED_ScrollStyle_t  */

/** @brief LED扫描模式结构体 */
typedef struct LED_ScanMode_t
{
    uint8_t ScanMode;/**< 扫描方式,1/16扫描方式设置为16，1/4扫描设置为4 */
    uint8_t AddrSize;/**< 扫描地址大小，通常设置为16，P20的设置8 */
    uint8_t OEPolar;/**< OE信号极性,高电平有效设置为1,低电平有效设置0 */
    uint8_t STPolar;/**< 锁存信号极性，高电平有效设置为1,低电平有效设置0 */
    uint8_t CLKPolar;/**< 时钟信号极性，上升沿有效设置1，下降沿有效设置0 */
    uint8_t DataPolar;/**< 数据信号极性，高电平有效设置为1,低电平有效设置0 */
}
LED_ScanMode_t;



#ifdef __cplusplus
}
#endif



#endif // __LEDSDK_H_INCLUDED
