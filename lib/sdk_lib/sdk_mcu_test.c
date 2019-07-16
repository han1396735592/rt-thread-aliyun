
#include "LEDLIB.h"


void SdkTestPack()
{
    //----------------------------- 自己封装数据包 ----------------------------------------
    //-------- 更多请参考 LED_PackInit 函数实现源码 (LED_SerialPort.cpp) ------------------
    // 更多函数请参考 PackInit.h
    //建议使用封装好的函数

    char pack[LEDPack_Size];     //数据包缓存,大小为数据包最大值
    int sendsize =0;    // 要发送的数据大小
    uint8_t ledid = 1;
    int n = 0;
    LED_ScanMode_t scanmode; // 扫描模式结构体

    LED_SetReceiveTimeout(800); // 设置 SDK 接收超时时间 ms

    scanmode.ScanMode = 16;
    scanmode.AddrSize = 16;
    scanmode.DataPolar = 0;
    scanmode.OEPolar = 1;
    scanmode.STPolar = 1;
    scanmode.CLKPolar = 1;

    // 设置 扫描方式
    sendsize = PackInit_SetScanMode((LED_Pack_t *)pack,ledid,&scanmode);

    if (sendsize >0) //判断是否初始化成功
    {
        n = LED_SendPack(ledid,pack,sendsize);//发送数据包，并接收返回值
        if (n != 0 )
        {
            // 调用出错 详情请查看 枚举变量 SDK_RECEIVE_e
        }
    }
}


// 调用封装好的函数
void SdkTest()
{

    uint8_t ledid = 1;
    int n = 0;
    LED_ScanMode_t scan;

    LED_SetReceiveTimeout(800); // 设置 SDK 接收超时时间 ms

    //-----------------------------  ----------------------------------------
    n = LED_SetSelfCheck(ledid,true,true,true,true);// 自检设置
    if (n != 0 )
    {
        // 调用出错 详情请查看 枚举变量 SDK_RECEIVE_e
        // 后面 代码中 返回值 判定省略
    }

    // 扫描方式设置1 --- 按结构体模式设置
    scan.ScanMode = 16;
    scan.AddrSize = 16;
    scan.CLKPolar = 1;
    scan.DataPolar = 1;
    scan.STPolar = 1;
    scan.OEPolar = 0;
    LED_SetScanMode(ledid,&scan);


    LED_SetPixelSize(ledid,64,16);//设置LED屏大小
    LED_SetBrushColour(ledid,3);//设置画笔颜色

    LED_ShowGBK(ledid,0,"ShowGBK"); //显示文字
//    LED_ShowUnicode(ledid,0,L"ShowUnicode");

    LED_SetBootGBK(ledid,0,"Boot GBK"); // 开机信息
//    LED_SetBootUnicode(ledid,0,L"Boot Unicode");

    LED_SetEmergGBK(ledid,0,"EM GBK "); //应急信息
//    LED_SetEmergUnicode(ledid,0,L"EM Unicode");

    LED_ShowImage(ledid,0,0,32,0);// 图片显示
    LED_SetBootImage(ledid,0,1,0,0);
    LED_SetEmergImage(ledid,0,0,0,0);

    LED_BlinkOn(ledid,100,100); //闪烁设置
    LED_BlinkOff(ledid);

    LED_DeltBlinkOn(ledid,100,200); // 开机默认闪烁设置
    LED_DeltBlinkOff(ledid);

    LED_SetAlignLine(ledid,0,ALIGN_CENTER);//按行设置对齐方式
    LED_SetAlign(ledid,ALIGN_CENTER);//设置所有行对齐方式

    LED_SetDeltAlignLine(ledid,0,ALIGN_CENTER); //开机默认对齐方式
    LED_SetDeltAlign(ledid,ALIGN_CENTER);

    LED_ClearScreen(ledid);//清屏
    LED_ClearLine(ledid,2);//清除指定行

    // 滚动设置
    LED_SetScrollTime(ledid,20,1000,0);
    LED_SetScrollStyle(ledid,LED_SCOLL_OFFINPULL|LED_SCOLL_OFFOUTPULL);
    LED_DeltScrollStyle(ledid,LED_SCOLL_OFFINPULL|LED_SCOLL_OFFOUTPULL);

    // 字体设置 -- 缓存字体
    LED_SetLineFont(ledid,0,5,7);   // 设置字体 5*7 点阵
    LED_SetLineFont(ledid,1,6,12);  // 设置字体 6*12 点阵，中文 12*12
    LED_SetLineFont(ledid,2,8,16);  // 设置字体 8*16 点阵，中文 16*16
    LED_SetLineFont(ledid,3,12,24); // 设置字体 12*24 点阵，中文 24*24
    LED_SetLineFont(ledid,3,16,32); // 设置字体 32*32 点阵，中文 32*32

    // 字体设置 -- 开机默认字体
    LED_DeltLineFont(ledid,0,5,7);   // 设置字体 5*7 点阵
    LED_DeltLineFont(ledid,1,6,12);  // 设置字体 6*12 点阵，中文 12*12
    LED_DeltLineFont(ledid,2,8,16);  // 设置字体 8*16 点阵，中文 16*16
    LED_DeltLineFont(ledid,3,12,24); // 设置字体 12*24 点阵，中文 24*24
    LED_DeltLineFont(ledid,3,16,32); // 设置字体 32*32 点阵，中文 32*32

    LED_SetBrigth(ledid,0);//亮度设置
    LED_Reset(ledid);// 重启LED
    LED_FactoryReset(ledid);//恢复出厂设置
    LED_ChangeID(ledid,2); // 修改LED ID
}
