/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-30     Rick       the first version
 */
#include "rtthread.h"
#include "rtdevice.h"
#include "pin_config.h"
#include "wifi-uart.h"
#include "wifi.h"
#include "wifi-service.h"
#include "led.h"

#define DBG_TAG "wifi_service"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static rt_thread_t WiFi_Service_Thread = RT_NULL;

void Show_WiFi(void)
{
    beep_start(0,10);//beep 5 times
    if(mcu_get_wifi_work_state()==0x03)
    {
        LOG_D("wifi is AP\r\n");
    }
    else
    {
        LOG_D("wifi is fail\r\n");
    }
}
MSH_CMD_EXPORT(Show_WiFi,Show_WiFi);
void Exit_WiFi(void)
{
    beep_start(0,11);//beep 3 times
}
MSH_CMD_EXPORT(Exit_WiFi,Exit_WiFi);

rt_timer_t Reset_WiFi_Timer = RT_NULL;
uint8_t Reset_WiFi_Counter = RT_NULL;
void Reset_WiFi(void)
{
    just_ring();
    mcu_reset_wifi();
    Reset_WiFi_Counter = 0;
    rt_timer_start(Reset_WiFi_Timer);
    LOG_D("Wait For Reset Result\r\n");
}
void Reset_WiFi_Callback(void *parameter)
{
    if(Reset_WiFi_Counter<3 && mcu_get_reset_wifi_flag()!=1)
    {
        Reset_WiFi_Counter++;
        just_ring();
        mcu_reset_wifi();
        LOG_D("Wifi Reset Retry Num is %d\r\n",Reset_WiFi_Counter);
    }
    else if(Reset_WiFi_Counter<3 && mcu_get_reset_wifi_flag()==1)
    {
        Reset_WiFi_Counter++;
        LOG_D("Wifi Reset Success\r\n");
        rt_timer_stop(Reset_WiFi_Timer);
    }
    else if(Reset_WiFi_Counter>=3)
    {
        LOG_D("Wifi Reset Fail\r\n");
        rt_timer_stop(Reset_WiFi_Timer);
    }
}
void service_callback(void *parameter)
{
    while(1)
    {
        wifi_uart_service();
        rt_thread_mdelay(5);
    }
}
void wifi_service_init(void)
{
    Reset_WiFi_Timer = rt_timer_create("Reset_WiFi_Timer", Reset_WiFi_Callback, RT_NULL, 1000, RT_TIMER_FLAG_SOFT_TIMER|RT_TIMER_FLAG_PERIODIC);
    WiFi_Service_Thread = rt_thread_create("wifi-service", service_callback, RT_NULL, 2048, 10, 10);
    if(WiFi_Service_Thread!=RT_NULL)rt_thread_startup(WiFi_Service_Thread);
}
MSH_CMD_EXPORT(wifi_service_init,wifi_service_init);
