/*	readuart.h	*/
#include "datatype.h"

/**********************************************************
	CONSTANT
**********************************************************/
//no of data cmd
#define C_NOOFDATACMD	0x04
//readuart.state
/*
#define C_NODATA			0x00
#define C_JUSTGETDATA		0x01
#define C_SENDDATA			0x02
#define C_ENDDATA			0x03
#define C_JUSTGETRESPONCE	0x06
*/
#define C_INIT_STATE		0x00
#define C_PRESS_STATE		0x02
#define C_UNPRESS_STATE		0x01

//readuart.timer
#define C_RESETTIMER	0x00
#define C_FULLTIME		0x0c		//35*12=420ms


//----------------
// readuart.data[](startcmd)
#define C_BUT_PRESS_startcmd		0x02//'2'//0x02
#define C_BUT_RELEASE_startcmd		0x03//'3'//0x03
#define C_End						0xff//'f'//0xff
#define C_Len						0x01//'1'//0x01	
#define C_RESPEnd					0xff
#define C_RESPLen					0x00

	//-----OK/Error Responce
#define C_OK_startcmd				0xfd
#define C_ERROR_startcmd			0xfe
	//----BT_ON/OFF_cmd
//#define C_UART_BT_ON					0x80
//#define C_UART_BT_OFF					0x81
//----------------
	
//readuart.counter
#define C_COUNTCmd	0x00
#define C_COUNTLen	0x01
#define C_COUNTBut	0x02
#define C_COUNTEnd	0x03
	//-----OK/Error Responce
#define C_COUNT_RESPEnd	0x02
#define C_COUNT_RESPLen	0x01
#define C_COUNT_RESPCmd	0x00

//------------------------------
//readuart.action_cmd	
#define C_NOCmd			0x00
#define C_ERRORCmd		0xf0

#define C_PLAYCmd		0x01
#define C_PAUSECmd		0x02
#define C_STOPCmd		0x03
#define C_FFCmd			0x04
#define C_REWCmd		0x05
#define C_NEXTTRACKCmd	0x06
#define C_PREVTRACKCmd	0x07
/*
#define C_INPSELCmd		0x11
#define C_POWERCmd		0x12
#define C_VOLIncCmd		0x13
#define C_VOLDecCmd		0x14
*/
#define C_INPSELCmd		0x01
#define C_POWERCmd		0x02
#define C_VOLIncCmd		0x03
#define C_VOLDecCmd		0x04

//readuart.enableflag
#define C_ENABLE		0x01
#define C_DISABLE		0x00

//readuart.tx_toggle
#define C_TOGGLELow		0x00
#define C_TOGGLEHigh	0x01


//replay BlueCore cmd
#define C_REPLY_BC_OKCmd		0xfd
#define C_REPLY_BC_ErrorCmd		0xfe
#define C_REPLY_BC_Len			0x00
#define C_REPLY_BC_End			0xff

//uart_data
#define C_BIT6_7		0xc0
#define C_BIT0_5		0x3f
#define C_PRESS_IND		0x00
#define C_RELEASE_IND	0x40
#define C_BUT_MIN		0x00
#define C_BUT_MAX		0x04
/**********************************************************
	STRUCTURE
**********************************************************/
typedef struct
{
	 uint8 state;
	 uint8 timer;
	 uint8 data[4];
	 uint8 counter;
	 uint8 action_cmd;
	 uint8 enableflag;
	 uint8 tx_toggle;
	 uint8 prev_action_cmd;
} READUART;
READUART readuart;

/**********************************************************
	Function
***********************************************************/
//void readuart_sendRC5(uint8 ReplyCmd,uint8 Tx_toggle);
void readuart_sendRC5(void);

//void readuart_replyBlueCoreCmd(uint8 ReplyCmd);
void readuart_init(uint8 ClearPrevActionCmd);
//void readuart_DecodeResponce(void);
void readuart_DecodeData(uint8 uart_data);
//uint8 readuart_chkpacketcmd(uint8 startcmd);
void detectpin_ChkBT_UartCmd(uint8 data);
