// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		hardware.c
//		Purpose:	Hardware handling routines (
//		Created:	29th June 2016
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "sys_processor.h"

static BYTE8 isInitialised = 0;												// Non zero when initialised
static BYTE8 pendingKey = 0;												// Key ready ?

static BYTE8 displayRAM[512];												// 64 lines of 8 bytes/64 pixels per line
static BYTE8 framesSinceEnabled = 0;										// Number of frames since display last enabled
static BYTE8 displayIsRunning = 0;											// True when display is running (e.g. visible)
static BYTE8 xCursor = 0,yCursor = 0;										// Drawing position on display.

// *******************************************************************************************************************************
//													Reset all hardware
// *******************************************************************************************************************************

void HWIReset(void) {
	if (isInitialised == 0) {
		isInitialised = 1;
		pendingKey = 0;														// Clear keyboard buffer
	}
}

// *******************************************************************************************************************************
//													Handle on end of frame.
// *******************************************************************************************************************************

void HWIEndFrame(void) {
	if (displayIsRunning) {													// Track time display is on.
		framesSinceEnabled = 0;												// Display is on.
	} else {																// Display is off.
		if (++framesSinceEnabled == 200) framesSinceEnabled = 200;			// Bump frames since enabled, limit to 200 (4s)
	}
}

// *******************************************************************************************************************************
//								Convert standard ASCII to ECS keyboard input (see ECS-5 Page 13)
// *******************************************************************************************************************************

static BYTE8 HWIASCIIToECS(BYTE8 ch) {
	BYTE8 result = 0xC0;													// Normal is 11xx xxxx
	if (ch < ' ') result = 0x40;											// Ctrl something turns off bit 7 01xx xxxx
	if (ch >= 96) result = 0x80;											// Shift turns off bit 6 10xx xxxx
	if (ch >= 'A' && ch <= 'Z') result = 0x80;								// Capital implies shift pressed.
	if (ch >= 'a' && ch <= 'z') {											// lower case, then shift not pressed.
		ch = ch - 32;														// make U/C
		result = 0xC0;								
	}
	result = result | (ch & 0x3F);											// Put 64 bit ASCII value in.
	if (ch == 0) result = 0xFF;												// No key pressed returns 0xFF
	if (ch == 0x0D) result = 0xFE;											// Return key returns 0xFE
	return result;
}

// *******************************************************************************************************************************
//									Debugger key intercept handler
// *******************************************************************************************************************************

int HWIProcessKey(int key,int isRunTime) {
	if (key != 0 && isRunTime != 0) {										// Running and key press
		BYTE8 newKey = GFXToASCII(key,1);									// Convert to ASCII
		if (newKey != 0) pendingKey = newKey;								// Put pending key in buffer
		if (pendingKey != 0) CPUInterruptRequest();							// Request Interrupt
	}
	return key;
}

// *******************************************************************************************************************************
//							Read keyboard. Technically wrong as only reads non-xFF for one read
// *******************************************************************************************************************************

BYTE8 HWIReadKeyboard(void) {
	BYTE8 rv = 0;
	if (pendingKey != 0) {													// Key waiting.
		rv = pendingKey;
		pendingKey = 0;														// Clear buffer
	}
	return HWIASCIIToECS(rv);												// Return appropriate ECS keyboard value.
}

// *******************************************************************************************************************************
//														Access video memory
// *******************************************************************************************************************************

BYTE8 *HWIGetVideoMemory(void) {
	if (framesSinceEnabled > FRAME_RATE/10) return NULL;					// Fade out after 1/10s.
	return displayRAM;
}

// *******************************************************************************************************************************
//													Set and clear pixel routines
// *******************************************************************************************************************************

void _HWISetPixel(void) {
	BYTE8 bit = (0x80 >> (xCursor & 7));									// bit mask.
	WORD16 addr = (xCursor >> 3) + yCursor * 8;								// address in video RAM.
	if ((displayRAM[addr] & bit) == 0) {									// only update if clear.
		displayRAM[addr] |= bit;											// set bit.
	}
}

void _HWIClearPixel(void) {
	BYTE8 bit = (0x80 >> (xCursor & 7));									// bit mask.
	WORD16 addr = (xCursor >> 3) + yCursor * 8;								// address in video RAM.
	if ((displayRAM[addr] & bit) != 0) {									// only update if set.
		displayRAM[addr] &= (bit ^ 0xFF);									// clear bit.
	}
}

// *******************************************************************************************************************************
//															Write to display
// *******************************************************************************************************************************

void HWIWriteDisplay(BYTE8 display) {
	if (displayIsRunning != 0) {											// Display is running. Only interested in TSF
		if ((display & 0307) == 0201) displayIsRunning = 0;					// TSF:2x1 because that turns the scan off.
	} else {																// Display is accessible.
		switch(display >> 6) {
			case 0:															// STX:0xx set x cursor
				xCursor = display & 0x3F;
				break;
			case 1:															// STY:1xx set y cursor
				yCursor = display & 0x3F;
				break;
			case 2:															// 2xc commands
				switch(display & 0307) {
					case 0200:												// 2x0:DCY decrement Y
						yCursor = (yCursor - 1) & 0x3F;
						break;
					case 0202:												// 2x2:ZON set Z on
						_HWISetPixel();
						break;
					case 0203:												// 2x3:ZOF set Z off
						_HWIClearPixel();
						break;
					case 0204:												// 2x4:ZNI set Z on and increment X
						_HWISetPixel();
						xCursor = (xCursor + 1) & 0x3F;
						if (xCursor == 0) yCursor = (yCursor + 1) & 0x3F;
						break;
					case 0205:												// 2x5:ZFI set Z off and increment X
						_HWIClearPixel();
						xCursor = (xCursor + 1) & 0x3F;
						if (xCursor == 0) yCursor = (yCursor + 1) & 0x3F;
						break;
					case 0206:												// 2x6:TSN turn scan on
						displayIsRunning = 1;
						break;
					case 0207:												// 2x7:DCX decrement X
						if (xCursor == 0) yCursor = (yCursor - 1) & 0x3F;
						xCursor = (xCursor - 1) & 0x3F;
						break;
				}
				break;
		}
	}
}
