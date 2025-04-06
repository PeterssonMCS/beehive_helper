#include "hal_def.h"
#include <stdio.h>

const int kPinList[PIN_LIST_MAX] = { 
    #define MACRO( NAME , PIN ) PIN,
    PIN_LIST( MACRO )
    #undef MACRO 
};

HAL_LIST(GEN_VAR)
HAL_LIST(GET_VAR)

void HAL_Init()
{
    HAL_LIST( HAL_INIT )
}

bool periodic_callback( struct repeating_timer* timer )
{
    OS_Tick();
    return true;
}

GEN_CFG( TIMER )
{
    bool success = false;
    switch( id )
    {
        case TIMER_OS_ID:
            cfg->type = TIMER_PERIODIC;
            cfg->timeout = 1;
            cfg->periodic_callback = periodic_callback;
            cfg->alarm_callback = NULL;
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( D1306 )
{
    bool success = false;
    switch( id )
    {
        case D1306_OLED_ID:
            cfg->external_vcc = false;
            cfg->width = 128;
            cfg->height = 64;
            cfg->i2c_cfg.address = 0x3C;
            cfg->i2c_cfg.frequency = 400*1000;
            cfg->i2c_cfg.i2c_id = 1;
            cfg->i2c_cfg.pin_sda = kPinList[DISPLAY_SDA_ID];
            cfg->i2c_cfg.pin_sdl = kPinList[DISPLAY_SCL_ID];
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( AHT10 )
{
    bool success = false;
    switch( id )
    {
        case AHT10_SENSOR_ID:
            cfg->i2c_cfg.address = 0x38;
            cfg->i2c_cfg.frequency = 4*1000;
            cfg->i2c_cfg.i2c_id = 0;
            cfg->i2c_cfg.pin_sda = kPinList[AHT10_SDA_ID];
            cfg->i2c_cfg.pin_sdl = kPinList[AHT10_SCL_ID];
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( JOYSTICK )
{
    bool success = false;
    switch( id )
    {
        case JOYSTICK_JOYSTICK_ID:
            cfg->x.pin = kPinList[JOYSTICK_X_ID];
            cfg->y.pin = kPinList[JOYSTICK_Y_ID];
            cfg->z.pin = kPinList[JOYSTICK_Z_ID];
            cfg->z.direction = 0;
            cfg->z.logic = 1;
            cfg->z.mode = 1;
            success = true;
        break;

        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( LED )
{
    bool success = false;
    switch( id )
    {
        case LED_RGB_ID:
            cfg->red.pin = kPinList[RGB_RED_ID];
            cfg->red.divider = 125;
            cfg->red.step = 100;
            cfg->red.period = 1000;
            cfg->red.duty = 0;
            
            cfg->green.pin = kPinList[RGB_GREEN_ID];
            cfg->green.divider = 125;
            cfg->green.step = 100;
            cfg->green.period = 1000;
            cfg->green.duty = 0;

            cfg->blue.pin = kPinList[RGB_BLUE_ID];
            cfg->blue.divider = 125;
            cfg->blue.step = 100;
            cfg->blue.period = 1000;
            cfg->blue.duty = 0;
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( BUZZER )
{
    bool success = false;
    switch( id )
    {
        /*
        case BUZZER_BUZZER_A_ID:
            cfg->pwm_cfg.pin = kPinList[BUZZER_A_ID];
            cfg->pwm_cfg.divider = 125;
            cfg->pwm_cfg.step = 100;
            cfg->pwm_cfg.period = 1000;
            cfg->pwm_cfg.duty = 100;
            success = true;
        break;
        */
        case BUZZER_BUZZER_B_ID:
            cfg->pwm_cfg.pin = kPinList[BUZZER_B_ID];
            cfg->pwm_cfg.divider = 125;
            cfg->pwm_cfg.step = 100;
            cfg->pwm_cfg.period = 1000;
            cfg->pwm_cfg.duty = 100;
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( BUTTON )
{
    bool success = false;
    switch( id )
    {
        case BUTTON_BUTTON_A_ID:
            cfg->gpio_cfg.pin = kPinList[BUTTON_A_ID];
            cfg->gpio_cfg.direction = 0;
            cfg->gpio_cfg.logic = 1;
            cfg->gpio_cfg.mode = 1;
            success = true;
        break;
        case BUTTON_BUTTON_B_ID:
            cfg->gpio_cfg.pin = kPinList[BUTTON_B_ID];
            cfg->gpio_cfg.direction = 0;
            cfg->gpio_cfg.logic = 1;
            cfg->gpio_cfg.mode = 1;
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( GPIO )
{
    bool success = false;
    switch( id )
    {
        case GPIO_COOLER_ID:
            cfg->pin = kPinList[COOLER_ID];
            cfg->direction = 1;
            cfg->logic = 1;
            cfg->mode = 1;
            success = true;
        break;
        case GPIO_ALARM_ID:
            cfg->pin = kPinList[ALARM_ID];
            cfg->direction = 0;
            cfg->logic = 1;
            cfg->mode = 1;
            success = true;
    break;
        default:
            success = false;
        break;
    }
    return success;
}