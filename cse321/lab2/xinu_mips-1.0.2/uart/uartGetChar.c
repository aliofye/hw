/**
 * @file uartGetChar.c
 * @provides uartGetChar
 *
 * $Id: uartGetChar.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <uart.h>
#include <device.h>

/**
 * Read a single character from UART.
 * @param pdev pointer to UART device
 */
devcall uartGetChar(device *pdev)
{  
  unsigned char ch = 0;  
  uartRead(pdev, &ch, 1);
  return ch;
}
