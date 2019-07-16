#ifndef __SH_C1P_H_INCLUDED
#define __SH_C1P_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief SH-C1P �������궨�塣(Դ�ļ�ģʽʹ��)
  *******************************************************************************
  * @note ���ļ�����Ӧ��Դ�ļ�(SH-C1P.c)��SDKԴ�ļ�ģʽʱʹ�ã����ʹ��DLLģʽ�����ע���ļ��� \n
  ���ļ�����Ӧ��Դ�ļ������� Windows ƽ̨�뵥Ƭ����Ŀ�С�
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

#include "LEDSDK.h"
#include "..\GPL\Modbus_RTU.h"

//#define C1X_RCVSIZE         (1)

#ifndef LEDResPack_Size
#define LEDResPack_Size     (LEDPack_Size) /**< LED��Ӧ���ݰ���С */
#endif // LEDResPack_Size




#define C1X_WriteKey(_buf,_bytecount)   { \
                                            _buf[(_bytecount)] = 0x14; \
                                            _buf[(_bytecount)+1] = 0xB4; \
                                            _buf[(_bytecount)+2] = 0xf8; \
                                            _buf[(_bytecount)+3] = 0x94; \
                                        }

typedef struct C1P_LineCmd_t
{
    /** @brief  �к� */
    uint8_t LineNo;
    /** @brief  ��ָ�� */
    uint8_t LineCMD;

    /** @brief  ���������� */
    uint8_t LineParam[250];
}
C1P_LineCmd_t;


enum
{
    C1PCMD_SETSCANMODE    = 0x2328, /**< ����ɨ�跽ʽ */
    C1PCMD_SETPIXELSIZE    = 0x2338, /**< ���������ش�С */
    C1PCMD_FACTORYRESET    = 0x270A, /**< �ָ��������� */
    C1PCMD_RESET    = 0x2706, /**< �������LED */
    C1PCMD_SETSELFCHECK    = 0x2348, /**< ���ÿ����Լ� */
    C1PCMD_ENTERDOWNMODE    = 0x2358, /**< ���������ͼƬ����ģʽ */
    C1PCMD_BRIGTH    = 0x2368, /**< �������� */
    C1PCMD_CHANGEID    = 0x236C, /**< ����(��ַ)���� */
    C1PCMD_BRUSHCOLOR    = 0x2370, /**< ���滭����ɫ */
    C1PCMD_DELTBRUSH    = 0x2372, /**< ����Ĭ�ϻ�����ɫ */
    C1PCMD_SETLINEFONT    = 0x2380, /**< ���ֻ����������� */
    C1PCMD_DELTLINEFONT    = 0x2390, /**< ���ֿ���Ĭ���������� */
    C1PCMD_SETALIGN    = 0x2376, /**< ͼƬ���ı�������뷽ʽ */
    C1PCMD_DELTALIGN    = 0x2378, /**< ͼƬ���ı�Ĭ�϶��뷽ʽ */
    C1PCMD_SETBLINK    = 0x23A0, /**< ��˸���ã����棩 */
    C1PCMD_DELTBLINK    = 0x23A8, /**< ��˸���ã�����Ĭ�ϣ� */
    C1PCMD_SETSCROLLTIME    = 0x23B8, /**< ����ʱ�����ã����棩 */
    C1PCMD_DELTSCROLLTIME    = 0x23C0, /**< ����ʱ�����ã�����Ĭ�ϣ� */
    C1PCMD_SETSCROLLSTYLE    = 0x23D0, /**< ������ʽ���ã����棩 */
    C1PCMD_DELTSCROLLSTYLE    = 0x23D8, /**< ������ʽ���ã�����Ĭ�ϣ� */
    C1PCMD_CLEARCREEN    = 0x23E8, /**< ����ָ�� */
    C1PCMD_LINE    = 0x2428, /**< ������ʾ��� */
};

enum
{
    C1PLINE_SHOWGBK = 0x01,                     /**< ������--��ʾGBK���� */
    C1PLINE_SHOWUNICODE = 0x02,                 /**< ������--��ʾUNICODE���� */
    C1PLINE_BOOTGBK = 0x20,                     /**< ������--���ÿ���ʱ��ʾGBK�������� */
    C1PLINE_BOOTUNICODE = 0x21,                 /**< ������--���ÿ���ʱ��ʾUNICODE�������� */
    C1PLINE_EMOGBK = 0x30,                      /**< ������--Ӧ����Ϣʱ��ʾGBK�������� */
    C1PLINE_EMOUNICODE = 0x31,                  /**< ������--Ӧ����Ϣʱ��ʾUNICODE�������� */
    C1PLINE_SHOWIMAGE = 0x08,                   /**< ������--��ʾͼƬ  */
    C1PLINE_BOOTIMAGE = 0x28,                   /**< ������--����ʱ��ʾͼƬ  */
    C1PLINE_EMOIMAGE = 0x38,                    /**< ������--Ӧ����Ϣʱ��ʾͼƬ  */
};


extern uint16_t CRC16_Modbus(const uint8_t *ptr,uint8_t len);

#define C1PBYTE_SETALIGN    (2)                     /**< ���뷽ʽ���� */
#define C1PBYTE_DELTALIGN   (2)   /**< ����Ĭ�϶��뷽ʽ���� */
#define C1PBYTE_BRUSHCOLOR      (2)     /**< ������ɫ */
#define C1PBYTE_DELTBRUSH       (2)     /**< ����ʱĬ�ϻ�����ɫ */
#define C1PBYTE_SETPIXELSIZE    (8)     /**< �����ش�С���� */
#define C1PBYTE_SETSCANMODE     (10)    /**< ����ɨ�跽ʽ */
#define C1PBYTE_FACTORYRESET    (4)     /**< �ָ��������� */
#define C1PBYTE_RESET           (4)     /**< �������ƿ� */
#define C1PBYTE_SETSELFCHECK    (8)     /**< �����Լ����� */
#define C1PBYTE_ENTERDOWNMODE   (8)     /**< ��������ģʽ */
#define C1PBYTE_BRIGTH          (2)     /**< �������� */
#define C1PBYTE_CHANGEID        (2)     /**< �޸Ļ��� */

#define C1PBYTE_SETLINEFONT     (10)            /**< �趨ָ���е����� */
#define C1PBYTE_DELTLINEFONT    (10)            /**< �趨ָ���п���Ĭ������ */
#define C1PBYTE_SETBLINK        (6)             /**< ��˸���� */
#define C1PBYTE_DELTBLINK       (6)             /**< ����Ĭ����˸���� */
#define C1PBYTE_SETSCROLLTIME   (8)             /**< ��������ʱ�� */
#define C1PBYTE_DELTSCROLLTIME  (8)             /**< ����Ĭ�Ϲ�������ʱ��*/
#define C1PBYTE_CLEARCREEN      (4)           /**< ���� */
#define C1PBYTE_SETSCROLLSTYLE  (4)            /**< �������÷�� */
#define C1PBYTE_DELTSCROLLSTYLE (4)            /**< ����Ĭ�Ϲ������÷��*/


#ifdef __cplusplus
}
#endif



#endif // __SH-C1X_H_INCLUDED
