#ifndef _DEBUG_H
#define _DEBUG_H
/************************************************************
  * @brief   debug.h
  * @date    2018-xx-xx
  * @version v1.0
  * @note    此文件用于打印日志信息
  ***********************************************************/
/**
* @name Debug print 
* @{
*/
#include "fsl_debug_console.h"
#ifndef PRINT_DEBUG_ENABLE
#define PRINT_DEBUG_ENABLE		1		/* 打印调试信息 */
#endif

#ifndef PRINT_ERR_ENABLE
#define PRINT_ERR_ENABLE			1 	/* 打印错误信息 */
#endif

#ifndef PRINT_INFO_ENABLE
#define PRINT_INFO_ENABLE			1		/* 打印个人信息 */
#endif

#if PRINT_DEBUG_ENABLE
#define PRINT_DEBUG(fmt, args...) 	 do{(PRINTF("\r\n[DEBUG] >> "), PRINTF(fmt, ##args));}while(0)     
#else
#define PRINT_DEBUG(fmt, args...)	     
#endif

#if PRINT_ERR_ENABLE
#define PRINT_ERR(fmt, args...) 	 do{(PRINTF("\r\n[ERR] >> "), PRINTF(fmt, ##args));}while(0)     
#else
#define PRINT_ERR(fmt, args...)	       
#endif

#if PRINT_INFO_ENABLE
#define PRINT_INFO(fmt, args...) 	 do{(PRINTF("\r\n[INFO] >> "), PRINTF(fmt, ##args));}while(0)     
#else
#define PRINT_INFO(fmt, args...)	       
#endif

/**@} */
	
//针对不同的编译器调用不同的stdint.h文件
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
#endif

/* 断言 Assert */
#define AssertCalled(char,int) 	PRINTF("\nError:%s,%d\r\n",char,int)
#define ASSERT(x)   if((x)==0)  AssertCalled(__FILE__,__LINE__)
  
typedef enum 
{
	ASSERT_ERR = 0,								/* 错误 */
	ASSERT_SUCCESS = !ASSERT_ERR	/* 正确 */
} Assert_ErrorStatus;


#define	FALSE  0		/* 假 */
#define	TRUE  !FALSE	/* 真 */



#endif /* __DEBUG_H */

