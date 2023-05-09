	/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "gpio_led_output.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 8000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

void togglepins(GPIO_Types *Port, uint32_t pin){
	Port->PTOR = pin;
}

void initpins(){
    CLOCK_EnableClock(kCLOCK_PortC);

    CLOCK_EnableClock(kCLOCK_PortD);

    PORT_SetPinMux(PORTD, 1U, kPORT_MuxAsGpio);

    PORT_SetPinMux(PORTC, 9U, kPORT_MuxAsGpio);

    PORT_SetPinMux(PORTC, 8U, kPORT_MuxAsGpio);

}

void initGPIO(GPIO_Types *Port, uint32_t pin, gpio_pin_config_t *config){
    assert(NULL != config);

    if (config->pinDirection == kGPIO_DigitalInput)
    {
    	Port->PDDR &= (~(1u << pin));
    }
    else
    {
        Port->PDDR |= ((1u << pin));
    }


}




/*!
 * @brief Main function
 */
int main(void)
{
    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };

    /* Board pin, clock, debug console init */
    initpins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n The LED is blinking.\r\n");

    /* Init output LED GPIO. */
    initGPIO(BOARD_LED_GPIO_D, BOARD_LED_RED_PIN, &led_config);
    initGPIO(BOARD_LED_GPIO_C, BOARD_LED_GREEN_PIN, &led_config);
    initGPIO(BOARD_LED_GPIO_C, BOARD_LED_BLUE_PIN, &led_config);
    GPIO_PortToggle(BOARD_LED_GPIO_C, 1u << BOARD_LED_BLUE_PIN);
    togglepins(BOARD_LED_GPIO_C, 1u << BOARD_LED_BLUE_PIN);
    while (1) {
        delay();
        togglepins(BOARD_LED_GPIO_C, 1u << BOARD_LED_BLUE_PIN);
        togglepins(BOARD_LED_GPIO_C, 1u << BOARD_LED_GREEN_PIN);
        delay();
        togglepins(BOARD_LED_GPIO_C, 1u << BOARD_LED_GREEN_PIN);
        togglepins(BOARD_LED_GPIO_D, 1u << BOARD_LED_RED_PIN);
        delay();
        togglepins(BOARD_LED_GPIO_D, 1u << BOARD_LED_RED_PIN);
        togglepins(BOARD_LED_GPIO_C, 1u << BOARD_LED_BLUE_PIN);

    }
}
