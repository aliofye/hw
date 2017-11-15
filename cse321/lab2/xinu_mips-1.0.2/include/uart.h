/**
 * @file uart.h
 *
 * $Id: uart.h 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#ifndef __XINU_SERIAL_H__
#define __XINU_SERIAL_H__

#include <semaphore.h>
#include <device.h>

/**
 * Control and status registers for the 16550 UART.  This structure is mapped
 * directly to the base address for the CSR.
 */
struct uart_csreg
{
	volatile uchar buffer;    /**< receive buffer (read only)            */
	                          /**<  OR transmit hold (write only)        */
	volatile uchar ier;       /**< interrupt enable                      */
	volatile uchar iir;       /**< interrupt ident (read only)           */
	                          /**<  OR FIFO control (write only)         */
	volatile uchar lcr;       /**< line control                          */
	volatile uchar mcr;       /**< modem control                         */
	volatile uchar lsr;       /**< line status                           */
	volatile uchar msr;       /**< modem status                          */
	volatile uchar scr;       /**< scratch                               */
};

/* Alternative names for control and status registers                    */
#define rbr buffer            /**< receive buffer (read only)            */
#define thr buffer            /**< transmit hold (write only)            */
#define fcr iir               /**< FIFO control (write only)             */
#define dll buffer            /**< divisor latch low byte                */
#define dlm ier               /**< divisor latch high byte               */

/* UART Bit flags for control and status registers                       */
/* Interrupt enable bits                                                 */
#define UART_IER_ERBFI  0x01  /**< Received data interrupt mask          */
#define UART_IER_ETBEI  0x02  /**< Transmitter buffer empty interrupt    */
#define UART_IER_ELSI   0x04  /**< Receiver line status interrupt mask   */
#define UART_IER_EMSI   0x08  /**< Modem status interrupt mask           */

/* Interrupt identification masks */
#define UART_IIR_IRQ    0x01  /**< Interrupt pending bit                 */
#define UART_IIR_IDMASK 0x0E  /**< 3-bit field for interrupt ID          */
#define UART_IIR_MSC    0x00  /**< Modem status change                   */
#define UART_IIR_THRE   0x02  /**< Transmitter holding register empty    */
#define UART_IIR_RTO    0x04  /**< Receiver timed out                    */
#define UART_IIR_RLSI   0x06  /**< Receiver line status interrupt        */
#define UART_IIR_RDA    0x0C  /**< Receiver data available               */

/* FIFO control bits */
#define UART_FCR_EFIFO  0x01  /**< Enable in and out hardware FIFOs      */
#define UART_FCR_RRESET 0x02  /**< Reset receiver FIFO                   */
#define UART_FCR_TRESET 0x04  /**< Reset transmit FIFO                   */
#define UART_FCR_TRIG0  0x00  /**< RCVR FIFO trigger level of one.       */
#define UART_FCR_TRIG1  0x40  /**< RCVR FIFO trigger level one quarter   */
#define UART_FCR_TRIG2  0x80  /**< RCVR FIFO trigger level about half    */
#define UART_FCR_TRIG3  0xC0  /**< RCVR FIFO trigger level almost full   */

/* Line control bits */
#define UART_LCR_DLAB   0x80  /**< Divisor latch access bit              */
#define UART_LCR_8N1    0x03  /**< 8 bits, no parity, 1 stop             */

/* Modem control bits */
#define UART_MCR_OUT2   0x08  /**< User-defined OUT2.                    */
#define UART_MCR_LOOP   0x10  /**< Enable loopback test mode             */

/* Line status bits */
#define UART_LSR_DR     0x01  /**< Data ready                            */
#define UART_LSR_THRE   0x20  /**< Transmit-hold-register empty          */
#define UART_LSR_TEMT   0x40  /**< Transmitter empty                     */

#define UART_FIFO_LEN   64    /**< At least 64 bytes on WRT54.           */

/* UART Buffer lengths */
#define UART_IBLEN      1024
#define UART_OBLEN      1024

/* UART 16550 control block */
struct uart
{
	/* Pointers to associated structures */
	struct uart_csreg *csr;             /**< Control & status registers  */
	device            *dev;             /**< Dev structure               */

	/* Statistical Counts */
	long               cout;            /**< Characters output           */
	long               cin;             /**< Characters input            */
	long               lserr;           /**< Receiver error count        */
	long               ovrrn;           /**< Characters overrun          */
	long               iirq;            /**< Input IRQ count             */
	long               oirq;            /**< Output IRQ count            */

	/* UART input fields */
	uchar              iflags;          /**< Input flags                 */
	semaphore          isema;           /**< I/0 semfor uart input       */
	ushort             istart;          /**< Index of first byte         */
	ushort             icount;          /**< Bytes in buffer             */
	uchar              in[UART_IBLEN];  /**< Input buffer                */

	/* UART output fields */
	uchar              oflags;          /**< Output flags                */
	semaphore          osema;           /**< I/0 semfor uart output      */
	ushort             ostart;          /**< Index of first byte         */
	ushort             ocount;          /**< Bytes in buffer             */
	uchar              out[UART_OBLEN]; /**< Output buffer               */
	bool               oidle;           /**< UART transmitter idle       */
};

extern struct uart uarttab[];

/* UART input flags */
#define UART_IFLAG_NOBLOCK      0x0001  /**< do non-blocking input       */
#define UART_IFLAG_ECHO         0x0002  /**< echo input                  */

/* UART output flags */
#define UART_OFLAG_NOBLOCK      0x0001  /**< do non-blocking output      */

/* uartControl() functions  */
#define UART_IOC_SETIFLAG       0x0010  /**< set input flags             */
#define UART_IOC_CLRIFLAG       0x0011  /**< clear input flags           */
#define UART_IOC_GETIFLAG       0x0012  /**< get input flags             */
#define UART_IOC_SETOFLAG       0x0013  /**< set output flags            */
#define UART_IOC_CLROFLAG       0x0014  /**< clear output flags          */
#define UART_IOC_GETOFLAG       0x0015  /**< get output flags            */
#define UART_IOC_OUTPUT_IDLE    0x0016  /**< determine if transmit idle  */

/* Driver functions */
devcall uartInit(device *);
devcall uartRead(device *, unsigned char *, int);
devcall uartWrite(device *, unsigned char *, int);
devcall uartGetChar(device *);
devcall uartPutChar(device *, unsigned char);
devcall uartControl(device *, int, unsigned char, unsigned char);
interrupt uartIntr(void);

#endif /* _UART_H_ */
