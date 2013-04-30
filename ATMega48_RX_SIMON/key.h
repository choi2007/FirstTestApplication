/*	key.h	*/
#include "datatype.h"
/**********************************************************
	Structure
**********************************************************/
typedef struct
{
	uint8 buttonPressRecord;
	uint8 buttonPressFlag;
	uint8 buttonReleaseFlag;

	uint8 buttonUpdatedRecord;

} Key_Record;

/**********************************************************
	Constant
**********************************************************/
#define _BV(bit) (1 << (bit))
#define C_BUTTONCmd		1
#define C_RESPONCECmd	2
#define C_INCORRECT		0

//	buttonPressFlag
#define C_UnPress	0
#define C_Press		1

//	buttonReleaseFlag
#define C_NotRelease	0
#define C_Release		1

//	buttonPressRecord
#define C_NoPressRecord		255
#define C_PlayRecord		0x01
#define C_PauseRecord		0x02
#define C_StopRecord		0x03
#define C_FfRecord			0x04
#define C_RewRecord			0x05
#define C_NextTRecord		0x06
#define C_PrevTRecord		0x07
#define C_InputSelRecord	0x11
#define C_PowerRecord		0x12
#define C_VolInRecord		0x13
#define C_VolDecRecord		0x14

//ReleasCmd
#define C_RELEASE_BIT	0x40
//*
//	buttonUpdatedRecord;
/*#define C_NoPressRecord		255
#define C_PlayRecord		0x01
#define C_PauseRecord		0x02
#define C_StopRecord		0x03
#define C_FfRecord			0x04
#define C_RewRecord			0x05
#define C_NextTRecord		0x06
#define C_PrevTRecord		0x07
#define C_InputSelRecord	0x11
#define C_PowerRecord		0x12
#define C_VolInRecord		0x13
#define C_VolDecRecord		0x14
*/
//---chould be change to BleCore ON/OFF cmd later
#define C_BlueCoreOnRecord			0x15
#define C_BlueCoreOffRecord			0x16
//---
//*/

/*
#define C_PowerRecord		0
#define C_AmpPowerRecord	1
#define C_InputRecord		2
#define C_VolUpRecord		3
#define C_VolDownRecord		4
#define C_MenuRecord		5
#define C_UpRecord			6
#define C_DownRecord		7
#define C_SelectRecord		8
#define C_ForwardRecord		9
#define C_RewindRecord		10
#define C_PlayPauseRecord	11
#define C_RepeatRecord		12
#define C_ShuffleRecord		13
#define C_MaxRecord			14
*/

// Button Press Command Format
#define BP_Cmd			0x12
#define BP_Len			0x01
#define BP_End			0xff

// Button Release Command Format
#define BR_Cmd			0x13
#define BR_Len			0x01
#define BR_End			0xff

// BlueCore On/Off Command Format
#define BC_OnOffCmd			0x14
#define BC_OnOffLen			0x01
#define BC_OnOffEnd			0xff

#define BC_OffState			0x00
#define BC_OnState			0x01

// Button Press Indication commands(Payloads)
#define BP_Play			0x01
#define BP_Pause		0x02
#define BP_Stop			0x03
#define BP_Ff			0x04
#define BP_Rew			0x05
#define BP_NextT		0x06
#define BP_PrevT		0x07
#define BP_InputSel		0x11
#define BP_Power		0x12
#define BP_VolIn		0x13
#define BP_VolDec		0x14

// Button Release Indication commands(Payloads)
#define BR_Play			0x01
#define BR_Pause		0x02
#define BR_Stop			0x03
#define BR_Ff			0x04
#define BR_Rew			0x05
#define BR_NextT		0x06
#define BR_PrevT		0x07
#define BR_InputSel		0x11
#define BR_Power		0x12
#define BR_VolIn		0x13
#define BR_VolDec		0x14

/**********************************************************
	Variables
**********************************************************/
Key_Record key;
/**********************************************************
	Functions
**********************************************************/
//------------main.c
void key_handler(void);
//------------ key.h
void key_init(void);
void key_chk_rc5_signalrelease(void);
void key_pressconfirm_action(uint8 PressButton,uint8 PressButtonCmd,uint8 ReleaseButtonCmd);
void SetPortC(unsigned char InputPort, unsigned char Data);
