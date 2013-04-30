/*	key.h	*/
#include "datatype.h"
/**********************************************************
	Structure
**********************************************************/
typedef struct
{
	uint8 modeswitch_state;
	uint8 modeswitch_timer;


} Mode_Switch;

/**********************************************************
	Constant
**********************************************************/
//modeswitch_timer
#define C_RESET			0
#define C_CHANGE_MODE	6

//modeswitch_state
#define C_READ_RC5		0
#define C_SEND_RC5		1

//pin
#define	IR_ENABLE		0x04
#define	RC5_OUT			0x01
 
/**********************************************************
	Variables
**********************************************************/
Mode_Switch mode;
/**********************************************************
	Functions
**********************************************************/
void rc5mode_switch_init(void);
void rc5mode_switch_handle(void);
//void Set_Disable(uint8 Pin);
//void Set_Enable(uint8 Pin);


