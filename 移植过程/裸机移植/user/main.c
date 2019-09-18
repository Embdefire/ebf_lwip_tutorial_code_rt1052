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
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "./systick/bsp_systick.h"
#include "./led/bsp_led.h"   

#include "ping.h"
#include "lwip/timeouts.h"
#include "lwip/init.h"
#include "lwip/tcpip.h"
#include "netif/ethernet.h"
#include "ethernetif.h"
#include "sys_arch.h"


extern int lwip_ping_test(void);

/*******************************************************************
 * Prototypes
 *******************************************************************/
int flag = 0;

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
  */
int main(void)
{ 
	  /* ������Ӳ����ʼ�� */
		BSP_Init();
	
		struct netif gnetif;
		ip4_addr_t ipaddr;
		ip4_addr_t netmask;
		ip4_addr_t gw;
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
		/*ping ��ʼ��*/
   // ping_init(&gw);
		/*��ӡ��ʾ��Ϣ*/
    PRINTF("\r\n************************************************\r\n");
    PRINTF(" PING example\r\n");
    PRINTF("************************************************\r\n");
    PRINTF(" IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&ipaddr)[0], ((u8_t *)&ipaddr)[1],
           ((u8_t *)&ipaddr)[2], ((u8_t *)&ipaddr)[3]);
    PRINTF(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&netmask)[0], ((u8_t *)&netmask)[1],
           ((u8_t *)&netmask)[2], ((u8_t *)&netmask)[3]);
    PRINTF(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *)&gw)[0], ((u8_t *)&gw)[1],
           ((u8_t *)&gw)[2], ((u8_t *)&gw)[3]);
    PRINTF("************************************************\r\n");

    while (1)
    {
			//�����������պ���
        ethernetif_input(&gnetif);
				/* ���� LwIP ��ʱ */
        sys_check_timeouts();
    }

}

