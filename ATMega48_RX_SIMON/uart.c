#include <avr/interrupt.h>
#include "datatype.h"
#include "uart.h"

/* UART globals */

UART_DATA uart;

uint16 uart_get_rxd_buf_cnt(void)
{ 	
	return uart.rxCnt;
}

void uart_init(void)
{
	uart.txCnt = 0;
	uart.rxCnt = 0;
	uart.txTail = uart.txBuf;
	uart.txHead = uart.txBuf;
	uart.rxTail = uart.rxBuf;
	uart.rxHead = uart.rxBuf;

	cli();
	
    UCSR0C=0x06;	/* asyn,no parity,1-stop bit,8bit	*/	
    UCSR0B=((1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0));

    /* set baud rate */
    UBRR0L=(uint8)(UBRR_9600);
	UBRR0H=(uint8)0x00;
    
	sei();
}

// Interrupt handler for reception finished

ISR(USART_RX_vect) 
{
	uint8 dummy;

    cli();

    dummy = UCSR0A;
    if ((dummy & 0x14) == 0)	// No Error
	{
		// Read byte
		*uart.rxHead = UDR0;
		
		// Increment pointer
		uart.rxHead++;
		if (uart.rxHead >= (uart.rxBuf+UART_RX_BUF_SIZE))
			uart.rxHead = uart.rxBuf;
		
		// Increment counter
		uart.rxCnt++;
	}
	else
	{
		dummy = UDR0;
	}

	sei();    
}

uint8 uart_getchar(void)
{
	uint8 c;
	
	cli();
	
	if (uart.rxCnt > 0)
	{
		// Get character from buffer
		c = *uart.rxTail;
		
		// Increment pointer
		uart.rxTail++;
		if (uart.rxTail >= (uart.rxBuf+UART_RX_BUF_SIZE))
			uart.rxTail = uart.rxBuf;
		
		// Decrement counter
		uart.rxCnt--;
		
		sei();
		return c;
	}

	sei();
	return 0xFF;
}
/*
volatile uint16 uart_getRxCnt(void)
{
	return uart.rxCnt;
}
*/
void uart_putchar(uint8 c)
{
	while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = c; 
}
