#include <avr/interrupt.h> 

#include "datatype.h"
#include "rc5.h"
#include "rc5_mode.h"
#include "readuart.h"
#include "key.h"
#include "detectpin.h"
#include "uart.h"
#include "bluecore.h"
/***********************************
	Structure
***********************************/
typedef struct
{
	uint8 RC5timer;
} Main_type;
Main_type maintype;
unsigned int delaytimer=0;
/**********************************************************
	MAIN INIT
**********************************************************/
void main_init(void)
{
	readuart_init(C_Set);	
//	uart_init(); 
//	key_init();
//	rc5_init();

	key_init();
	rc5_init();
	uart_init();
	bc_init();
	//detectpin_init();
	rc5mode_switch_init();

/**********TIMER 0 (35ms,for uart, timeing chk)*/

	TIMSK0 		|=_BV(TOIE0);
	TCCR0B 		|= _BV(CS00)|_BV(CS02);//|_BV(WGM02);
	maintype.RC5timer	=C_RESET_mainRC5timer;			//it increase as Timer0
}
void mute_3s_init(void)
{
//-------set mute for 3s
	DDRC	|=C_MUTECTRL_Pin;
	PORTC	|=C_MUTECTRL_Pin;
	cli();
	main_init();
	sei();
	//----start delay 35ms*85~=3s	
	delaytimer=0;
	while(delaytimer < 85)
	{
		if(delaytimer ==43)
			detectpin_init();
			//detectpin_ChangeSetMuteCtrl(C_LOW);
	}
//--------unmut after 3s
	DDRC	&=~C_MUTECTRL_Pin;
	PORTC	&=~C_MUTECTRL_Pin;
}
int main(void)
{



	mute_3s_init();

	while (1)
	{
		bc_receive();
		
		rc5_transmit();
	}
	
	return 0;
}
