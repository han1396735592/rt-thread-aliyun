#ifndef __SH_C1X_H_INCLUDED
#define __SH_C1X_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief SH-C1X��SH-C1T �������궨�塣(Դ�ļ�ģʽʹ��)
  *******************************************************************************
  * @note ���ļ�����Ӧ��Դ�ļ�(SH-C1X.c)��SDKԴ�ļ�ģʽʱʹ�ã����ʹ��DLLģʽ�����ע���ļ��� \n
  ���ļ�����Ӧ��Դ�ļ������� Windows ƽ̨�뵥Ƭ����Ŀ�С� \n
  ���ѡ���˲���ID��Э��(��SH-C1X)��SDK����������Ҫledid����ʱ�����⴫��һ�����֡�
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SH_C1T
#   ifndef USE_PACT_ID
#       define USE_PACT_ID
#   endif // USE_PACT_ID
#   define LEDPack_Min     (7) /**< �������ݰ���С���ȣ�SH-C1TΪ7��SH-C1XΪ6 */

#   if (LEDPack_Size<=(LEDPack_Min))
#       error  "LEDPack_Size can not be less than 8 "
#   endif
#endif // SH_C1T

#ifdef SH_C1X
#   define LEDPack_Min     (6) /**< �������ݰ���С���ȣ�SH-C1TΪ7��SH-C1XΪ6 */
#   if (LEDPack_Size<=(LEDPack_Min))
#       error  "LEDPack_Size can not be less than 7 "
#   endif
#endif // SH_C1T

typedef struct C1T_LineCmd_t
{
    /** @brief  �к� */
    uint8_t LineNo;
    /** @brief  ��ָ�� */
    uint8_t LineCMD;

    /** @brief  ���������� */
    uint8_t LineParam[LEDPack_Size-LEDPack_Min];
}
C1T_LineCmd_t;


/** @brief SH-C1T ���ݰ��ṹ�� -- ���256���ֽ� */
typedef struct C1T_Pack_t
{
    /** @brief ���ݰ�ͷ */
    uint8_t Head;
    /** @brief ���ݰ����� */
    uint8_t Length;
    /** @brief ���ݰ�����У�� */
    uint8_t LenCheck;
    /** @brief ���� */
    uint8_t id;
    /** @brief ����(ָ�����) */
    uint8_t CMD;

    /** @brief ָ��������� */
    uint8_t Param[LEDPack_Size-7+2];
}
C1T_Pack_t;

/** @brief  SH-C1X ���ݰ��ṹ�� -- ���256���ֽ� */
typedef struct C1X_Pack_t
{
    /** @brief ���ݰ�ͷ */
    uint8_t Head;
    /** @brief ���ݰ����� */
    uint8_t Length;
    /** @brief ���ݰ�����У�� */
    uint8_t LenCheck;
    /** @brief ����(ָ�����) */
    uint8_t CMD;
    /** @brief ָ��������� */
    uint8_t Param[LEDPack_Size-6+2];

}
C1X_Pack_t;

#define C1X_RCVSIZE         (1) /**< LED���ݰ�����ֵ��С */




#define C1X_WriteKey(_buf,_bytecount)   { \
                                            _buf[(_bytecount)] = 0x14; \
                                            _buf[(_bytecount)+1] = 0xB4; \
                                            _buf[(_bytecount)+2] = 0xf8; \
                                            _buf[(_bytecount)+3] = 0x94; \
                                        }


/** @brief LEDָ����� ö�� */
enum
{
    C1XCMD_BRUSHCOLOR = 0x56,                   /**< ������ɫ */
    C1XCMD_DELTBRUSH = 0x80+C1XCMD_BRUSHCOLOR,  /**< ����ʱĬ�ϻ�����ɫ */
    C1XCMD_LINE = 0x5c,                         /**< LED��ָ�� */
    C1XCMD_BRIGTH = 0x43,                       /**< �������� */
    C1XLINE_SHOWGBK = 0x01,                     /**< ������--��ʾGBK���� */
    C1XLINE_SHOWUNICODE = 0x02,                 /**< ������--��ʾUNICODE���� */
    C1XLINE_BOOTGBK = 0x20,                     /**< ������--���ÿ���ʱ��ʾGBK�������� */
    C1XLINE_BOOTUNICODE = 0x21,                 /**< ������--���ÿ���ʱ��ʾUNICODE�������� */
    C1XLINE_EMOGBK = 0x30,                      /**< ������--Ӧ����Ϣʱ��ʾGBK�������� */
    C1XLINE_EMOUNICODE = 0x31,                  /**< ������--Ӧ����Ϣʱ��ʾUNICODE�������� */
    C1XLINE_SHOWIMAGE = 0x08,                   /**< ������--��ʾͼƬ  */
    C1XLINE_BOOTIMAGE = 0x28,                   /**< ������--����ʱ��ʾͼƬ  */
    C1XLINE_EMOIMAGE = 0x38,                    /**< ������--Ӧ����Ϣʱ��ʾͼƬ  */

    C1XCMD_FACTORYRESET = 0x9e,                 /**< �ָ��������� */
    C1XCMD_RESET = 0x99,                        /**< �������ƿ� */
    C1XCMD_CLEARCREEN = 0x63,                   /**< ���� */
    C1XCMD_CHANGEID = 0x21,                     /**< �޸Ļ��� */

    C1XCMD_SETALIGN = 0x6a,                     /**< ���뷽ʽ���� */
    C1XCMD_DELTALIGN = 0x80+C1XCMD_SETALIGN,    /**< ����Ĭ�϶��뷽ʽ���� */

    C1XCMD_SETBLINK = 0x61,                     /**< ��˸���� */
    C1XCMD_DELTBLINK = 0x80+C1XCMD_SETBLINK,    /**< ����Ĭ����˸���� */

    C1XCMD_SETPIXELSIZE = 0x9c,                 /**< �����ش�С���� */
    C1XCMD_SETSCANMODE = 0x9d,                  /**< ����ɨ�跽ʽ */
    C1XCMD_SETSELFCHECK = 0x9f,                 /**< �����Լ����� */

    C1XCMD_SETSCROLLTIME = 0x65,                /**< ��������ʱ�� */
    C1XCMD_DELTSCROLLTIME =
        0x80+C1XCMD_SETSCROLLTIME,              /**< ����Ĭ�Ϲ�������ʱ��*/

    C1XCMD_SETSCROLLSTYLE = 0x66,               /**< �������÷�� */
    C1XCMD_DELTSCROLLSTYLE =
        0x80+C1XCMD_SETSCROLLSTYLE,             /**< ����Ĭ�Ϲ������÷��*/

    C1XCMD_SETLINEFONT = 0x69,                  /**< �趨ָ���е����� */
    C1XCMD_DELTLINEFONT =
        0x80+C1XCMD_SETLINEFONT,                /**< �趨ָ���п���Ĭ������ */

    C1XCMD_ENTERDOWNMODE = 0x58,                /**< ��������ģʽ */
    C1XCMD_VOICE = 0x56,                        /**< �������� */
    C1XCMD_VOTEXT = 0x71,                       /**< ����������ʾ���� */


    C1XCMD_QUICKWRITEDISPMEM = 0x80,    /**< �Դ����д�� */

};

/** @brief LED����ֵ ö�� */
enum
{
    C1X_TREACT_OK           = 0x0f, /**< LED����ֵ�������ɹ� */
    C1X_ERROR_CHECK         = 0xf0, /**< LED����ֵ��У����� */
    C1X_ERROR_UNCMD         = 0xf1, /**< LED����ֵ��δ��������� */
    C1X_ERROR_LINETH        = 0xf2, /**< LED����ֵ�����ݰ����ȴ��� */
    C1X_ERROR_DATA          = 0xf3, /**< LED����ֵ�����ݰ����ݴ��� */
};


#ifdef __cplusplus
}
#endif



#endif // __SH-C1X_H_INCLUDED
