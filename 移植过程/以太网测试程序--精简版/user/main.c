/**
  ******************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   Һ����ʾӢ��
  ******************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  i.MXRT1052������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************
  */
#include <stdio.h>

#include "fsl_debug_console.h"
#include "fsl_elcdif.h"


#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "./delay/core_delay.h"   

#include "./led/bsp_led.h" 

#include "ping/ping.h"
#include "lwip/timeouts.h"
#include "lwip/init.h"
#include "netif/ethernet.h"
#include "ethernetif.h"

extern int lwip_ping_test(void);

/*******************************************************************
 * Prototypes
 *******************************************************************/
#define SDRAM_TEST_FAIL  0
#define SDRAM_TEST_OK    1

#define ENET_TEST_FAIL   0
#define ENET_TEST_OK     1

/*******************************************************************
 * Variables
 *******************************************************************/

/*******************************************************************
 * Code
 *******************************************************************/

/**
  * @brief  ������
  * @param  ��
  * @retval ��
//*/
//int main(void)
//{ 
//	uint8_t result1,result2 =0;	

//	#if (!CPU_TS_INIT_IN_DELAY_FUNCTION)      
//		//ʹ��ʱ�����ʱ����ǰ������ʹ�ܼ�����
//		CPU_TS_TmrInit();
//	#endif

//	/* ��ʼ���ڴ汣����Ԫ */
//	BOARD_ConfigMPU();
//	/* ��ʼ������������ */
//	BOARD_InitPins();
//	/* ��ʼ��������ʱ�� */
//	BOARD_BootClockRUN();
//	/* ��ʼ�����Դ��� */
//	BOARD_InitDebugConsole();
//	/* ��ӡϵͳʱ�� */
//	PRINTF("\r\n");
//	PRINTF("*****��ӭʹ�� Ұ��i.MX RT1052 ������*****\r\n");
//	PRINTF("CPU:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_CpuClk));
//	PRINTF("AHB:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_AhbClk));
//	PRINTF("SEMC:            %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SemcClk));
//	PRINTF("SYSPLL:          %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllClk));
//	PRINTF("SYSPLLPFD0:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
//	PRINTF("SYSPLLPFD1:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
//	PRINTF("SYSPLLPFD2:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
//	PRINTF("SYSPLLPFD3:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));	

//	PRINTF("*****������̫��*****\r\n");	
//	/* ������̫������ */
//	if(lwip_ping_test())
//	{
//		result2 = ENET_TEST_FAIL;
//		PRINTF("*****��̫������ʧ��*****\r\n");	
//	}
//	else
//	{      
//		result2 = ENET_TEST_OK;
//		PRINTF("*****��̫�����Գɹ�*****\r\n");	
//	}		
//	/* ��ʼ��LED */
//	LED_GPIO_Config();
//	
//	while(1);
//	
//}

#define DEST_IP_ADDR0               192
#define DEST_IP_ADDR1               168
#define DEST_IP_ADDR2                 0
#define DEST_IP_ADDR3               232

#define DEST_PORT                  5001

#define UDP_SERVER_PORT            5002   /* define the UDP local connection port */
#define UDP_CLIENT_PORT            5002   /* define the UDP remote connection port */

#define LOCAL_PORT                 5001

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0                    192
#define IP_ADDR1                    168
#define IP_ADDR2                      0
#define IP_ADDR3                    112

/*NETMASK*/
#define NETMASK_ADDR0               255
#define NETMASK_ADDR1               255
#define NETMASK_ADDR2               255
#define NETMASK_ADDR3                 0

/*Gateway Address*/
#define GW_ADDR0                    192
#define GW_ADDR1                    168
#define GW_ADDR2                      0
#define GW_ADDR3                      1
/* MAC address configuration. */
#define configMAC_ADDR                     \
    {                                      \
        0x02, 0x12, 0x13, 0x10, 0x15, 0x11 \
    }

/* Address of PHY interface. */
#define EXAMPLE_PHY_ADDRESS 0x00U
		/* System clock name. */
#define EXAMPLE_CLOCK_NAME kCLOCK_CoreSysClk

struct netif gnetif;
ip4_addr_t ipaddr;
ip4_addr_t netmask;
ip4_addr_t gw;
		
void TCPIP_Init(void)
{
		/*����������Ϣ*/
    ethernetif_config_t fsl_enet_config0 = {
        .phyAddress = EXAMPLE_PHY_ADDRESS,
        .clockName = EXAMPLE_CLOCK_NAME,
        .macAddress = configMAC_ADDR,
    };
 time_init();
		/* ����ӿ����� */
    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
		/*LWIP��ʼ��*/
    lwip_init();

		netif_add(&gnetif, &ipaddr, &netmask, &gw, &fsl_enet_config0,
                       ethernetif0_init, ethernet_input);
    netif_set_default(&gnetif);
    netif_set_up(&gnetif);
		ping_init(&gw);

}

int main(void)
{
	BSP_Init();
	TCPIP_Init();
	while(1)
	{
       //�����������պ���
     ethernetif_input(&gnetif);

     //����LwIP�ж�ʱ�¼�
     sys_check_timeouts();

	
	}

}

/****************************END OF FILE**********************/
