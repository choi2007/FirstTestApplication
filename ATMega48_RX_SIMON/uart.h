#ifndef _UART_H_
#define _UART_H_

#include "datatype.h"

/**********************************************************
	Constants
**********************************************************/

// Serial Interface

#define UART_TX_BUF_SIZE	1
#define UART_RX_BUF_SIZE	20

/* set baud rate here */
#define UART_BAUD_RATE	9600
#define ESC				0x1B
#define UBRR_9600		47

/* automatically calcuate baud register value */
#define UART_BAUD_SELECT (F_CPU/(UART_BAUD_RATE*16l)-1)


/**********************************************************
	Structures
**********************************************************/

typedef struct
{
	volatile uint16 txCnt, rxCnt;
	volatile uint8 *txHead, *txTail;
	volatile uint8 *rxHead, *rxTail;
	uint8 txBuf[UART_TX_BUF_SIZE], rxBuf[UART_RX_BUF_SIZE];
} UART_DATA;


/**********************************************************
	Variables
**********************************************************/

extern UART_DATA uart;

/**********************************************************
	Functions
**********************************************************/

void uart_init(void);
uint8 uart_getchar(void);
/*volatile uint16 uart_getRxCnt(void);*/
void uart_putchar(uint8 c);

#endif /* _UART_H_ */
