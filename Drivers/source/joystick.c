#include <stdint.h>
#include "LPC17xx.h"
#include "lpc1768_timer.h"
#include "joystick.h"
#include "bmboard.h"
typedef enum
{
	KEY_IDLE,
	KEY_PRESSED,
	KEY_RELEASED,
	KEY_PRESS_CONFIRMED,
	KEY_RELEASE_CONFIRMED
}KEY_FSM_STATUS;



void (*oldcb)(void);
KEY_FSM_STATUS status;
KEY_TypeDef Key;

void Joystick_Config(void)
{
	LPC_PINCON->PINSEL3 = 0;
	LPC_GPIO1->FIODIR = ~(JOY_ENTER | JOY_LEFT | 
	                      JOY_RIGHT | JOY_UP | JOY_DOWN);
	oldcb = pTimer0Callback;
	pTimer0Callback = KeyboardScan;
	
	status = KEY_IDLE;
}


KEY_TypeDef GetKey()
{
	KEY_TypeDef CurKey;
	CurKey.KeyValue = Key.KeyValue;
	CurKey.Pressed = Key.Pressed;
	CurKey.Released = Key.Released;
	
	if(status == KEY_RELEASE_CONFIRMED)
	{
		Key.KeyValue = KEY_VALUE_NOKEY;
	    Key.Pressed = 0;
	    Key.Released = 0;
		status = KEY_IDLE;
    }
	else if(status == KEY_PRESS_CONFIRMED || status == KEY_RELEASED)
		Key.Pressed = 0;
	return CurKey;
}


void KeyboardScan()
{
    static uint8_t counter=0;
	uint32_t key;
	
	if(counter++ < 15)
	{
	    oldcb();
		return;
	}
	else
	{
	    counter = 0;
	    key = ~(LPC_GPIO1->FIOPIN) & 0x3E000000;
		
		if(key & JOY_UP)             key = KEY_VALUE_UP;
		else if(key & JOY_DOWN)      key = KEY_VALUE_DOWN;
		else if(key & JOY_LEFT)      key = KEY_VALUE_LEFT;
		else if(key & JOY_RIGHT)     key = KEY_VALUE_RIGHT;
		else if(key & JOY_ENTER)     key = KEY_VALUE_ENTER;
		else                         key = KEY_VALUE_NOKEY;
	}
	
	switch(status)
	{
	    case KEY_IDLE:
			if(key)
				status = KEY_PRESSED;
			break;
			
		case KEY_PRESSED:
			if(key)
			{
				status = KEY_PRESS_CONFIRMED;
				Key.KeyValue = key;
				Key.Pressed = 1;
            }
			else
				status = KEY_IDLE;
			break;
			
		case KEY_PRESS_CONFIRMED:
			if(key)
				status;
			else
				status = KEY_RELEASED;
			break;
			
		case KEY_RELEASED:
			if(key)
				status = KEY_PRESS_CONFIRMED;
			else
			{
				status = KEY_RELEASE_CONFIRMED;
				Key.Released = 1;
            }
			break;
			
		case KEY_RELEASE_CONFIRMED:
			if(key)
			{
				status = KEY_PRESSED;
				Key.KeyValue = key;
            }
			break;
	}
	oldcb();
}

