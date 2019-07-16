#ifndef __PACKINIT_H_INCLUDED
#define __PACKINIT_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief ��SDK ���ݰ���ʼ�������Ķ���
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



/** \brief ����SDK��ʼ�����ݰ�������LED������ɫ��(����������ʾ���ֵ���ɫ�����ı�������ʾ������)
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param ledcolour ��ɫֵ��ָ����ɫֵ��
    - 1 ����ɫ��
    - 2 ����ɫ��
    - 3 ����ɫ��
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetBrushColour(LED_Pack_t *Buf,uint8_t ledid,unsigned char ledcolour);

/** \brief ����SDK��ʼ�����ݰ�������LED����ʱ,������ɫ(��������� @ref LED_SetBrushColour �ı���ɫ)
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param ledcolour ��ɫֵ��ָ����ɫֵ��
    - 1 ����ɫ��
    - 2 ����ɫ��
    - 3 ����ɫ��
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_DeltBrushColour(LED_Pack_t *Buf,uint8_t ledid,unsigned char ledcolour);

/** \brief ����SDK��ʼ�����ݰ�����ʾGBK���������
 *
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ��ʾ���к�
 * \param str Ҫ��ʾ���ַ���
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_ShowGBK(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const char *str);

/** \brief ����SDK��ʼ�����ݰ�������GBK����Ŀ���Ĭ������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param str Ҫ���õ��ַ���
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_SetBootGBK(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const char *str);

/** \brief ����SDK��ʼ�����ݰ�����ʾunicode���������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ��ʾ���к�
 * \param wstr Ҫ��ʾ���ַ���
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_ShowUnicode(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief ����SDK��ʼ�����ݰ�������GBK�����Ӧ����Ϣ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param str Ҫ���õ��ַ���
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_SetEmergGBK(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const char *str);

/** \brief ����SDK��ʼ�����ݰ�������unicode�����Ӧ����Ϣ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param wstr Ҫ���õ��ַ���
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_SetEmergUnicode(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief ����SDK��ʼ�����ݰ�������unicode����Ŀ���Ĭ������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ���õ��к�
 * \param wstr Ҫ���õ��ַ���
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 * \note ���Ҫ�ı�������ɫ���ȵ��� @ref LED_SetBrushColour
 *
 */
uint8_t PackInit_SetBootUnicode(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,const wchar_t *wstr);

/** \brief ����SDK��ʼ�����ݰ�������LED����
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param brigth ����ֵ (��� @ref LED_BRIGTH_e )
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetBrigth(LED_Pack_t *Buf,uint8_t ledid,unsigned char brigth);

/** \brief ����SDK��ʼ�����ݰ�������LED�ָ���������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_FactoryReset(LED_Pack_t *Buf,uint8_t ledid);


/** \brief ����SDK��ʼ�����ݰ���ִ����������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_ClearScreen(LED_Pack_t *Buf,uint8_t ledid);

/** \brief ����SDK��ʼ�����ݰ�����ָ���е�����
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo Ҫ������к�
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_ClearLine(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo);

/** \brief ����SDK��ʼ�����ݰ�������LED
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_Reset(LED_Pack_t *Buf,uint8_t ledid);

/** \brief ����SDK��ʼ�����ݰ�������LED����ʱĬ�����ֶ��뷽ʽ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param align ���뷽ʽ�� ��� @ref LED_ALIGN_e
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetDeltAlign(LED_Pack_t *Buf,uint8_t ledid,unsigned char align);

/** \brief ����SDK��ʼ�����ݰ�������ָ���п���ʱĬ�����ֶ��뷽ʽ
* \param Buf ���ݰ�����ָ��
* \param ledid LED��ַ(id)
* \param lineNo Ҫ���õ��к�
* \param align ���뷽ʽ�� ��� @ref LED_ALIGN_e
* \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
*
*/
uint8_t PackInit_SetDeltAlignLine(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,unsigned char align);

/** \brief ����SDK��ʼ�����ݰ����������ֶ��뷽ʽ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param align ���뷽ʽ�� ��� @ref LED_ALIGN_e
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetAlign(LED_Pack_t *Buf,uint8_t ledid,unsigned char align);

/** \brief ����SDK��ʼ�����ݰ�������ָ�������ֶ��뷽ʽ
* \param Buf ���ݰ�����ָ��
* \param ledid LED��ַ(id)
* \param lineNo Ҫ���õ��к�
* \param align ���뷽ʽ�� ��� @ref LED_ALIGN_e
* \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
*
*/
uint8_t PackInit_SetAlignLine(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,unsigned char align);

/** \brief ����SDK��ʼ�����ݰ�������˸����
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param BrightTiem LED����ʱ��(ms)
 * \param OffTiem LED���ʱ��(ms)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_BlinkOn(LED_Pack_t *Buf,uint8_t ledid,uint16_t BrightTiem,uint16_t OffTiem);

/** \brief ����SDK��ʼ�����ݰ����ر���˸����
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_BlinkOff(LED_Pack_t *Buf,uint8_t ledid);

/** \brief ����SDK��ʼ�����ݰ����򿪿���Ĭ����˸����
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param BrightTiem LED����ʱ��(ms)
 * \param OffTiem LED���ʱ��(ms)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_DeltBlinkOn(LED_Pack_t *Buf,uint8_t ledid,uint16_t BrightTiem,uint16_t OffTiem);

/** \brief ����SDK��ʼ�����ݰ����رտ���Ĭ����˸����
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_DeltBlinkOff(LED_Pack_t *Buf,uint8_t ledid);

/** \brief ����SDK��ʼ�����ݰ������ù���ʱ��
 * \note �� MoveTime �� PauseTime ��Ϊ0ʱ��ʾ��������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param MoveTime �����ٶ�(ms)
 * \param PauseTime ͣ��ʱ��(ms)
 * \param StageTime ����ʱ��(ms)(һ����ʾ�����Ϣʱʹ��),��ʹ��ʱ����0
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetScrollTime(LED_Pack_t *Buf,uint8_t ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime);

/** \brief ����SDK��ʼ�����ݰ������ÿ���Ĭ�Ϲ���ʱ��
 * \note �� MoveTime �� PauseTime ��Ϊ0ʱ��ʾ��������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param MoveTime �����ٶ�(ms)
 * \param PauseTime ͣ��ʱ��(ms)
 * \param StageTime ����ʱ��(ms)(һ����ʾ�����Ϣʱʹ��),��ʹ��ʱ����0
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_DeltScrollTime(LED_Pack_t *Buf,uint8_t ledid,uint16_t MoveTime,uint16_t PauseTime,uint32_t StageTime);

/** \brief ����SDK��ʼ�����ݰ������ù������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param scrollStyle ��ʽ����� @ref LED_ScrollStyle_t
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetScrollStyle(LED_Pack_t *Buf,uint8_t ledid,uint32_t scrollStyle);

/** \brief ����SDK��ʼ�����ݰ������ÿ���Ĭ�Ϲ������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param scrollStyle ��ʽ����� @ref LED_ScrollStyle_t
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_DeltScrollStyle(LED_Pack_t *Buf,uint8_t ledid,uint32_t scrollStyle);

/** \brief ����SDK��ʼ�����ݰ�������LED���ش�С
 * \note ���صĿ�͸߶����ܳ���LED��֧�ֵ�����
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param Width LED��(���ص�)
 * \param Height LED��(���ص�)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetPixelSize(LED_Pack_t *Buf,uint8_t ledid,uint16_t Width,uint16_t Height);

/** \brief ����SDK��ʼ�����ݰ�������LEDɨ�跽ʽ
 * \note ����LEDɨ�跽ʽ�������źż��ԡ�
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param ledpolar �����źŽṹ��ָ�롣  @ref LED_ScanMode_t
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetScanMode(LED_Pack_t *Buf,uint8_t ledid,const LED_ScanMode_t *ledpolar);

/** \brief ����SDK��ʼ�����ݰ�����ģ����������LEDɨ�跽ʽ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param moduleName ģ�����ơ�
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
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
uint8_t PackInit_SetModule(LED_Pack_t *Buf,uint8_t ledid,const char *moduleName);

/** \brief ����SDK��ʼ�����ݰ������ÿ����Լ�
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param showTime �Լ���ʾʱ��(��λ:��),����Ϊ0����ʾ�����п����Լ�
 * \param isShowID �Ƿ���ʾID�����Э��֧��ID��
 * \param isShowVer �Ƿ���ʾ�̼��汾��
 * \param IsShowMsg �������Ƿ���ʾ "����Ĭ����Ϣ"
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetSelfCheck(LED_Pack_t *Buf,uint8_t ledid,uint8_t showTime,bool isShowID,bool isShowVer,bool IsShowMsg);

/** \brief ����SDK��ʼ�����ݰ����޸�LED ID�����LEDЭ��ID���ã�
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id) ����ID��
 * \param newid ��ID
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_ChangeID(LED_Pack_t *Buf,uint8_t ledid,unsigned char newid);

/** \brief ����SDK��ʼ�����ݰ���ʹLED��������ģʽ��
 * \note ���ز����ʹ��ʹ���ʱ������������ʹ������״���������ļ�������Ϊ345600,С�ļ�����Ϊ 115200 ��  \n
 ��������ģʽ��ֻ�ܶ�LED�������ݣ������ͼƬ��������������Ч�� \n Ҫ�˳�����ģʽ���ֶ�����LED�豸��
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param uintBaudrate: ����ʱʹ�õĲ����ʡ�
 * \param strProtocol: ����ʱ����λ��У��λ��ֹͣλ���á�ͨ��ѡ "8N1"
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_EnterDownMode(LED_Pack_t *Buf,uint8_t ledid,unsigned int uintBaudrate,const char *strProtocol);

/** \brief ����SDK��ʼ�����ݰ�������ָ���п���ʱ��ʾͼƬ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param imageAddr ͼƬ��ַ
 * \param Width Ҫ��ʾ�Ŀ�ȣ����Ϊ0ʱ����ʾ����ͼƬ��LED�������ʾ
 * \param Height Ҫ��ʾ�ĸ߶ȣ��߶�Ϊ0ʱ����ʾ����ͼƬ��LED�߶�����ʾ
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetBootImage(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief ����SDK��ʼ�����ݰ�������ָ����Ӧ����Ϣʱ��ʾͼƬ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param imageAddr ͼƬ��ַ
 * \param Width Ҫ��ʾ�Ŀ�ȣ����Ϊ0ʱ����ʾ����ͼƬ��LED�������ʾ
 * \param Height Ҫ��ʾ�ĸ߶ȣ��߶�Ϊ0ʱ����ʾ����ͼƬ��LED�߶�����ʾ
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetEmergImage(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief ����SDK��ʼ�����ݰ�������ָ������ʾͼƬ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param imageAddr ͼƬ��ַ
 * \param Width Ҫ��ʾ�Ŀ�ȣ����Ϊ0ʱ����ʾ����ͼƬ��LED�������ʾ
 * \param Height Ҫ��ʾ�ĸ߶ȣ��߶�Ϊ0ʱ����ʾ����ͼƬ��LED�߶�����ʾ
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_ShowImage(LED_Pack_t *Buf,uint8_t ledid,unsigned char lineNo,uint32_t imageAddr,uint16_t Width,uint16_t Height);

/** \brief ��SDK��ʼ�����ݰ�������ָ��������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param Width ������
 * \param Height ����߶�
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_SetLineFont(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint16_t Width,uint16_t Height);

/** \brief ����SDK��ʼ�����ݰ�������ָ���п���Ĭ������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param lineNo ָ�����к�
 * \param Width ������
 * \param Height ����߶�
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_DeltLineFont(LED_Pack_t *Buf,uint8_t ledid,uint8_t lineNo,uint16_t Width,uint16_t Height);

/** \brief ����SDK��ʼ�����ݰ��������Զ�������
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param customcmd �Զ���������ַ���(16����)
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_Custom(LED_Pack_t *Buf,uint8_t ledid,const char *customcmd);

 #if (defined SH_C1X)||(defined SH_C1T)
/** \brief ��SDK��ʼ�����ݰ�������д�����ַ
 * \param Buf ���ݰ�����ָ��
 * \param ledid LED��ַ(id)
 * \param Xpos X����
 * \param Ypos Y����
 * \param Pixel Ҫд������ص���
 * \param PixelBuf Ҫд�������ֵ
 * \return ���ݰ���Ч���ݳ��ȣ�����ֵΪ0��ʾ��ʼ��ʧ��
 *
 */
uint8_t PackInit_QuickWriteDisp(LED_Pack_t *Buf,uint8_t ledid,uint16_t Xpos,uint16_t Ypos,uint16_t Pixel,const uint8_t *PixelBuf);

#endif

/** \brief ����SDK����LED��������ת��ΪSDKͳһ����Ķ���ķ���ֵ
 *
 * \param *pData LED�������ݻ���
 * \param dataSize LED�������ݴ�С
 * \return SDKͳһ����Ķ���ķ���ֵ
 *
 */
int8_t PackInit_RCVData2SDK(const unsigned char *pData,uint8_t dataSize);


#ifdef __cplusplus
}
#endif

#endif // __LEDSDK_H_INCLUDED
