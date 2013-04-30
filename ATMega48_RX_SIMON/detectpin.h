#include <avr/io.h> 

#include "datatype.h"

/***********************************
	Structure
***********************************/
typedef struct
{
	uint8 Shock_BlutoothState_Change;
	uint8 Shock_BlutoothState;
	uint8 Shock_State;
	uint8 Shock_PrevState;
	uint8 Shock_Counter;
	uint8 Shocktimer;
	uint8 Shock_DelayTimer;
	uint8 Shock_LogicStage;
} DetectPin;
/***********************************
	 VARIABLE
***********************************/

/***********************************
	CONSTANT
***********************************/
//detectpin.Shock_BlutoothState_Change
#define C_BT_UNCHANGE	0x00
#define C_BT_CHANGE		0x01

//detectpin.Shock_BlutoothState
#define C_BT_OFF	0x00
#define C_BT_ON		0x01
	//----BT_ON/OFF_cmd
	#define C_UART_BT_ON					0x80
	#define C_UART_BT_OFF					0x81

//detectpin.Shock_State
#define C_UNPLUG	0x00	//5.6s[0xa0*0.035s(tmer0)]
#define C_PLUGIN	C_DETECT_Pin

//detectpin.Shock_LogicStage
#define C_LOGICSTAGE_0	0x00
#define C_LOGICSTAGE_1	0x01
#define C_LOGICSTAGE_2	0x02
#define C_LOGICSTAGE_3	0x03

//AUDIO SWITCH Pin
#define C_AUDIOSWITCH_Pin	0x02
//DETECT Pin
#define C_DETECT_Pin	0x04//PC2
//MUTE_CTRL Pin
#define C_MUTECTRL_Pin	0x01
#define C_HIGH			1
#define C_LOW			0

//pin
#define	IR_ENABLE		0x04
#define	RC5_OUT			0x01
#define	C_I2C_REQ		0x08
/***********************************
	FUNCTION
***********************************/
void detectpin_init(void);
void detectpin_handle(void);
void detectpin_ChkBT_UartCmd(uint8 data);

void Set_Disable(uint8 Pin);
void Set_Enable(uint8 Pin);

