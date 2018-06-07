#include <LPC17xx.H>
#include "lpc1768_timer.h"
#include "LCD.h"
#include "game.h"


volatile uint32_t DelayCounter = 0;
int i=0;
int j=0;
void (*pTimer0Callback)(void);
void (*pTimer1Callback)(void);
static void nop(void)
{
    return;
}
uint32_t init_timer0(uint8_t timer_num)   //1ms
{
    if(timer_num == 0)
	{
	    NVIC_EnableIRQ(TIMER0_IRQn);
		LPC_TIM0->CTCR = 0;
		LPC_TIM0->PR = (25000000UL/2000-1);
		LPC_TIM0->MR0 = 2-1;
		LPC_TIM0->MCR = 3;
		LPC_TIM0->EMR = (0x3 << 4);
		LPC_TIM0->TCR = TCR_COUNTER_ENABLE;
		pTimer0Callback = nop;
		return(1);
	}
}
uint32_t init_timer1(uint8_t timer_num)  //200ms
{
    if(timer_num == 0)
	{
	    NVIC_EnableIRQ(TIMER1_IRQn);
		LPC_TIM1->CTCR = 0;
		LPC_TIM1->PR = (25000000UL/10-1);
		LPC_TIM1->MR0 = 2-1;
		LPC_TIM1->MCR = 3;
		LPC_TIM1->EMR = (0x3 << 4);
		LPC_TIM1->TCR = TCR_COUNTER_ENABLE;
		pTimer1Callback = nop;
		return(1);
	}
}
void DelayMs(uint32_t delayInMs)
{
    if(delayInMs == 0)
	    return;
	DelayCounter = delayInMs;
	while(DelayCounter);
	return;
}

void TIMER0_IRQHandler (void)
{
    LPC_TIM0->IR = 1;
	if(DelayCounter)
		DelayCounter--;
    pTimer0Callback();
}
void TIMER1_IRQHandler (void)
{
    LPC_TIM1->IR = 1;
    DrawName();
    if(gameover==0) move();
    else LCD_DisplayString(80,130,"Game Over!");
    pTimer0Callback();
}
