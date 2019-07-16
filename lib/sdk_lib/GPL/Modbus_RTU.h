#ifndef MODBUS_RTU_H_INCLUDED
#define MODBUS_RTU_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @author     SPING
  * @version    V0.0.1
  * @date       2016-01-30
  * @copyright  sping520@gmail.com
  * @brief
  ******************************************************************************
  * @note
  * @attention
  * <P style="FONT-SIZE:13px;"><center>&copy; COPYRIGHT 2013 SPING </center></P>
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief modbus功能码定义 */
typedef enum Modbus_FunCode
{
    MODBUS_READCOIL     = 0x01,/**< 读取线圈状态 取得一组逻辑线圈的当前状态（ ON/OFF) */
    MODBUS_READINPUT    = 0x02,/**< 读取输入状态 取得一组开关输入的当前状态（ ON/OFF) */
    MODBUS_READLOHDING  = 0x03,/**< 读取保持寄存器 在一个或多个保持寄存器中取得当前的二进制值  */
    MODBUS_READANALOG   = 0x04,/**< 读取输入寄存器 在一个或多个输入寄存器中取得当前的二进制值 */
    MODBUS_WRITESINGLE  = 0x05,/**< 强置单线圈 强置一个逻辑线圈的通断状态  */

    MODBUS_WRITE_ONEHOLD_REGISTER       = 0x06, /**< 写单一保持寄存器 */
    MODBUS_WRITE_MULTHOLD_REGISTER      = 0x10, /**< 写多个保持寄存器 */

}
/** @brief modbus功能码定义 */
Modbus_FunCode;

#define MODBUS_MULTW_MINBYTE        (9)
#define MBADU_MINSIZE       (4)

/** @brief modbus写数据结构体 */
typedef struct ModbusWrite_t
{
    uint8_t AddrH;
    uint8_t AddrL;
    uint8_t DataH;
    uint8_t DataL;
}
/** @brief modbus写数据结构体 */
ModbusWrite_t;


/** @brief modbus写多个数据结构体 */
typedef struct ModbusMultW_t
{
    uint8_t AddrHi;
    uint8_t AddrLi;

    uint8_t QuantityHi;
    uint8_t QuantityLi;

    uint8_t ByteCount;

    uint8_t Data[LEDPack_Size-MODBUS_MULTW_MINBYTE];
}
ModbusMultW_t;



/** @brief MODBUS异常响应PDU */
typedef struct mb_excep_rsp_pdu
{
    uint8_t function_code;/**< 功能码, ODBUS 功能码  + 0x80 */
    uint8_t exception_code;/**< 错误码 ，在下表中定义了MODBUS异常码 */
}
mb_excep_rsp_pdu;

/** @brief MODBUS响应PDU */
typedef struct mb_rsp_pdu
{
    uint8_t function_code;/**< 功能码 */
    uint8_t response_data[LEDPack_Size-MBADU_MINSIZE];/**< 数据 */
}
/** @brief MODBUS响应PDU */
mb_rsp_pdu;

/**< MODBUS请求PDU */
typedef struct mb_req_pdu
{
    uint8_t function_code;/**< 功能码 */
    ModbusMultW_t MultW;/**< 多寄存器写 */
    //uint8_t response_data[LEDPack_Size-MBADU_MINSIZE];/**< 数据 */
}
/**< MODBUS请求PDU */
mb_req_pdu;

typedef struct Modbus_CRC
{
    uint8_t CRCL;/**< 校验低字节 */
    uint8_t CRCH;/**< 校验高字节 */
}
Modbus_CRC;

/** @brief 请求数据包 */
typedef struct Modbus_ADU
{
    uint8_t         Addr;/**< 地址域 */
    mb_req_pdu      req;/**< 请求PDU */
    Modbus_CRC      CRC16;
}
Modbus_ADU;

/** @brief 错误返回数据包 */
typedef struct Modbus_Excep
{
    uint8_t Addr;/**< 地址域 */
	  mb_excep_rsp_pdu        esp;/**< 异常响应 */
    Modbus_CRC CRC16;
}
Modbus_Excep;

/** @brief 响应返回数据包 */
typedef struct Modbus_Rsp
{
    uint8_t Addr;/**< 地址域 */
		mb_rsp_pdu              rsp;/**< 响应PDU */
    Modbus_CRC CRC16;
}
Modbus_Rsp;





/** @brief MODBUS 错误代码 */
typedef enum MBEC_ENUM
{
    MBEC_INVALIDFUNCTION = 1,/**< 无效的功能 */
    MBEC_INVALIDADDRESS = 2,/**< 无效的地址 */
    MBEC_INVALIDDATA = 3,/**< 无效的数据 */
}
MBEC_ENUM;

#ifdef __cplusplus
}
#endif

#endif // MODBUS_RTU_H_INCLUDED
