#include "detectpin.h"
#include "key.h"
#include "uart.h"
DetectPin	detectpin;
/**********************************************************
	DETECT_PIN_HANDLE
**********************************************************/
/*
void detectpin_ChkBT_UartCmd(uint8 data)
{
	if(data==C_UART_BT_ON)
	{
		detectpin.Shock_BlutoothState		=C_BT_ON;
		detectpin.Shock_BlutoothState_Change=C_BT_CHANGE;
	}
	if(data==C_UART_BT_OFF)
	{
		detectpin.Shock_BlutoothState		=C_BT_OFF;
		detectpin.Shock_BlutoothState_Change=C_BT_CHANGE;
	}
}
*/
//----------------------------------
void detectpin_readpin(void)
{

	static uint8 i, tempPortState, tempPrevPortState;
	//chk timer, chk port every 35ms*4
	if((detectpin.Shocktimer>=1)&&(detectpin.Shock_LogicStage	==C_LOGICSTAGE_0))
	{
		//set port 
//		DDRC	&=~C_DETECT_Pin;
//		PORTC	&=~C_DETECT_Pin;
		DDRC	&=~C_I2C_REQ;
		PORTC	&=~C_I2C_REQ;
		//read port
		i=0;
		while(i<=20)
			{
				tempPortState	=PINC	&C_I2C_REQ;
				if(tempPrevPortState	!=tempPortState)
				{
					tempPrevPortState	=tempPortState;
					i=0;
				}
				else
					i++;
			}
		//compare state and update counter
		if(detectpin.Shock_PrevState	==tempPortState)
			detectpin.Shock_Counter++;
		else
		{
			detectpin.Shock_Counter=0;
			detectpin.Shock_PrevState	=tempPortState;
		}
		//update state
		if(detectpin.Shock_Counter	>=5)
		{
			detectpin.Shock_Counter	=0;
			if(detectpin.Shock_State	!=detectpin.Shock_PrevState)
			{
				detectpin.Shock_State	=detectpin.Shock_PrevState;
				detectpin.Shock_LogicStage	=C_LOGICSTAGE_1;
				
			}		 

		}
		detectpin.Shocktimer=0;
	}
}

//----------------------------------
void detectpin_ChangeSetAudio_DetectSwitch(uint8 State)
{

//	DDRD	|=0xc0;
	DDRC	|=C_AUDIOSWITCH_Pin;
//	if(State	== C_BT_OFF)
	if(State	== 0x00)		//BloothTooth OFF state
	{
		//set AudioSwitch Pin OUTPUT HIGH
		PORTC	|=C_AUDIOSWITCH_Pin;
		//PORTC	&=~C_AUDIOSWITCH_Pin;
//		PORTD	|=0xc0;
	}
	else
	{
		//set AudioSwitch Pin OUTPUT LOW
		//PORTC	|=C_AUDIOSWITCH_Pin;
		PORTC	&=~C_AUDIOSWITCH_Pin;

//		PORTD	&=~0xc0;
	}
//--------
/*
//	if(State	== C_BT_OFF)
	if(State	== 0x00)		//BloothTooth OFF state
	{
		//high impedence
		DDRC	&=~C_DETECT_Pin;
		PORTC	&=~C_DETECT_Pin;
	}
	else
	{
		//output high
		DDRC	|=C_DETECT_Pin;
		PORTC	|=C_DETECT_Pin;

	}
*/
}
//--------------------------------
void detectpin_ChangeSetMuteCtrl(uint8 State)
{

	if(State	==C_HIGH)
	{
		//set AudioSwitch Pin OUTPUT HIGH
		DDRC	|=C_MUTECTRL_Pin;
		PORTC	|=C_MUTECTRL_Pin;
	}
	else
	{
		//set AudioSwitch Pin HIGH IMPEDENCE
		DDRC	&=~C_MUTECTRL_Pin;
		PORTC	&=~C_MUTECTRL_Pin;
	}
}
//--------------------------------
void detectpin_init()
{
//	detectpin.Shock_BlutoothState =C_BT_OFF;
//	detectpin_ChangeSetAudio_DetectSwitch(C_BT_OFF);
	detectpin_ChangeSetAudio_DetectSwitch(0x00);

	detectpin.Shocktimer		=0;
	detectpin.Shock_PrevState	=0;
//	detectpin.Shock_State		=0xff;
	detectpin.Shock_State		=0;
	detectpin.Shock_Counter		=0;
	detectpin.Shock_LogicStage	=C_LOGICSTAGE_0;
//		detectpin_ChangeSetMuteCtrl(C_LOW);
}
//--------------------------------
/*
void detectpin_ChangeSetBluetoothCmd(uint8 State)
{
	
	uart_putchar(BC_OnOffCmd);
	uart_putchar(BC_OnOffLen);
	//-----------
	if(State	==C_PLUGIN)
		uart_putchar(BC_OffState);
	else
		uart_putchar(BC_OnState);
	//-----------
	uart_putchar(BC_OnOffEnd);
}
*/
//----------------------------------
void detectpin_ChangeAction(void)
{
//	static uint8 i; 
	
	if(detectpin.Shock_LogicStage	==C_LOGICSTAGE_1)
	{
	//set mute_ctrl
		detectpin_ChangeSetMuteCtrl(C_HIGH);
		
		detectpin.Shock_DelayTimer	=0;
		detectpin.Shock_LogicStage	=C_LOGICSTAGE_2;
	}
	if(detectpin.Shock_LogicStage	==C_LOGICSTAGE_2)
	{	
	//---delay loop for reduce the hardware "pop" sound
//		if(detectpin.Shock_DelayTimer>=5)	//delay time=(Timer0[35ms] *5)=165ms
		if(detectpin.Shock_DelayTimer>=43)	//delay time=(Timer0[35ms] *43)=1.5s
		{
			detectpin.Shock_LogicStage	=C_LOGICSTAGE_3;
				//set audio switch+detectpin
//			detectpin_ChangeSetAudio_DetectSwitch(detectpin.Shock_BlutoothState);			
			detectpin_ChangeSetAudio_DetectSwitch(detectpin.Shock_State);//I2C_REQ pin

			detectpin.Shock_DelayTimer	=0;
		}
	}
	if(detectpin.Shock_LogicStage	==C_LOGICSTAGE_3)
	{	
	//set audio switch
	//	detectpin_ChangeSetAudioSwitch(detectpin.Shock_State);
	//set uart cmd to ON/OFF BC 
		
	//---delay loop for reduce the hardware "pop" sound
//		if(detectpin.Shock_DelayTimer>=5)	//delay time=(Timer0[35ms] *5)=165ms		
		if(detectpin.Shock_DelayTimer>=43)	//delay time=(Timer0[35ms] *43)=1.5s
		{
			//detectpin_ChangeSetBluetoothCmd(detectpin.Shock_State);
			detectpin_ChangeSetMuteCtrl(C_LOW);
			detectpin.Shock_LogicStage	=C_LOGICSTAGE_0;
			//-----------
			/*
			main_init();
			if(detectpin.Shock_State==C_PLUGIN)
			{
				Set_Enable(IR_ENABLE);
				Set_Disable(RC5_OUT);
				//disable hardware interrupt,RC5_IN
				PCICR &= ~_BV(PCIE0) ;
			}
			*/
		}
	}

}
//----------------------------------
void detectpin_handle(void)
{
//	static uint8 i, tempPortState, tempPrevPortState;

	detectpin_readpin();
	detectpin_ChangeAction();
}
