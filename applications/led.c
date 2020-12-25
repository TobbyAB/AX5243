#include <agile_led.h>
#include <stdlib.h>
#include "led.h"
#include "pin_config.h"

static agile_led_t *led0 = RT_NULL;
static agile_led_t *led1 = RT_NULL;
static agile_led_t *beep = RT_NULL;

#define DBG_TAG "led"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

void led_Init(void)
{
    if(led0 == RT_NULL)
    {
        led0 = agile_led_create(LED0_PIN, PIN_LOW, "100,200", -1);
        LOG_D("LED_0 Init Success\r\n");
    }

    if(led1 == RT_NULL)
    {
        led1 = agile_led_create(LED1_PIN, PIN_LOW, "200,100", -1);
        LOG_D("LED_1 Init Success\r\n");
    }

    if(beep == RT_NULL)
    {
        beep = agile_led_create(0, PIN_HIGH, "200,100", -1);
        LOG_D("Beep Init Success\r\n");
    }

}
void beep_start(uint8_t led_id,int mode)
{
    switch (mode)
    {
    case 0:
        agile_led_set_light_mode(beep, "500,5000", -1);
        agile_led_start(beep);
        if(led_id)//绿灯
        {
            agile_led_set_light_mode(led1, "500,1000", -1);
            agile_led_start(led1);
            led_Stop(0);
        }
        else//红灯
        {
            agile_led_set_light_mode(led0, "500,1000", -1);
            agile_led_start(led0);
            led_Stop(1);
        }
        break;

    case 1:
        agile_led_set_light_mode(beep, "500,250,500,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "500,250,500,5000", -1);
            agile_led_start(led1);
            led_Stop(0);
        }
        else
        {
            agile_led_set_light_mode(led0, "500,250,500,5000", -1);
            agile_led_start(led0);
            led_Stop(1);
        }
        break;

    case 2:
        agile_led_set_light_mode(beep, "500,250,500,250,500,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "500,250,500,250,500,5000", -1);
            agile_led_start(led1);
            led_Stop(0);
        }
        else
        {
            agile_led_set_light_mode(led0, "500,1000", -1);
            agile_led_start(led0);
            led_Stop(1);
        }
        break;
    case 3:
        agile_led_set_light_mode(beep, "500,250,500,250,500,250,500,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "500,250,500,250,500,250,500,5000", -1);
            agile_led_start(led1);
            led_Stop(0);
        }
        else
        {
            agile_led_set_light_mode(led0, "500,1000", -1);
            agile_led_start(led0);
            led_Stop(1);
        }
        break;
    case 4:
        agile_led_set_light_mode(beep, "500,250,500,250,500,250,500,250,500,250", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "500,250,500,250,500,250,500,250,500,5000", -1);
            agile_led_start(led1);
            led_Stop(0);
        }
        else
        {
            agile_led_set_light_mode(led0, "500,1000", -1);
            agile_led_start(led0);
            led_Stop(1);
        }
        break;
    case 5:
        agile_led_set_light_mode(beep, "500,250,500,250,500,250,500,250,500,250,500,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "500,250,500,250,500,250,500,250,500,250,500,5000", -1);
            agile_led_start(led1);
            led_Stop(0);
        }
        else
        {
            agile_led_set_light_mode(led0, "500,1000", -1);
            agile_led_start(led0);
            led_Stop(1);
        }
        break;
    }
}
void beep_stop(void)
{
    rt_pin_write(0, 0);
    agile_led_stop(beep);
}
void key_down(void)
{
    led_Stop(0);
    led_Stop(2);
    rt_thread_mdelay(10);
    agile_led_set_light_mode(beep, "100,100", 1);
    agile_led_set_light_mode(led0, "100,100", 1);
    agile_led_start(beep);
    agile_led_start(led0);
}
void led_Long_Start(uint8_t led_id)
{
    switch (led_id)
    {
    case 0:
        agile_led_set_light_mode(led0, "1000,0", -1);
        agile_led_start(led0);
        led_Stop(1);
        break;

    case 1:
        agile_led_set_light_mode(led1, "1000,0", -1);
        agile_led_start(led1);
        led_Stop(0);
        break;
    }
}
void led_Slow_Start(uint8_t led_id,int count)
{
    switch (led_id)
    {
    case 0:
        agile_led_set_light_mode(led0, "500,1000", count);
        agile_led_start(led0);
        led_Stop(1);
        break;

    case 1:
        agile_led_set_light_mode(led1, "500,1000", count);
        agile_led_start(led1);
        led_Stop(0);
        break;
    }
}
void led_Fast_Start(uint8_t led_id,int count)
{
    switch (led_id)
    {
    case 0:
        agile_led_set_light_mode(led0, "200,300", count);
        agile_led_start(led0);
        led_Stop(1);
        break;

    case 1:
        agile_led_set_light_mode(led1, "200,300", count);
        agile_led_start(led1);
        led_Stop(0);
        break;
    }

}
void led_Stop(uint8_t led_id)
{
    switch (led_id)
    {
    case 0:
        agile_led_stop(led0);
        rt_pin_write(LED0_PIN, 1);
        break;

    case 1:
        agile_led_stop(led1);
        rt_pin_write(LED1_PIN, 1);
        break;

    case 2:
        agile_led_stop(beep);
        rt_pin_write(0, 0);
        break;
    }
}