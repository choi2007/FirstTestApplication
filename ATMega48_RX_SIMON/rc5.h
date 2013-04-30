#ifndef _RC5_H_
#define _RC5_H_

#include "datatype.h"

/**********************************************************
	Constants
**********************************************************/

// Pins
#define C_PD2		0x04
#define C_PB1		0x02
#define	IR_ENABLE	0x04
#define	RC5_OUT		0x01
 
// Logic
#define RC5_NEG_LOGIC
#define RC5_HIGH	1
#define RC5_LOW		0

// Tick	(By measurement, every timer interrupt = TICK_TIME = 11.5us but not 10us)
#define RC5_ERROR				32L		// Bit width tolerance in %
#define RC5_REPEAT_FRAME_TICK	7500L//9896L	// Repeat = 113.8ms (1138/TICKTIME)
#define RC5_HALF_BIT_TICK		77L		// Half bit = 889us	(890/TICK_TIME)
#define RC5_FULL_BIT_TICK		155L	// Full bit = 1778us (1778/TICK_TIME)
#define RC5_DELTA				(RC5_HALF_BIT_TICK*RC5_ERROR/100L)

#define RC5_NO_EXT	0xFF

// RC5 commands
enum
{
	RC5_PLAY_PAUSE,
	RC5_NEXT_TRACK,
	RC5_PREV_TRACK,
	RC5_NEXT_ALBUM,
	RC5_PREV_ALBUM,
	RC5_STOP,
	RC5_PLAY,
	RC5_PAUSE,
	RC5_MUTE_TOGGLE,
	RC5_MUTE_ON,
	RC5_MUTE_OFF,
	RC5_NEXT_CHAP,
	RC5_PREV_CHAP,
	RC5_NEXT_PLAYLIST,
	RC5_PREV_PLAYLIST,
	RC5_SHUFFLE_TOGGLE,
	RC5_SHUFFLE_TRACKS,
	RC5_SHUFFLE_ALBUMS,
	RC5_SHUFFLE_OFF,
	RC5_REPEAT_TOGGLE,
	RC5_REPEAT_TRACK,
	RC5_REPEAT_ALL,
	RC5_REPEAT_OFF,
	RC5_POWER_ON,
	RC5_POWER_OFF,
	RC5_POWER_TOGGLE,
	RC5_BACKLIGHT_30S,
	RC5_BACKLIGHT_TOGGLE,
	RC5_BACKLIGHT_OFF,
	RC5_BEGIN_FF,
	RC5_BEGIN_REW,
	RC5_MENU,
	RC5_SELECT_OK,
	RC5_UP,
	RC5_DOWN,

	RC5_IMAGE_PLAY_PAUSE,
	RC5_IMAGE_NEXT_IMAGE,
	RC5_IMAGE_PREV_IMAGE,
	RC5_IMAGE_STOP,
	RC5_IMAGE_PLAY,
	RC5_IMAGE_PAUSE,
	RC5_IMAGE_SHUFFLE_TOGGLE,
	RC5_IMAGE_SHUFFLE_TRACKS,
	RC5_IMAGE_SHUFFLE_ALBUMS,
	RC5_IMAGE_SHUFFLE_OFF,
	RC5_IMAGE_REPEAT_TOGGLE,
	RC5_IMAGE_REPEAT_TRACK,
	RC5_IMAGE_REPEAT_ALL,
	RC5_IMAGE_REPEAT_OFF,
	
	RC5_VIDEO_PLAY_PAUSE,
	RC5_VIDEO_NEXT_VIDEO,
	RC5_VIDEO_PREV_VIDEO,
	RC5_VIDEO_STOP,
	RC5_VIDEO_PLAY,
	RC5_VIDEO_PAUSE,
	RC5_VIDEO_FF,
	RC5_VIDEO_REW,
	RC5_VIDEO_NEXT_CHAP,
	RC5_VIDEO_PREV_CHAP,
	RC5_VIDEO_NEXT_FRAME,
	RC5_VIDEO_PREV_FRAME,
	RC5_VIDEO_CAPTION,
	
	RC5_AUDIO_PLAY_PAUSE,
	RC5_AUDIO_NEXT_TRACK,
	RC5_AUDIO_PREV_TRACK,
	RC5_AUDIO_NEXT_ALBUM,
	RC5_AUDIO_PREV_ALBUM,
	RC5_AUDIO_STOP,
	RC5_AUDIO_PLAY,
	RC5_AUDIO_PAUSE,
	RC5_AUDIO_MUTE_TOGGLE,
	RC5_AUDIO_MUTE_ON,
	RC5_AUDIO_MUTE_OFF,
	RC5_AUDIO_NEXT_CHAP,
	RC5_AUDIO_PREV_CHAP,
	RC5_AUDIO_NEXT_PLAYLIST,
	RC5_AUDIO_PREV_PLAYLIST,
	RC5_AUDIO_SHUFFLE_TOGGLE,
	RC5_AUDIO_SHUFFLE_TRACKS,
	RC5_AUDIO_SHUFFLE_ALBUMS,
	RC5_AUDIO_SHUFFLE_OFF,
	RC5_AUDIO_REPEAT_TOGGLE,
	RC5_AUDIO_REPEAT_TRACK,
	RC5_AUDIO_REPEAT_ALL,
	RC5_AUDIO_REPEAT_OFF,
	RC5_AUDIO_FF,
	RC5_AUDIO_REW,

	RC5_AMP_POWER,
	RC5_AMP_INPUT,
	RC5_AMP_VOL_UP,
	RC5_AMP_VOL_DOWN,

	RC5_MAX
};

#define RC5_TX_BUF_SIZE	10
#define RC5_RX_BUF_SIZE 1


/**********************************************************
	Structures
**********************************************************/

typedef struct
{
	uint8 stream[6];	// stream[5] Bit 7 is bExt
} RC5_FRAME;

typedef struct
{
	/*
	struct
	{
		volatile uint16 prevTimer;	// Debug use
		volatile uint16 timer, frameTimer;
		volatile uint16 cnt;
		RC5_FRAME *head, *tail;
		RC5_FRAME buf[RC5_RX_BUF_SIZE];
		
		RC5_FRAME frame;
		uint8 bits, halfBits, logic;
		bool bWaitingExt, bExt;
		uint8 bitStream[23];	// start from 1, debug use
		bool enabled;
	} rx;
	*/
	
	struct
	{
		volatile uint32 timer, frameTimer;
		volatile uint16 cnt;
		RC5_FRAME *head, *tail;
		RC5_FRAME buf[RC5_TX_BUF_SIZE];

		//RC5_FRAME frame;
		volatile uint8 bits, halfBits;
		volatile uint8 logic;
		bool bExt;
		uint8 stream[6], pos, shift, toggle;
		bool enabled;
	} tx;
} RC5_DATA;

/**********************************************************
	Variables
**********************************************************/

extern RC5_DATA rc5;

/**********************************************************
	Functions
**********************************************************/

void rc5_init(void);

/*
volatile uint16 rc5_getRxCnt(void);

void rc5_getFrame(RC5_FRAME *frame);
volatile uint16 rc5_getTxCnt(void);

void rc5_receive(void);
void rc5_decode(RC5_FRAME *frame);
*/

void rc5_putFrame(RC5_FRAME *frame);
void rc5_transmit(void);
void rc5_sendInput(void);

#endif /* _RC5_H_ */
