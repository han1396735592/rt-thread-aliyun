#ifndef __LEDSDK_H_INCLUDED
#define __LEDSDK_H_INCLUDED

/**
  ******************************************************************************
  * @file
  * @brief ��SDK�궨���뺯���Ķ���
  *******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif


/** @brief SDK�㲥��ַ0��
��SH-C1X��SH-C1TЭ���й㲥��ַΪ255��Ϊ�˸��õ���ModbusЭ��Խӣ������û�ʹ�õ�ַ0�� \n
�ڹ㲥ģʽʱ��������������Ч�ġ�(���ͨ��Э��)
*/
#define SDK_BROADCAST       (0)

/** @brief SDK�㲥��ַ255��
��SH-C1X��SH-C1TЭ���й㲥��ַΪ255��Ϊ�˱��ּ����ԣ�SDK�ж����˹㲥��ַ255���ڵ���SDK����ʱ��
�в��й㲥��ַ0��㲥��ַ255������һ���ģ�SDK����ݲ�ͬ��Э���Զ�ת���㲥��ַ��
*/
#define SDK_BROADCAST_OLD   (0xff)

/** \brief SDK ��������ö��
�������ֵ >= 0 ,��ʾ����������ȷ��\n
�������ֵ������LED�յ����ݰ��󷵻ص����ݣ�����SDKͳһ�����ֵ��
SDK���ݲ�ͬ��Э���Զ���LED�������ݽ���ת����
 */
enum SDK_RECEIVE_e
{
    SDK_SEND_NOTRECEIVE = 1,/**< 1:����SDK����ʱ������LED����ֵ�������в�ledidΪ�㲥��ַ���� ���ճ�ʱ @ref LED_SetReceiveTimeout ����Ϊ0 */
    SDK_RECEIVE_OK = 0, /**< 0:SDK�������óɹ���LED���ݰ��������������յ���LED��ȷ�ķ���ֵ��*/

    SDK_PARAMETER_ERROR = -17,/**< -17:SDK��������ʱ�вδ���SDK�����а����˲��������顣 */
    SDK_SERIALPORT_NOTOPEN = -18,/**< -18:����û�д򿪡�δ���� @ref LED_OpenSerialPort �򿪴��ڣ��򴮿ڴ�δ�ɹ��� */
    SDK_SERIALPORT_ERROR = -19,/**< -19:���ڴ�������������Ӳ����ԭ�����ݰ��ڷ��͹����г��������ȵ��� @ref LED_CloseSerialPort �����´򿪴��ڡ� */

    SDK_RECEIVE_OUTTIME = -33,/**< -33:���ճ�ʱ����ָ����ʱ����δ�յ����ݷ��ء�����ͨ�����Ƿ�������ȷ��Э���Ƿ�ѡ�ԣ����ճ�ʱ @ref LED_SetReceiveTimeout �Ƿ����õ�̫��(������100ms����)�� */
    SDK_RECEIVE_UNKNOWN = -34,/**< -34:LED����δ֪�����ݣ��յ�������δ���塣���SDK�İ汾�Ƿ���µ����¡� */
    SDK_RECEIVE_CHECKERROR = -35,/**< -35:LED����У��������ݰ���У�����ݳ������Э���Ƿ�ѡ�ԡ� */
    SDK_RECEIVE_FUNCTIONUNDEFINED = -36,/**< -36:LED���ع�����δ���壬����LED�̼�δ���µ����°汾�� */
    SDK_RECEIVE_LENGTHERROR = -37,/**< -37:LED�������ݰ����ȴ���SDK���ú���ʱ�����Ƿ���ȷ�� */
    SDK_RECEIVE_DATAERROR = -38,/**< -38:LED�������ݰ������ݴ��󣬲�����������Χ��̼�δ���¡� */
    SDK_LED_NOTFUNCTION = -39,/**< -39:LEDû��������ܡ���LED�Ĳ���SDK��δ���巽���� */
    SDK_RECEIVE_ADDRESSERROR = -40,/**< -39:LED�������ݰ��е�ַ���󣬵�ַ��������Χ��̼�δ���¡� */
};


/** @brief ���ȼ���ö�� */
typedef enum LED_BRIGTH_e
{
    LED_BRIGTH_AUTO = 0xff,/**< �Զ�����(������ӵĹ��������Զ�����) */
    LED_BRIGTH_L1 = 0,/**< 0:���ȼ���1 */
    LED_BRIGTH_L2,/**< 1:���ȼ���2 */
    LED_BRIGTH_L3,/**< 2:���ȼ���3 */
    LED_BRIGTH_L4,/**< 3:���ȼ���4 */
    LED_BRIGTH_L5,/**< 4:���ȼ���5 */
    LED_BRIGTH_L6,/**< 5:���ȼ���6 */
    LED_BRIGTH_L7,/**< 6:���ȼ���7 */
    LED_BRIGTH_L8,/**< 7:���ȼ���8 */
    LED_BRIGTH_L9,/**< 8:���ȼ���9 */
    LED_BRIGTH_L10,/**< 9:���ȼ���10 */
    LED_BRIGTH_L11,/**< 10:���ȼ���11 */
    LED_BRIGTH_L12,/**< 11:���ȼ���12 */
    LED_BRIGTH_L13,/**< 12:���ȼ���13 */
    LED_BRIGTH_L14,/**< 13:���ȼ���14 */
    LED_BRIGTH_L15,/**< 14:���ȼ���15 */
    LED_BRIGTH_L16,/**< 15:���ȼ���16 */
}
LED_BRIGTH_e;

/** @brief ���뷽ʽ */
typedef enum LED_ALIGN_e
{
    ALIGN_NONE = 0,     //!< 0����ָ�����뷽ʽ,��LED�Զ�ѡ��
    ALIGN_LEFT = 1,     //!< 1�������
    ALIGN_RIGHT = 2,    //!< 2���Ҷ���
    ALIGN_CENTER = 4,   //!< 4������
}
LED_ALIGN_e;


#define LED_SCOLL_OFFINPULL     (0x01)  /**< �رտ�ʼ����ʱ��Ļ����� @ref LED_ScrollStyle_t */
#define LED_SCOLL_OFFOUTPULL    (0x02)  /**< �ر���ɹ���ʱ��Ļ����� @ref LED_ScrollStyle_t  */

/** @brief LEDɨ��ģʽ�ṹ�� */
typedef struct LED_ScanMode_t
{
    uint8_t ScanMode;/**< ɨ�跽ʽ,1/16ɨ�跽ʽ����Ϊ16��1/4ɨ������Ϊ4 */
    uint8_t AddrSize;/**< ɨ���ַ��С��ͨ������Ϊ16��P20������8 */
    uint8_t OEPolar;/**< OE�źż���,�ߵ�ƽ��Ч����Ϊ1,�͵�ƽ��Ч����0 */
    uint8_t STPolar;/**< �����źż��ԣ��ߵ�ƽ��Ч����Ϊ1,�͵�ƽ��Ч����0 */
    uint8_t CLKPolar;/**< ʱ���źż��ԣ���������Ч����1���½�����Ч����0 */
    uint8_t DataPolar;/**< �����źż��ԣ��ߵ�ƽ��Ч����Ϊ1,�͵�ƽ��Ч����0 */
}
LED_ScanMode_t;



#ifdef __cplusplus
}
#endif



#endif // __LEDSDK_H_INCLUDED
