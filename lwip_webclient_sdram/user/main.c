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
#include "client.h"

////���ñ������嵽��EXRAM�������ĺ�
//#define __EXRAM  __attribute__ ((section ("EXRAM")))

//���ڴ涨����SDRAM��
//uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __EXRAM;
uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] ;

////�������鵽SDRAM
//uint8_t testGrup[3] __EXRAM ={1,2,3};
////�������鵽SRAM
//uint8_t testGrup2[3] ={1,2,3};

/**************************** ������ ********************************/
/* 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ�������������������������������Լ�����ô
 * ����������ΪNULL��
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* ���������� */
static TaskHandle_t Test1_Task_Handle = NULL;/* LED������ */
static TaskHandle_t Test2_Task_Handle = NULL;/* KEY������ */

/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬�����ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */

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
static void AppTaskCreate(void);/* ���ڴ������� */

static void Test1_Task(void* pvParameters);/* Test1_Task����ʵ�� */
static void Test2_Task(void* pvParameters);/* Test2_Task����ʵ�� */

extern void TCPIP_Init(void);

/*****************************************************************
  * @brief  ������
  * @param  ��
  * @retval ��
  * @note   ��һ����������Ӳ����ʼ�� 
            �ڶ���������APPӦ������
            ������������FreeRTOS����ʼ���������
  ****************************************************************/
int main(void)
{	
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  
  /* ������Ӳ����ʼ�� */
  BSP_Init();
//  Netif_Config();
  /* ����AppTaskCreate���� */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* ������ں��� */
                        (const char*    )"AppTaskCreate",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* ������ƿ�ָ�� */ 
  /* ����������� */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* �������񣬿������� */
  else
    return -1;  
  
  while(1);   /* ��������ִ�е����� */    
}


/***********************************************************************
  * @ ������  �� AppTaskCreate
  * @ ����˵���� Ϊ�˷���������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
//  Netif_Config();
  TCPIP_Init();
  
  PRINTF("��������ʾ�������ȡ��ҳ����\n\n");
  
  PRINTF("��������ģ�����£�\n\t ����<--����-->·��<--����-->������\n\n");
  
  PRINTF("ʵ����ʹ��TCPЭ�鴫�����ݣ���������ΪTCP Server\n\n");
  
  PRINTF("�����̵�IP��ַ����User/arch/sys_arch.h�ļ����޸�\n\n");
    
  PRINTF("�����̲ο�<<LwIPӦ��ʵս����ָ��>>��19�� HTTP Э��\n\n");
  
  client_init();
  
  taskENTER_CRITICAL();           //�����ٽ���

  /* ����Test1_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )Test1_Task, /* ������ں��� */
                        (const char*    )"Test1_Task",/* �������� */
                        (uint16_t       )512,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )1,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&Test1_Task_Handle);/* ������ƿ�ָ�� */
  if(pdPASS == xReturn)
    PRINTF("Create Test1_Task sucess...\r\n");
  
  /* ����Test2_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )Test2_Task,  /* ������ں��� */
                        (const char*    )"Test2_Task",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )2, /* ��������ȼ� */
                        (TaskHandle_t*  )&Test2_Task_Handle);/* ������ƿ�ָ�� */ 
  if(pdPASS == xReturn)
    PRINTF("Create Test2_Task sucess...\n\n");
  
  vTaskDelete(AppTaskCreate_Handle); //ɾ��AppTaskCreate����
  
  taskEXIT_CRITICAL();            //�˳��ٽ���
}



/**********************************************************************
  * @ ������  �� Test1_Task
  * @ ����˵���� Test1_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Test1_Task(void* parameter)
{	
  while (1)
  {
    
    LED1_TOGGLE;
//    PRINT_DEBUG("LED1_TOGGLE\n");
    vTaskDelay(1000);/* ��ʱ1000��tick */
  }
}

/**********************************************************************
  * @ ������  �� Test2_Task
  * @ ����˵���� Test2_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
extern struct netif gnetif;
static void Test2_Task(void* parameter)
{	 
  while (1)
  {
//    LED2_TOGGLE;
//    PRINT_DEBUG("LED2_TOGGLE\n");
    vTaskDelay(2000);/* ��ʱ2000��tick */
  }
}



/********************************END OF FILE****************************/
