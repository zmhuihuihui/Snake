/******************************************************************************/
/* Blinky.c: LED Flasher and graphic demo                                     */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2009 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "LCD.h"
#include "string.h"
#include "logo.h"
#include "game.h"

int main (void)                        /* Main Program                       */
{
	LCD_Init();
    init_timer0(0);
    LCD_ClearScreen (LCD_COLOR_WHITE);
    LCD_ShowBmp(100,20,100,124, (uint16_t*)logo);
    LCD_SetBackColor(LCD_COLOR_WHITE);
    LCD_DisplayString(160,85,"Loading...");
    drawLoading();
    DelayMs(1000);
    LCD_SetBackColor(LCD_COLOR_BLACK);
	LCD_ClearScreen (LCD_COLOR_BLACK);
    init_timer1(0);
    gameInitial();
    gameOn();
}


