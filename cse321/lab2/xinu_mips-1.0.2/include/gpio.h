/**
 * @file gpio.h
 *
 * $Id: gpio.h 224 2007-07-11 21:42:09Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#ifndef __XINU_GPIO_H__
#define __XINU_GPIO_H__

#define GPIO_BASE 0xb8000060

/* Control and status registers for the GPIO. */
struct gpio_csreg
{
	volatile unsigned long input;       /**< input                      */
	volatile unsigned long output;      /**< output                     */
	volatile unsigned long enable;      /**< direction                  */
	volatile unsigned long control;     /**< usage unkmown              */
};


/* GPIO bits for pin direction */
#define GPIO_DIR_IN         0x00        /**< set pin for input          */
#define GPIO_DIR_OUT        0x01        /**< set pin for output         */

/* GPIO bit flags for pins */
#define GPIO0               0x01
#define GPIO1               0x02
#define GPIO2               0x04
#define GPIO3               0x08
#define GPIO4               0x10
#define GPIO5               0x20
#define GPIO6               0x40
#define GPIO7               0x80

#define GPIO_PIN_COUNT      8

/* LEDs */
#define GPIO_LED_WLAN       GPIO0       /**< WLAN LED                   */
#define GPIO_LED_POWER      GPIO1       /**< Power LED (also hardware controlled) */
#define GPIO_LED_CISCOWHT   GPIO2       /**< White Cisco LED            */
#define GPIO_LED_CISCOONG   GPIO3       /**< Orange Cisco LED           */
#define GPIO_LED_DMZ        GPIO7       /**< DMZ LED                    */

/* LED control functions */
#define GPIO_CTRL_LED_ON(n) ((struct gpio_csreg *)GPIO_BASE)->enable |= n; \
							((struct gpio_csreg *)GPIO_BASE)->output &= ~n

#define GPIO_CTRL_LED_OFF(n) ((struct gpio_csreg *)GPIO_BASE)->enable &= ~n

/* Buttons */ 
#define GPIO_BUT_CISCO      GPIO4       /**< Front Cisco button         */
#define GPIO_BUT_RESET      GPIO6       /**< Back reset button          */

#endif
