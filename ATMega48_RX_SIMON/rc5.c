#include <avr/interrupt.h>
#include "datatype.h"
#include "rc5.h"
#include "bluecore.h"

RC5_DATA rc5;
//volatile uint16 timer10us = 0;

void Set_Enable(uint8 Pin)
{

	//output pull low
	DDRB |= Pin;
	PORTB |= Pin;	

}
void Set_Disable(uint8 Pin)
{

	//input pull low 
	DDRB |= Pin;
	PORTB &= ~Pin;	
}

void rc5_init(void)
{
	//rc5.rx.enabled = TRUE;
	/*rc5.rx.halfBits = 0;
	
	rc5.rx.cnt = 0;
	rc5.rx.tail = rc5.rx.buf;
	rc5.rx.head = rc5.rx.buf;*/

	rc5.tx.enabled = TRUE;	
	rc5.tx.bits = 0;
	rc5.tx.cnt = 0;
	rc5.tx.tail = rc5.tx.buf;
	rc5.tx.head = rc5.tx.buf;
	rc5.tx.toggle = 0;
	
	cli();
	
//----------(pin interrupt, for detect each rc5_receive signal)------------//

	//PCINT1 level edge

	//enable PCINT1(C_PB1) as the RC_5 signal receiving input port
	//input pull low 

	DDRB &= ~C_PB1;
	PORTB &= ~C_PB1;

	PCICR |= _BV(PCIE0) ; 
	PCMSK0 |= _BV(PCINT1); //Any logic change will cause interrupt
//----------(timer1 interrupt, for calulate the time of each rc5_receive signal)------------//
	TCNT1H=0x00;
	TCNT1L=0x00;

	OCR1AH =0x00;
	OCR1AL =0x30;	//0x2d// for INT0 "0x25"
	TIMSK1 =_BV(OCIE1A);
	TCCR1B |= _BV(CS10);

/**********TIMER 2 (for rc5_transmit)*/
	TCNT2=0x00;

	//OCR2 =0x00;
	OCR2A =0x32;	//0x18//0x2d// for INT0 "0x25"
	TIMSK2 =_BV(OCIE2A);
	TCCR2A |= _BV(WGM21)|_BV(WGM20);
	//TCCR2B |= _BV(CS21)|_BV(CS22)|_BV(WGM22);
	TCCR2B |= _BV(CS20)|_BV(CS22);
	TCCR2B |= _BV(WGM22);

//*/
	sei();
}

////////////////////////////////////////////////////////////////////////////////
// RC5 Transmission
////////////////////////////////////////////////////////////////////////////////

ISR(TIMER2_COMPA_vect) 
{
	cli();

	//bCPU_TM0EN = 0;
	DDRB	|=0x01;
	//PORTB &= ~0x01;
	if (rc5.tx.bits > 0)
	{
		if ((rc5.tx.stream[rc5.tx.pos]>>rc5.tx.shift) & 0x01)
			PORTB |=0x01;
			//DDRB |=0x01;
		else
			PORTB &= ~0x01;
			//DDRB &= ~0x01;			

		rc5.tx.shift++;
		if (rc5.tx.shift == 8)
		{
			rc5.tx.pos++;
			rc5.tx.shift = 0;
		}
		rc5.tx.halfBits++;
		if (rc5.tx.bExt)
		{
			if (rc5.tx.halfBits == 45) rc5.tx.bits = 0;
		}
		else
		{
			if (rc5.tx.halfBits == 29) rc5.tx.bits = 0;
		}
	}
	else
	{
		PORTB &= ~0x01;
		//DDRB &= ~0x01;
	}
	rc5.tx.frameTimer++;
	
	//bCPU_TM0EN = 1;
	sei();
}

void rc5_sendInput(void)
{
	RC5_FRAME frame;
	
	if (rc5.tx.bits != 0 || rc5.tx.frameTimer <= 128) return;
	
	frame.stream[0] = 0x8A;

	if (rc5.tx.toggle == 1)
		frame.stream[0] |= 0x20;
	else
		frame.stream[0] |= 0x10;
		
	frame.stream[1] = 0x55;
	frame.stream[2] = 0x50;
	frame.stream[3] = 0x55;
	frame.stream[4] = 0xA5;
	frame.stream[5] = 0x89;	// With extension
	
	rc5_putFrame(&frame);
}

void rc5_putFrame(RC5_FRAME *frame)
{
	RC5_FRAME *p;
	
	cli();
	
	p = rc5.tx.head;
	
	p->stream[0] = frame->stream[0];
	p->stream[1] = frame->stream[1];
	p->stream[2] = frame->stream[2];
	p->stream[3] = frame->stream[3];
	p->stream[4] = frame->stream[4];
	p->stream[5] = frame->stream[5];	// Bit 7 is bExt
	
	rc5.tx.head++;
	if (rc5.tx.head >= (rc5.tx.buf+RC5_TX_BUF_SIZE))
		rc5.tx.head = rc5.tx.buf;
	
	rc5.tx.cnt++;
	
	sei();
}

/*
volatile uint16 rc5_getTxCnt(void)
{
	return (rc5.tx.cnt);
}
*/
void rc5_transmit(void)
{
	RC5_FRAME *p;
	
	if (rc5.tx.bits == 0)
	{
		// Not sending
		//if (rc5_getTxCnt() > 0)
		if(rc5.tx.cnt > 0)
		{
			// There exists frame to send
			if (rc5.tx.frameTimer > 128)
			{
				// FrameTimer expired ==> Start new transmission
				rc5.tx.bits = 1;
				rc5.tx.halfBits = 0;
				rc5.tx.timer = 0;
				rc5.tx.frameTimer = 0;
				rc5.tx.pos = 0;
				rc5.tx.shift = 0;
				
				p = rc5.tx.tail;
				
				rc5.tx.stream[0] = p->stream[0];
				rc5.tx.stream[1] = p->stream[1];
				rc5.tx.stream[2] = p->stream[2];
				rc5.tx.stream[3] = p->stream[3];
				rc5.tx.stream[4] = p->stream[4];
				rc5.tx.stream[5] = p->stream[5];
				rc5.tx.bExt = (rc5.tx.stream[5] & 0x80) ? TRUE : FALSE;

				if (bc.btnState == BC_BTN_RELEASED)
				{
					rc5.tx.tail++;
					if (rc5.tx.tail >= (rc5.tx.buf+RC5_TX_BUF_SIZE))
						rc5.tx.tail = rc5.tx.buf;
						
					rc5.tx.cnt--;
					return;
				}

				Set_Enable(IR_ENABLE);
				Set_Disable(RC5_OUT);
				//disable hardwre interrupt,RC5_IN
				PCICR &= ~_BV(PCIE0) ;
			}
		}
	}
}
