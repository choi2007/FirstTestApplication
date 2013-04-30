
#include <avr/io.h> 
#include "datatype.h"
#include "key.h"
#include "uart.h"


/**********************************************************
	Variables
**********************************************************/
// #define DEBUG_KEY
#define	CODE_REDUCEKEY
/**********************************************************
	Functions
**********************************************************/
void key_sentButtonPressCmd(uint8 PressCmd)
{	
/*
	{
		uart_putchar(BP_Cmd);
		uart_putchar(BP_Len);
			uart_putchar(PressCmd);
		uart_putchar(BP_End);
	}
*/
	uart_putchar(PressCmd);	
}
void key_sentButtonReleaseCmd(uint8 ReleasCmd)
{
	if((ReleasCmd==C_BlueCoreOffRecord)||(ReleasCmd==C_BlueCoreOffRecord))
		return;
	else
	{
		uart_putchar(ReleasCmd|C_RELEASE_BIT);
/*
		uart_putchar(BR_Cmd);
		uart_putchar(BR_Len);
			uart_putchar(ReleasCmd);
		uart_putchar(BP_End);
*/
	}

}

void key_pressconfirm_action(uint8 PressButton, uint8 PressButtonCmd, uint8 ReleaseButtonCmd)
{
					//chk the previous button release or not 			
					if(key.buttonPressFlag==C_Press)
						{
							if(key.buttonPressRecord!=PressButton)
							{
								//Release key.buttonPressRecord Button Action
								key_sentButtonReleaseCmd(ReleaseButtonCmd);
								#ifdef DEBUG_KEY
									SetPortC(0x3f,0);
								#endif
								//------------------------//
								//Press Button Action
								key_sentButtonPressCmd(PressButtonCmd);
								#ifdef DEBUG_KEY
									SetPortC(0x01,1);
								#endif
								//---------------------//
								//Set buttonPressFlag+buttonPressRecord
								key.buttonPressFlag = C_Press;
								key.buttonReleaseFlag = C_NotRelease;
								key.buttonPressRecord = PressButton;
							}	
						}
					else
						{
							//Press Button Action
							key_sentButtonPressCmd(PressButtonCmd);
							#ifdef DEBUG_KEY
								SetPortC(0x01,1);
							#endif
							//---------------------//
							//Set buttonPressFlag+buttonPressRecord
							key.buttonPressFlag = C_Press;
							key.buttonReleaseFlag = C_NotRelease;
							key.buttonPressRecord = PressButton;
						}
}
void key_reset_parameter(void)
{
	//-----reset parameter
	key.buttonPressFlag 	= C_UnPress;
	key.buttonReleaseFlag 	= C_NotRelease;
	key.buttonPressRecord	= C_NoPressRecord;
}
void key_chk_rc5_signalrelease(void)
{
	if((key.buttonPressFlag == C_Press)&&(key.buttonReleaseFlag == C_Release))
	{
		//----release button action
		key_sentButtonReleaseCmd(key.buttonPressRecord);
		#ifdef DEBUG_KEY
			SetPortC(0x01,0);
		#endif
		//-----reset parameter
		key_reset_parameter();
/*
		switch(key.buttonPressRecord)
		{

			case C_PlayRecord:
			{
				//----release button action
				key_sentButtonReleaseCmd(BR_Play);
				#ifdef DEBUG_KEY
					SetPortC(0x01,0);
				#endif
				//-----reset parameter
				key_reset_parameter();
				break;
			}	
			case C_PauseRecord:
			{
				//----release button action
				key_sentButtonReleaseCmd(BR_Pause);
				#ifdef DEBUG_KEY
					SetPortC(0x01,0);
				#endif
				//-----reset parameter
				key_reset_parameter();
				break;
			}	
			case C_StopRecord:
			{
				//----release button action
				key_sentButtonReleaseCmd(BR_Stop);
				#ifdef DEBUG_KEY
					SetPortC(0x01,0);
				#endif
				//-----reset parameter
				key_reset_parameter();
				break;
			}	
			case C_FfRecord:
			{
				//----release button action
				key_sentButtonReleaseCmd(BR_Ff);
				#ifdef DEBUG_KEY
					SetPortC(0x01,0);
				#endif
				//-----reset parameter				
				key_reset_parameter();
				break;
			}	
			case C_RewRecord:
			{
				//----release button action
				key_sentButtonReleaseCmd(BR_Rew);
				#ifdef DEBUG_KEY
					SetPortC(0x01,0);
				#endif
				//-----reset parameter
				key_reset_parameter();
				break;
			}	
			case C_NextTRecord:
			{

				//----release button action
				key_sentButtonReleaseCmd(BR_NextT);
				#ifdef DEBUG_KEY
					SetPortC(0x01,0);
				#endif
				//-----reset parameter
				key_reset_parameter();
				break;
			}	
			case C_PrevTRecord:
			{
				//----release button action
				key_sentButtonReleaseCmd(BR_PrevT);
				#ifdef DEBUG_KEY
					SetPortC(0x01,0);
				#endif
				//-----reset parameter
				key_reset_parameter();
				break;
			}
			default:
			break;
		}
*/
	}
}

//----------
void key_init(void)
{
	key.buttonPressFlag 	= C_UnPress;
	key.buttonReleaseFlag 	= C_NotRelease;
	key.buttonPressRecord 	= C_NoPressRecord;
	key.buttonUpdatedRecord	= C_NoPressRecord;
}
//----------
//	for debug								
#ifdef DEBUG_KEY
	void SetPortC(unsigned char InputPort, unsigned char Data)
	{
		DDRC |= InputPort;
		if(Data !=0x00)
			PORTC |= InputPort;	
		else
			PORTC &= ~InputPort;			
	}
#endif
