#ifndef _DATATYPE_H_
#define _DATATYPE_H_

typedef unsigned char	uint8;
typedef char			s08;
typedef unsigned short	uint16;
typedef short 			s16;
typedef uint8			bool;
typedef unsigned long	uint32;
typedef long			s32;

typedef union
{
	uint8 ch[2];
	uint16 i;
} CONV16;

typedef union
{
	uint8 ch[4];
	uint32 i;
} CONV32;
//================================
//CONSTANT
//================================
#define TRUE	1
#define FALSE	0

#endif /* _DATATYPE_H_ */
#define	C_NOTset	0x00 
#define	C_Set		0x01 

//maintype.RC5timer
#define C_OVERFLOW_mainRC5timer	0xfe	//5.6s[0xa0*0.035s(tmer0)]
#define C_RESET_mainRC5timer	0x00

//maintype.Shock_State
#define C_UNPLUG	0x00	//5.6s[0xa0*0.035s(tmer0)]
#define C_PLUGIN	C_DETECT_Pin

//miantype.Shock_LogicStage
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
