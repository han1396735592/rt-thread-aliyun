
#ifndef __GPL_TYPEDEF_H__
#define __GPL_TYPEDEF_H__

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

#define DLL_EXPORT

#if (defined Compile_KeilC51)
#   include <string.h>
#   include "GPL-Typedef_KeilC51.h"

#elif (Compile_MDKARM)
#   include <stdint.h>
#   include <string.h>
typedef uint16_t              wchar_t;
typedef enum {false = 0, true = !false} bool;
int wcslen(const wchar_t *str);
void ZeroMemory(uint8_t *Destination,size_t Length);

#elif (Compile_IARSTM8)
#   include "stm8s.h"
#   include <string.h>
typedef uint16_t              wchar_t;
int wcslen(const wchar_t *str);
void ZeroMemory(uint8_t *Destination,size_t Length);

#define false    (FALSE)
#define true     (TRUE)

#else
#endif





#ifdef __cplusplus
}
#endif


#endif // __GPL_TYPEDEF_H__
