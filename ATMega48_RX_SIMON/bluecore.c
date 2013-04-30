#include "datatype.h"
#include "bluecore.h"
#include "uart.h"
#include "rc5.h"

BC_DATA bc;

extern RC5_DATA rc5;
void bc_init(void)
{
	bc.enabled = TRUE;
	bc.btnState = BC_BTN_RELEASED;
}

void bc_receive(void)
{
	//while (uart_getRxCnt() > 0)
	if(rc5.tx.cnt > 0)
	{
		bc.rxCmd = uart_getchar();
		bc_decode();
	}
}

void bc_decode(void)
{
	RC5_FRAME frame;
	uint8 btn;
	
	if (bc.rxCmd == BC_CMD_OK || bc.rxCmd == BC_CMD_ERROR) return;
	
	btn = bc.rxCmd & BC_MASK_BUTTON;
	if (btn > 0x04) return;
	
	bc.btnState = (bc.rxCmd & BC_MASK_RELEASED)>>6;
	if (bc.btnState == BC_BTN_PRESSED)
	{
		rc5.tx.toggle = 1 - rc5.tx.toggle;
	}
	else
	{
		return;
	}
	
	switch (btn)
	{
		case BC_CMD_INPUT:
			frame.stream[0] = 0x8A;
			frame.stream[1] = 0x55;
			frame.stream[2] = 0x50;
			frame.stream[3] = 0x55;
			frame.stream[4] = 0xA5;
			frame.stream[5] = 0x89;
			break;
			
		case BC_CMD_POWER:
			frame.stream[0] = 0x8A;
			frame.stream[1] = 0x55;
			frame.stream[2] = 0xA5;
			frame.stream[3] = 0x05;
			frame.stream[4] = 0x00;
			frame.stream[5] = 0x00;
			break;
		
		case BC_CMD_VOL_UP:
			frame.stream[0] = 0x8A;
			frame.stream[1] = 0x55;
			frame.stream[2] = 0x59;
			frame.stream[3] = 0x05;
			frame.stream[4] = 0x00;
			frame.stream[5] = 0x00;
			break;
		
		case BC_CMD_VOL_DOWN:
			frame.stream[0] = 0x8A;
			frame.stream[1] = 0x55;
			frame.stream[2] = 0x59;
			frame.stream[3] = 0x09;
			frame.stream[4] = 0x00;
			frame.stream[5] = 0x00;
			break;
	}

	if (rc5.tx.toggle == 1)
		frame.stream[0] |= 0x20;
	else
		frame.stream[0] |= 0x10;
	
	rc5_putFrame(&frame);
}
