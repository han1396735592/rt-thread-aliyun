
#ifndef __GPL_TYPEDEF_KEILC51_H__
#define __GPL_TYPEDEF_KEILC51_H__

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

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef short               int16_t;
typedef unsigned short      uint16_t;
typedef unsigned long       uint32_t;
typedef uint16_t            wchar_t;

typedef enum {false = 0, true = !false} bool;

int wcslen(const wchar_t *str);
void ZeroMemory(uint8_t *Destination,size_t Length);

#ifdef __cplusplus
}
#endif


#endif // __GPL_TYPEDEF_H__
