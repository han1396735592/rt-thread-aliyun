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

/** @brief modbus�����붨�� */
typedef enum Modbus_FunCode
{
    MODBUS_READCOIL     = 0x01,/**< ��ȡ��Ȧ״̬ ȡ��һ���߼���Ȧ�ĵ�ǰ״̬�� ON/OFF) */
    MODBUS_READINPUT    = 0x02,/**< ��ȡ����״̬ ȡ��һ�鿪������ĵ�ǰ״̬�� ON/OFF) */
    MODBUS_READLOHDING  = 0x03,/**< ��ȡ���ּĴ��� ��һ���������ּĴ�����ȡ�õ�ǰ�Ķ�����ֵ  */
    MODBUS_READANALOG   = 0x04,/**< ��ȡ����Ĵ��� ��һ����������Ĵ�����ȡ�õ�ǰ�Ķ�����ֵ */
    MODBUS_WRITESINGLE  = 0x05,/**< ǿ�õ���Ȧ ǿ��һ���߼���Ȧ��ͨ��״̬  */

    MODBUS_WRITE_ONEHOLD_REGISTER       = 0x06, /**< д��һ���ּĴ��� */
    MODBUS_WRITE_MULTHOLD_REGISTER      = 0x10, /**< д������ּĴ��� */

}
/** @brief modbus�����붨�� */
Modbus_FunCode;

#define MODBUS_MULTW_MINBYTE        (9)
#define MBADU_MINSIZE       (4)

/** @brief modbusд���ݽṹ�� */
typedef struct ModbusWrite_t
{
    uint8_t AddrH;
    uint8_t AddrL;
    uint8_t DataH;
    uint8_t DataL;
}
/** @brief modbusд���ݽṹ�� */
ModbusWrite_t;


/** @brief modbusд������ݽṹ�� */
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



/** @brief MODBUS�쳣��ӦPDU */
typedef struct mb_excep_rsp_pdu
{
    uint8_t function_code;/**< ������, ODBUS ������  + 0x80 */
    uint8_t exception_code;/**< ������ �����±��ж�����MODBUS�쳣�� */
}
mb_excep_rsp_pdu;

/** @brief MODBUS��ӦPDU */
typedef struct mb_rsp_pdu
{
    uint8_t function_code;/**< ������ */
    uint8_t response_data[LEDPack_Size-MBADU_MINSIZE];/**< ���� */
}
/** @brief MODBUS��ӦPDU */
mb_rsp_pdu;

/**< MODBUS����PDU */
typedef struct mb_req_pdu
{
    uint8_t function_code;/**< ������ */
    ModbusMultW_t MultW;/**< ��Ĵ���д */
    //uint8_t response_data[LEDPack_Size-MBADU_MINSIZE];/**< ���� */
}
/**< MODBUS����PDU */
mb_req_pdu;

typedef struct Modbus_CRC
{
    uint8_t CRCL;/**< У����ֽ� */
    uint8_t CRCH;/**< У����ֽ� */
}
Modbus_CRC;

/** @brief �������ݰ� */
typedef struct Modbus_ADU
{
    uint8_t         Addr;/**< ��ַ�� */
    mb_req_pdu      req;/**< ����PDU */
    Modbus_CRC      CRC16;
}
Modbus_ADU;

/** @brief ���󷵻����ݰ� */
typedef struct Modbus_Excep
{
    uint8_t Addr;/**< ��ַ�� */
	  mb_excep_rsp_pdu        esp;/**< �쳣��Ӧ */
    Modbus_CRC CRC16;
}
Modbus_Excep;

/** @brief ��Ӧ�������ݰ� */
typedef struct Modbus_Rsp
{
    uint8_t Addr;/**< ��ַ�� */
		mb_rsp_pdu              rsp;/**< ��ӦPDU */
    Modbus_CRC CRC16;
}
Modbus_Rsp;





/** @brief MODBUS ������� */
typedef enum MBEC_ENUM
{
    MBEC_INVALIDFUNCTION = 1,/**< ��Ч�Ĺ��� */
    MBEC_INVALIDADDRESS = 2,/**< ��Ч�ĵ�ַ */
    MBEC_INVALIDDATA = 3,/**< ��Ч������ */
}
MBEC_ENUM;

#ifdef __cplusplus
}
#endif

#endif // MODBUS_RTU_H_INCLUDED
