/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   FreeRTOS V9.0.0 + i.MXRT LwIP
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� i.MX RT ȫϵ�п����� 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "debug.h"
#include "fsl_iomuxc.h"
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "tcpecho.h"
#include "enet_ethernetif.h"
#include "sys_arch.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"

/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */


/******************************* �궨�� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩ�궨�塣
 */


/*
*************************************************************************
*                             ��������
*************************************************************************
*/
extern void TCPIP_Init(void);

/*****************************************************************
  * @brief  ������
  * @param  ��
  * @retval ��
  ****************************************************************/
int flag = 0;
int main(void)
{	

  /* ������Ӳ����ʼ�� */
	BSP_Init();
	TCPIP_Init();
	PRINTF("LwIP�汾��%s\n",LWIP_VERSION_STRING);
	PRINTF("pingʵ������\n");

	PRINTF("ʹ��ͬһ���������еĵ���ping������ĵ�ַ���ɽ��в���\n");

	PRINTF("����IP�Ͷ˿�: %d.%d.%d.%d\n",IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
	TCP_Echo_Init();
	while (1)
	{  
			/* ����̫���������ж�ȡ���ݰ�������LwIP���� */
			if(flag)
			{
				flag = 0;
				LED2_TOGGLE;
				//�����������պ���
				ethernetif_input(&gnetif);
			}
			/* ���� LwIP ��ʱ */
			sys_check_timeouts();
	}	

}
