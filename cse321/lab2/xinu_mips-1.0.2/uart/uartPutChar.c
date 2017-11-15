/**
 * @file uartPutChar.c
 * @provides uartPutChar
 *
 * $Id: uartPutChar.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <uart.h>
#include <device.h>

/**
 * Write a single character to the UART
 * @param  pdev  pointer to UART device
 * @param  ch    character to write 
 */
devcall uartPutChar(device *pdev, uchar ch)
{  
  return uartWrite(pdev, &ch, 1);
}

