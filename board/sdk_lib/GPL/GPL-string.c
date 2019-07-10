/**
  ******************************************************************************
  * @file
  * @author     SPING
  * @version    V0.0.1
  * @date       2016-10-29
  * @copyright  sping520@gmail.com
  * @brief
  ******************************************************************************
  * @note
  * @attention
  * <P style="FONT-SIZE:13px;"><center>&copy; COPYRIGHT 2013 SPING </center></P>
  *******************************************************************************
  */


#include "GPL-string.h"


//uint8_t  *memcpy(uint8_t *dest, const uint8_t *src, size_t n)
//{
//    while(n--)
//    {
//        *((uint8_t *)dest)++ = *(const uint8_t *)src++;
//    }
//    return dest;
//}


void ZeroMemory(uint8_t *Destination,size_t Length )
{
    while(Length--)
    {
        *(uint8_t *)Destination = 0;
        Destination++;
    }
}

int wcslen(const wchar_t *str)
{
    int len = 0;
    while(*str++)
    {
        len++;
    }
    return len;
}




