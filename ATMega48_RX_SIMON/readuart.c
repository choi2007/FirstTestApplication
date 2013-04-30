#include <avr/io.h> 
#include <avr/interrupt.h> 


//unsigned char CurrentPort,Cmd,loopCount; 

/*

*/

#include "rc5.h"
//#include "key.h"
#include "uart.h"
#include "datatype.h"
#include "readuart.h"

extern maintype;
//--------------------
/*
void readuart_DecodeData(uint8 uart_data)
{
//	state
//#define C_NODATA		0x00
//#define C_JUSTGETDATA	0x01
//#define C_SENDDATA		0x02
//#define C_ENDDATA		0x03
//
//
//#define C_NOCmd			0x00
//#define C_ERRORCmd		0xf0

//#define C_PLAYCmd		0x01
//#define C_PAUSECmd		0x02
//#define C_STOPCmd		0x03
//#define C_FFCmd			0x04
//#define C_REWCmd		0x05
//#define C_NEXTTRACKCmd	0x06
//#define C_PREVTRACKCmd	0x07

//#define C_INPSELCmd		0x11
//#define C_POWERCmd		0x12
//#define C_VOLIncCmd		0x13
//#define C_VOLDecCmd		0x14
//
	static uint8 uart_dataBit6_7;
	static uint8 uart_dataBit0_5;
	uart_dataBit6_7	=uart_data & C_BIT6_7;
	uart_dataBit0_5	=uart_data & C_BIT0_5;
		
	if(
		((uart_dataBit6_7==C_PRESS_IND)||(uart_dataBit6_7==C_RELEASE_IND))	&
		((uart_dataBit0_5<=C_BUT_MAX)	&(uart_dataBit0_5>C_BUT_MIN))
	  )
	{		
		//correct button
			//reset mainRC5timer
			maintype.RC5timer			=C_RESET_mainRC5timer;
			readuart.action_cmd			=uart_dataBit0_5;
			readuart.prev_action_cmd	=uart_dataBit0_5;

			if(uart_dataBit6_7	==C_PRESS_IND)
			{
				readuart.state		=C_PRESS_STATE;
				//invert "tx_toggle" 
				//readuart.tx_toggle	^=0x01;
				if(readuart.tx_toggle	==C_TOGGLELow)
					readuart.tx_toggle	=C_TOGGLEHigh;
				else
					readuart.tx_toggle	=C_TOGGLELow;
				//cli();
				//rc5_rest_tx_cnt();
				//sei();
			}
			else
			{
				readuart.state		=C_UNPRESS_STATE;	
				cli();
				rc5_rest_tx_cnt();
				sei();			
			}
			return;

	}
	else
	if(uart_data	==C_OK_startcmd)
	{				
		//Ok responce		
	}
	else
	if(uart_data	==C_ERROR_startcmd)
	{				
		//error responce		
	}
//	else
//		detectpin_ChkBT_UartCmd(uart_data);
}
*/
//---------------------------------
void readuart_init(uint8 ClearPrevActionCmd)
{
//	static uint8 i; 
	//readuart.state				=C_NODATA;
	readuart.state				=C_INIT_STATE;
//	readuart.timer				=C_RESETTIMER;	//C_FULLTIME
	readuart.action_cmd 		=C_NOCmd;
//	readuart.counter			=C_COUNTCmd;
	readuart.enableflag			=C_DISABLE;
	
//	for(i=0x00;i<0x04;i++)
//		readuart.data[i]=0x00;

	if(ClearPrevActionCmd)
	{
		readuart.prev_action_cmd	=C_NOCmd;
		readuart.tx_toggle			=C_TOGGLELow;
	}
}
//------------------------
/*
void readuart_sendRC5()
{
	static RC5_FRAME_TX frame;

//	switch(ReplyCmd)
		if(readuart.prev_action_cmd==C_INPSELCmd)
		{
			frame.data	=0x00;
			frame.packet[0]	=0x8a;	//suppose command code of 7th bit is "0"
			if(readuart.tx_toggle	==C_TOGGLELow)
				frame.packet[0] |=0x20;
			else
				frame.packet[0] |=0x10;

				frame.packet[1] =0x55;
				frame.packet[2] =0x50;
				frame.packet[3] =0x55;
				frame.packet[4] =0xa5;		
				frame.packet[5] =0x09;		//suppose bit0/1 is not used. set 0

			
			//readuart_setframe(readuart.tx_toggle,16,00,13);

			//DDRB|=0x01;
			rc5_putFrame(&frame);
			return;
		}
		if(readuart.prev_action_cmd==C_POWERCmd)
		//case	C_POWERCmd:
		{
			frame.data	=RC5_NO_EXT;
			frame.packet[0]	=0x8a;	//suppose command code of 7th bit is "0"
			if(readuart.tx_toggle	==C_TOGGLELow)
				frame.packet[0] |=0x20;
			else
				frame.packet[0] |=0x10;

				frame.packet[1] =0x55;
				frame.packet[2] =0xa5;
				frame.packet[3] =0x05;		//suppose bit0/1/2/3 is not used. set 0
				//frame.packet[4] |=0x59;		
			
			//readuart_setframe(readuart.tx_toggle,16,12,RC5_NO_EXT);
			rc5_putFrame(&frame);
			return;
		}
		if(readuart.prev_action_cmd==C_VOLIncCmd)
		//case	C_VOLIncCmd:
		{
			frame.data	=RC5_NO_EXT;
			frame.packet[0]	=0x8a;	//suppose command code of 7th bit is "0"
			if(readuart.tx_toggle	==C_TOGGLELow)
				frame.packet[0] |=0x20;
			else
				frame.packet[0] |=0x10;

				frame.packet[1] =0x55;
				frame.packet[2] =0x59;
				frame.packet[3] =0x05;		//suppose bit0/1/2/3 is not used. set 0
			
			//readuart_setframe(readuart.tx_toggle,16,16,RC5_NO_EXT);
			rc5_putFrame(&frame);
			return;
		}
		if(readuart.prev_action_cmd==C_VOLDecCmd)
		//case	C_VOLDecCmd:
		{
			frame.data	=RC5_NO_EXT;
			frame.packet[0]	=0x8a;	//suppose command code of 7th bit is "0"
			if(readuart.tx_toggle	==C_TOGGLELow)
				frame.packet[0] |=0x20;
			else
				frame.packet[0] |=0x10;

				frame.packet[1] =0x55;
				frame.packet[2] =0x59;
				frame.packet[3] =0x09;		//suppose bit0/1/2/3 is not used. set 0

			//readuart_setframe(readuart.tx_toggle,16,17,RC5_NO_EXT);
			rc5_putFrame(&frame);
			return;
		}
//		default:
//			break;
//	}
	
}
*/
/*
//void readuart_sendRC5(uint8 ReplyCmd,uint8 Tx_toggle)
void readuart_sendRC5()
{
	static RC5_FRAME frame;
	



//	switch(ReplyCmd)
	switch(readuart.prev_action_cmd)
	{
		case	C_INPSELCmd:
		{
			
			frame.toggle = readuart.tx_toggle;
			frame.system = 16;
			frame.command = 00;
			frame.data = 13;
			
			//readuart_setframe(readuart.tx_toggle,16,00,13);

			//DDRB|=0x01;
			rc5_putFrame(&frame);
			break;
		}
		case	C_POWERCmd:
		{
			
			frame.toggle = readuart.tx_toggle;
			frame.system = 16;
			frame.command = 12;
			frame.data = RC5_NO_EXT;
						
			//readuart_setframe(readuart.tx_toggle,16,12,RC5_NO_EXT);
			rc5_putFrame(&frame);
			break;
		}
		case	C_VOLIncCmd:
		{
			
			frame.toggle = readuart.tx_toggle;
			frame.system = 16;
			frame.command = 16;
			frame.data = RC5_NO_EXT;
			
			//readuart_setframe(readuart.tx_toggle,16,16,RC5_NO_EXT);
			rc5_putFrame(&frame);
			break;
		}
		case	C_VOLDecCmd:
		{

			frame.toggle = readuart.tx_toggle;
			frame.system = 16;
			frame.command = 17;
			frame.data = RC5_NO_EXT;

			//readuart_setframe(readuart.tx_toggle,16,17,RC5_NO_EXT);
			rc5_putFrame(&frame);
			break;
		}
		default:
			break;
	}
	
}
*/
