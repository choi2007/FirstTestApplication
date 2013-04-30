#include <avr/io.h> 
//#include <avr/interrupt.h> 

//#include "rc5.h"
//#include "key.h"

#include "datatype.h"
#include "uart.h"
#include "rc5_mode.h"
//--------------------
//------RC5_OUT pin Setting

//-----IR_ENABLE Setting
void Set_Enable(uint8 Pin)
{
/*
	//output pull low
	DDRB |= Pin;
	PORTB &= ~Pin;	
*/
	DDRB |= Pin;
	PORTB |= Pin;	

}
void Set_Disable(uint8 Pin)
{
/*
	//input pull low 
	DDRB &= ~Pin;
	PORTB &= ~Pin;	
*/
	DDRB |= Pin;
	PORTB &= ~Pin;	
}

void rc5mode_switch_init(void)
{

	mode.modeswitch_state	=C_READ_RC5;
		Set_Enable(IR_ENABLE);
		Set_Disable(RC5_OUT);
		PCICR |= _BV(PCIE0) ;

	mode.modeswitch_timer	=C_RESET;
}
void rc5mode_switch_handle(void)
{
	if(mode.modeswitch_state	==C_READ_RC5)
	{
		if((mode.modeswitch_timer>=C_CHANGE_MODE)&&(uart_get_rxd_buf_cnt()>0))
			{
				mode.modeswitch_state	=C_SEND_RC5;
//				Set_Disable(IR_ENABLE);
				Set_Enable(IR_ENABLE);
				Set_Disable(RC5_OUT);
				//disable hardwre interrupt,RC5_IN
				PCICR &= ~_BV(PCIE0) ;

				mode.modeswitch_timer	=C_RESET;
				return;
			}
	}
	else
	{
		if(mode.modeswitch_timer>=C_CHANGE_MODE)
			{
				mode.modeswitch_state	=C_READ_RC5;
				Set_Enable(IR_ENABLE);
				Set_Disable(RC5_OUT);
				//enable hardware interrupt,RC5_IN
				PCICR |= _BV(PCIE0) ;

				mode.modeswitch_timer	=C_RESET;
				return;
			}

	}	
}
