#ifndef _BLUECORE_H_
#define _BLUECORE_H_

#include "datatype.h"

/**********************************************************
	Constants
**********************************************************/

#define BC_MASK_RELEASED	0x40
#define BC_MASK_BUTTON		0x07

#define BC_BTN_PRESSED	0x00
#define BC_BTN_RELEASED	0x01

// Commands List

// BC ==> MCU
#define BC_CMD_INPUT	0x01
#define BC_CMD_POWER	0x02
#define BC_CMD_VOL_UP	0x03
#define BC_CMD_VOL_DOWN	0x04
#define BC_CMD_OK		0xFD
#define BC_CMD_ERROR	0xFE

// MCU ==> BC

/**********************************************************
	Structures
**********************************************************/

typedef struct
{
	bool enabled;
	//uint8 buffer[10];
	uint8 rxCmd;
	uint8 btnState;
} BC_DATA;

/**********************************************************
	Variables
**********************************************************/

extern BC_DATA bc;

/**********************************************************
	Functions
**********************************************************/

void bc_init(void);

void bc_receive(void);
void bc_decode(void);

#endif /* _BLUECORE_H_ */
