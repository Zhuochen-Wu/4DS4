/*
 * gpio_led_output.h
 *
 *  Created on: Jan. 19, 2022
 *      Author: halo3
 */

#ifndef GPIO_LED_OUTPUT_H_
#define GPIO_LED_OUTPUT_H_

typedef struct {
  __IO uint32_t PDOR;                              /**< Port Data Output Register, offset: 0x0 */
  __O  uint32_t PSOR;                              /**< Port Set Output Register, offset: 0x4 */
  __O  uint32_t PCOR;                              /**< Port Clear Output Register, offset: 0x8 */
  __O  uint32_t PTOR;                              /**< Port Toggle Output Register, offset: 0xC */
  __I  uint32_t PDIR;                              /**< Port Data Input Register, offset: 0x10 */
  __IO uint32_t PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
} GPIO_Types;


#define BOARD_LED_GPIO_D    	((GPIO_Types *)GPIOD_BASE)
#define BOARD_LED_GPIO_C    	((GPIO_Types *)GPIOC_BASE)
#define BOARD_LED_RED_PIN 	1
#define BOARD_LED_GREEN_PIN 9
#define BOARD_LED_BLUE_PIN	8

#include "core_cm4.h"                  /* Core Peripheral Access Layer */
//#include "system_MK66F18.h"            /* Device specific configuration file */



void togglepins(GPIO_Types *Port, uint32_t pin);

void initpins();

void initGPIO(GPIO_Types *Port, uint32_t pin, gpio_pin_config_t *config);




#endif /* GPIO_LED_OUTPUT_H_ */
