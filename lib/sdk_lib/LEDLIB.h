#ifndef LED_LEDLIB_H_INCLUDED
#define LED_LEDLIB_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief SDK ���ݰ����Ͳ�����(Ƕ��ʽƽ̨)
  ******************************************************************************
  * @note ���ļ�ֻ������ Ƕ��ʽƽ̨�� \n
  ���ѡ���˲���ID��Э��(��SH-C1X)��SDK����������Ҫledid����ʱ�����⴫��һ�����֡�
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------
// ȫ�ֺ궨��
//---------------------------------------------------------------------



//---------------------------------------------------------------------

#ifndef LEDPack_Size
#   define LEDPack_Size (256)
#endif // LEDPack_Size

#if (defined SH_C1T)//LED �ͺ�
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


/** \brief LED �������ݺ���,�ú�����Ҫ�û���ʵ��
 *
 * \param outtime �ȴ���ʱʱ��(ms)
 * \return extern int ��LED���յ������ݾ��� PackInit_RCVData2SDK ת�� �󷵻ء���ֵҲ�� LED����ͺ����ķ���ֵ��(LED_*****,@ref LED_SendPack)
 *
 */
extern int LED_ReceiveData(uint16_t outtime);

/** \brief LED �������ݰ�,�ú�����Ҫ�û���ʵ��
 *
 * \param pBuf Ҫ���͵����ݰ�ָ��
 * \param BufSize Ҫ���͵��ֽ���
 * \return extern �ѷ��͵��ֽ���
 *
 */
extern uint16_t LED_SendData(const uint8_t *pBuf,size_t BufSize);


/** \brief ����SDK,���ý��ճ�ʱʱ��
 * \note δ���ô˺����ǣ�Ĭ�� ���ճ�ʱ ʱ��Ϊ 100ms�� \n  ����SDK�����������ݰ�ʱ���ǹ㲥ģʽʱ����
 �ȴ�LED�������ݣ������ ���ճ�ʱ ���յ��������ݺ�����ǰ���ء�����ȴ���ʱ�������� @ref SDK_RECEIVE_OUTTIME �� \n
 ��� ���ճ�ʱ ����Ϊ0����ʾ������LED�������ݡ����ݰ�������ɺ󷵻� @ref SDK_SEND_NOTRECEIVE  ��
 * \param outtime ��ʱʱ�䣬��λms��(�������ô���100)
 */
void DLL_EXPORT LED_SetReceiveTimeout(unsigned int outtime);

/** \brief ����SDK������һ�����ݰ�
 *
 * \param ledid LED��ַ(id)
 * \param pBuf Ҫ���͵����ݰ�ָ��
 * \param sendByte ���ݰ���Ҫ���͵��ֽ���
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SendPack(unsigned char ledid,const char *pBuf,int sendByte);

/** \brief ����SDK,����LED������ɫ��(����������ʾ���ֵ���ɫ�����ı�������ʾ������)
 * \param ledid LED��ַ(id)
 * \param ledcolour ��ɫֵ��ָ����ɫֵ��
    - 1 ����ɫ��
    - 2 ����ɫ��
    - 3 ����ɫ��
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetBrushColour(unsigned char ledid,unsigned char ledcolour);

/** \brief ����SDK,����LED����ʱ,������ɫ(��������� @ref LED_SetBrushColour �ı���ɫ)
 * \param ledid LED��ַ(id)
 * \param ledcolour ��ɫֵ��ָ����ɫֵ��
    - 1 ����ɫ��
    - 2 ����ɫ��
    - 3 ����ɫ��
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltBrushColour(unsigned char ledid,unsigned char ledcolour);

/** \brief ����SDK,��ʾGBK���������
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ��ʾ���к�
 * \param str Ҫ��ʾ���ַ���
 * \return int @ref SDK_RECEIVE_e
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_ShowGBK(unsigned char ledid,unsigned char lineNo,const char *str);


#if (defined SH_C1X)||(defined SH_C1T)

/** \brief ����SDK,����д���Դ�
 *
 * \param ledid LED��ַ(id)
 * \param Xpos X����
 * \param Ypos Y����
 * \param Pixel Ҫд������ص���
 * \param PixelBuf Ҫд�������ֵ
 * \return int @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_QuickWriteDisp(uint8_t ledid,uint16_t Xpos,uint16_t Ypos,uint16_t Pixel,const uint8_t *PixelBuf);

#endif


/** \brief ����SDK,����GBK����Ŀ���Ĭ������
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param str Ҫ���õ��ַ���
 * \return int @ref SDK_RECEIVE_e
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_SetBootGBK(unsigned char ledid,unsigned char lineNo,const char *str);

/** \brief ����SDK,��ʾunicode���������
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ��ʾ���к�
 * \param wstr Ҫ��ʾ���ַ���
 * \return int @ref SDK_RECEIVE_e
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_ShowUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief ����SDK,����GBK�����Ӧ����Ϣ
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param str Ҫ���õ��ַ���
 * \return int @ref SDK_RECEIVE_e
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_SetEmergGBK(unsigned char ledid,unsigned char lineNo,const char *str);

/** \brief ����SDK,����unicode�����Ӧ����Ϣ
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param wstr Ҫ���õ��ַ���
 * \return int @ref SDK_RECEIVE_e
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_SetEmergUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief ����SDK,����unicode����Ŀ���Ĭ������
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param wstr Ҫ���õ��ַ���
 * \return int @ref SDK_RECEIVE_e
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
int DLL_EXPORT LED_SetBootUnicode(unsigned char ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief ����SDK,����LED����
 *
 * \param ledid LED��ַ(id)
 * \param brigth ����ֵ (��� @ref LED_BRIGTH_e )
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetBrigth(unsigned char ledid,unsigned char brigth);

/** \brief ����SDK,����LED�ָ���������
 *
 * \param ledid LED��ַ(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_FactoryReset(unsigned char ledid);


/** \brief ����SDK��ִ����������
 *
 * \param ledid LED��ַ(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_ClearScreen(unsigned char ledid);

/** \brief ����SDK����ָ���е�����
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ������к�
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_ClearLine(unsigned char ledid,unsigned char lineNo);

/** \brief ����SDK������LED
 *
 * \param ledid LED��ַ(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_Reset(unsigned char ledid);

/** \brief ����SDK������LED����ʱĬ�����ֶ��뷽ʽ
 *
 * \param ledid LED��ַ(id)
 * \param align ���뷽ʽ�� ��� @ref LED_ALIGN_e
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetDeltAlign(unsigned char ledid,unsigned char align);

 /** \brief ����SDK������ָ���п���ʱĬ�����ֶ��뷽ʽ
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param align ���뷽ʽ�� ��� @ref LED_ALIGN_e
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetDeltAlignLine(unsigned char ledid,unsigned char lineNo,unsigned char align);

/** \brief ����SDK���������ֶ��뷽ʽ
 *
 * \param ledid LED��ַ(id)
 * \param align ���뷽ʽ�� ��� @ref LED_ALIGN_e
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetAlign(unsigned char ledid,unsigned char align);

 /** \brief ����SDK������ָ�������ֶ��뷽ʽ
 *
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param align ���뷽ʽ�� ��� @ref LED_ALIGN_e
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetAlignLine(unsigned char ledid,unsigned char lineNo,unsigned char align);


/** \brief ����SDK������˸����
 *
 * \param ledid LED��ַ(id)
 * \param BrightTiem LED����ʱ��(ms)
 * \param OffTiem LED���ʱ��(ms)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_BlinkOn(unsigned char ledid,uint16_t BrightTiem,uint16_t OffTiem);

/** \brief ����SDK���ر���˸����
 *
 * \param ledid LED��ַ(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_BlinkOff(unsigned char ledid);

/** \brief ����SDK���򿪿���Ĭ����˸����
 *
 * \param ledid LED��ַ(id)
 * \param BrightTiem LED����ʱ��(ms)
 * \param OffTiem LED���ʱ��(ms)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltBlinkOn(unsigned char ledid,uint16_t BrightTiem,uint16_t OffTiem);

/** \brief ����SDK���رտ���Ĭ����˸����
 *
 * \param ledid LED��ַ(id)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltBlinkOff(unsigned char ledid);

/** \brief ����SDK�����ù���ʱ��
 * \note �� MoveTime �� PauseTime ��Ϊ0ʱ��ʾ��������
 * \param ledid LED��ַ(id)
 * \param MoveTime �����ٶ�(ms)
 * \param PauseTime ͣ��ʱ��(ms)
 * \param StageTime ����ʱ��(ms)(һ����ʾ�����Ϣʱʹ��),��ʹ��ʱ����0
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetScrollTime(unsigned char ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime);

/** \brief ����SDK�����ÿ���Ĭ�Ϲ���ʱ��
 * \note �� MoveTime �� PauseTime ��Ϊ0ʱ��ʾ��������
 * \param ledid LED��ַ(id)
 * \param MoveTime �����ٶ�(ms)
 * \param PauseTime ͣ��ʱ��(ms)
 * \param StageTime ����ʱ��(ms)(һ����ʾ�����Ϣʱʹ��),��ʹ��ʱ����0
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltScrollTime(unsigned char ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime);


/** \brief ����SDK�����ù������
 *
 * \param ledid LED��ַ(id)
 * \param scrollStyle ��ʽ����� @ref LED_ScrollStyle_t
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetScrollStyle(unsigned char ledid,uint32_t scrollStyle);


/** \brief ����SDK�����ÿ���Ĭ�Ϲ������
 *
 * \param ledid LED��ַ(id)
 * \param scrollStyle ��ʽ����� @ref LED_ScrollStyle_t
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltScrollStyle(unsigned char ledid,uint32_t scrollStyle);


/** \brief ����SDK������LED���ش�С
 * \note ���صĿ�͸߶����ܳ���LED��֧�ֵ�����
 * \param ledid LED��ַ(id)
 * \param Width LED��(���ص�)
 * \param Height LED��(���ص�)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetPixelSize(unsigned char ledid,uint16_t Width,uint16_t Height);

/** \brief ����SDK������LEDɨ�跽ʽ
 * \note ����LEDɨ�跽ʽ�������źż��ԡ�
 * \param ledid LED��ַ(id)
 * \param ledpolar �����źŽṹ��ָ�롣  @ref LED_ScanMode_t
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetScanMode(unsigned char ledid,const LED_ScanMode_t *ledpolar);

/** \brief ����SDK����ģ����������LEDɨ�跽ʽ
 * \param ledid LED��ַ(id)
 * \param moduleName ģ�����ơ�
 * \return int @ref SDK_RECEIVE_e
 * \note  ģ�����ƹ��� ��P�� + ����ࡱ + ����ɫ�� + ����չ�� ���� ��P10������P3.75D��
    - P ����д��ĸ ��P�� ��ͷ��
    - ��� ��ģ������ؼ��(mm)��
    - ��ɫ��(����Ϊ��)
        -# ˫ɫ����д��ĸ D
        -# ȫ�ʣ���д��ĸ A
    - ��չ��(��Ϊ��)
        -# E��ȫ����ģ�顣
 *
 */
int DLL_EXPORT LED_SetModule(unsigned char ledid,const char *moduleName);

/** \brief ����SDK�����ÿ����Լ�
 *
 * \param ledid LED��ַ(id)
 * \param showTime �Լ���ʾʱ��(��λ:��),����Ϊ0����ʾ�����п����Լ�
 * \param isShowID �Ƿ���ʾID�����Э��֧��ID��
 * \param isShowVer �Ƿ���ʾ�̼��汾��
 * \param IsShowMsg �������Ƿ���ʾ "����Ĭ����Ϣ"
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetSelfCheck(unsigned char ledid,uint8_t showTime,bool isShowID,bool isShowVer,bool IsShowMsg);

/** \brief ����SDK���޸�LED ID�����LEDЭ��ID���ã�
 *
 * \param ledid LED��ַ(id) ����ID��
 * \param newid ��ID
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_ChangeID(unsigned char ledid,unsigned char newid);

/** \brief ����SDK,ʹLED��������ģʽ��
 * \note ���ز����ʹ��ʹ���ʱ������������ʹ������״���������ļ�������Ϊ345600,С�ļ�����Ϊ 115200 ��  \n
 ��������ģʽ��ֻ�ܶ�LED�������ݣ������ͼƬ��������������Ч�� \n Ҫ�˳�����ģʽ���ֶ�����LED�豸��
 * \param ledid LED��ַ(id)
 * \param uintBaudrate: ����ʱʹ�õĲ����ʡ�
 * \param strProtocol: ����ʱ����λ��У��λ��ֹͣλ���á�ͨ��ѡ "8N1"
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_EnterDownMode(unsigned char ledid,unsigned int uintBaudrate,const char *strProtocol);

/** \brief ����SDK������ָ���п���ʱ��ʾͼƬ
 *
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param imageAddr ͼƬ��ַ
 * \param Width Ҫ��ʾ�Ŀ�ȣ����Ϊ0ʱ����ʾ����ͼƬ��LED�������ʾ
 * \param Height Ҫ��ʾ�ĸ߶ȣ��߶�Ϊ0ʱ����ʾ����ͼƬ��LED�߶�����ʾ
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetBootImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief ����SDK������ָ����Ӧ����Ϣʱ��ʾͼƬ
 *
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param imageAddr ͼƬ��ַ
 * \param Width Ҫ��ʾ�Ŀ�ȣ����Ϊ0ʱ����ʾ����ͼƬ��LED�������ʾ
 * \param Height Ҫ��ʾ�ĸ߶ȣ��߶�Ϊ0ʱ����ʾ����ͼƬ��LED�߶�����ʾ
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetEmergImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief ����SDK������ָ������ʾͼƬ
 *
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param imageAddr ͼƬ��ַ
 * \param Width Ҫ��ʾ�Ŀ�ȣ����Ϊ0ʱ����ʾ����ͼƬ��LED�������ʾ
 * \param Height Ҫ��ʾ�ĸ߶ȣ��߶�Ϊ0ʱ����ʾ����ͼƬ��LED�߶�����ʾ
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_ShowImage(unsigned char ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief ����SDK������ָ��������
 *
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param Width ������
 * \param Height ����߶�
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_SetLineFont(unsigned char ledid,uint8_t lineNo,uint16_t Width,uint16_t Height);

/** \brief ����SDK������ָ���п���Ĭ������
 *
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param Width ������
 * \param Height ����߶�
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_DeltLineFont(unsigned char ledid,uint8_t lineNo,uint16_t Width,uint16_t Height);

/** \brief ����SDK�������Զ�������
 *
 * \param ledid LED��ַ(id)
 * \param customcmd �Զ���������ַ���(16����)
 * \return int @ref SDK_RECEIVE_e
 *
 */
int DLL_EXPORT LED_Custom(unsigned char ledid,const char *customcmd);

/** \brief ��SDK�������ݰ���ʼ��
 *
 * \param func Ҫ��LED���в���������
 * \param packbuf ���ݰ�����(�����СΪ���ݰ��ṹ��Ĵ�С,ͨ����256 Byte)
 * \param ledid LED��ַ(id)
 * \param argc ���ݰ�����������
 * \param argv[] ���ݰ�����������
 * \return int ��ʼ���ɹ��������ݰ���Ч���ȣ���ʼ��ʧ�ܷ��� 0
 *
 */
int DLL_EXPORT LED_PackInit(const char *func,void *packbuf,uint8_t ledid,int argc,const char* argv[]);


#ifdef __cplusplus
}
#endif

#endif // LED_SERIALPORT_H_INCLUDED
