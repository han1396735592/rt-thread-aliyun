
#include "LEDLIB.h"


void SdkTestPack()
{
    //----------------------------- �Լ���װ���ݰ� ----------------------------------------
    //-------- ������ο� LED_PackInit ����ʵ��Դ�� (LED_SerialPort.cpp) ------------------
    // ���ຯ����ο� PackInit.h
    //����ʹ�÷�װ�õĺ���

    char pack[LEDPack_Size];     //���ݰ�����,��СΪ���ݰ����ֵ
    int sendsize =0;    // Ҫ���͵����ݴ�С
    uint8_t ledid = 1;
    int n = 0;
    LED_ScanMode_t scanmode; // ɨ��ģʽ�ṹ��

    LED_SetReceiveTimeout(800); // ���� SDK ���ճ�ʱʱ�� ms

    scanmode.ScanMode = 16;
    scanmode.AddrSize = 16;
    scanmode.DataPolar = 0;
    scanmode.OEPolar = 1;
    scanmode.STPolar = 1;
    scanmode.CLKPolar = 1;

    // ���� ɨ�跽ʽ
    sendsize = PackInit_SetScanMode((LED_Pack_t *)pack,ledid,&scanmode);

    if (sendsize >0) //�ж��Ƿ��ʼ���ɹ�
    {
        n = LED_SendPack(ledid,pack,sendsize);//�������ݰ��������շ���ֵ
        if (n != 0 )
        {
            // ���ó��� ������鿴 ö�ٱ��� SDK_RECEIVE_e
        }
    }
}


// ���÷�װ�õĺ���
void SdkTest()
{

    uint8_t ledid = 1;
    int n = 0;
    LED_ScanMode_t scan;

    LED_SetReceiveTimeout(800); // ���� SDK ���ճ�ʱʱ�� ms

    //-----------------------------  ----------------------------------------
    n = LED_SetSelfCheck(ledid,true,true,true,true);// �Լ�����
    if (n != 0 )
    {
        // ���ó��� ������鿴 ö�ٱ��� SDK_RECEIVE_e
        // ���� ������ ����ֵ �ж�ʡ��
    }

    // ɨ�跽ʽ����1 --- ���ṹ��ģʽ����
    scan.ScanMode = 16;
    scan.AddrSize = 16;
    scan.CLKPolar = 1;
    scan.DataPolar = 1;
    scan.STPolar = 1;
    scan.OEPolar = 0;
    LED_SetScanMode(ledid,&scan);


    LED_SetPixelSize(ledid,64,16);//����LED����С
    LED_SetBrushColour(ledid,3);//���û�����ɫ

    LED_ShowGBK(ledid,0,"ShowGBK"); //��ʾ����
//    LED_ShowUnicode(ledid,0,L"ShowUnicode");

    LED_SetBootGBK(ledid,0,"Boot GBK"); // ������Ϣ
//    LED_SetBootUnicode(ledid,0,L"Boot Unicode");

    LED_SetEmergGBK(ledid,0,"EM GBK "); //Ӧ����Ϣ
//    LED_SetEmergUnicode(ledid,0,L"EM Unicode");

    LED_ShowImage(ledid,0,0,32,0);// ͼƬ��ʾ
    LED_SetBootImage(ledid,0,1,0,0);
    LED_SetEmergImage(ledid,0,0,0,0);

    LED_BlinkOn(ledid,100,100); //��˸����
    LED_BlinkOff(ledid);

    LED_DeltBlinkOn(ledid,100,200); // ����Ĭ����˸����
    LED_DeltBlinkOff(ledid);

    LED_SetAlignLine(ledid,0,ALIGN_CENTER);//�������ö��뷽ʽ
    LED_SetAlign(ledid,ALIGN_CENTER);//���������ж��뷽ʽ

    LED_SetDeltAlignLine(ledid,0,ALIGN_CENTER); //����Ĭ�϶��뷽ʽ
    LED_SetDeltAlign(ledid,ALIGN_CENTER);

    LED_ClearScreen(ledid);//����
    LED_ClearLine(ledid,2);//���ָ����

    // ��������
    LED_SetScrollTime(ledid,20,1000,0);
    LED_SetScrollStyle(ledid,LED_SCOLL_OFFINPULL|LED_SCOLL_OFFOUTPULL);
    LED_DeltScrollStyle(ledid,LED_SCOLL_OFFINPULL|LED_SCOLL_OFFOUTPULL);

    // �������� -- ��������
    LED_SetLineFont(ledid,0,5,7);   // �������� 5*7 ����
    LED_SetLineFont(ledid,1,6,12);  // �������� 6*12 �������� 12*12
    LED_SetLineFont(ledid,2,8,16);  // �������� 8*16 �������� 16*16
    LED_SetLineFont(ledid,3,12,24); // �������� 12*24 �������� 24*24
    LED_SetLineFont(ledid,3,16,32); // �������� 32*32 �������� 32*32

    // �������� -- ����Ĭ������
    LED_DeltLineFont(ledid,0,5,7);   // �������� 5*7 ����
    LED_DeltLineFont(ledid,1,6,12);  // �������� 6*12 �������� 12*12
    LED_DeltLineFont(ledid,2,8,16);  // �������� 8*16 �������� 16*16
    LED_DeltLineFont(ledid,3,12,24); // �������� 12*24 �������� 24*24
    LED_DeltLineFont(ledid,3,16,32); // �������� 32*32 �������� 32*32

    LED_SetBrigth(ledid,0);//��������
    LED_Reset(ledid);// ����LED
    LED_FactoryReset(ledid);//�ָ���������
    LED_ChangeID(ledid,2); // �޸�LED ID
}
