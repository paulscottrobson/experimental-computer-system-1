// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		processor.h
//		Purpose:	Processor Emulation (header)
//		Created:	26th October 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifndef _SYS_PROCESSOR_H
#define _SYS_PROCESSOR_H

// *******************************************************************************************************************************
//															Timing
// *******************************************************************************************************************************
	
#define CYCLES_PER_SECOND	(500000/2)												// Clock at 500Khz, 2 Clocks per T-State	
#define FRAME_RATE			(60)													// Frame rate
#define CYCLES_PER_FRAME	(CYCLES_PER_SECOND/FRAME_RATE)							// T-States per second.


typedef unsigned short WORD16;														// 8 and 16 bit types.
typedef unsigned char  BYTE8;
typedef unsigned int   LONG32;

#define RAMSIZE 	(4096)															// RAM we have installed
#define MEMORYMASK	(RAMSIZE-1)

#define DEFAULT_BUS_VALUE (0xFF)													// What's on the bus if it's not memory.
#define PCTR	PC[PCP]

void CPUReset(void);																// CPU methods
BYTE8 CPUExecuteInstruction(void);													// Execute one instruction (multi phases)
void CPUInterruptRequest(void);														// Request Interrupt.

void HWIReset(void);																// Reset hardware.
void HWIEndFrame(void);																// End frame.
BYTE8 HWIReadKeyboard(void);														// Read keyboard
int HWIProcessKey(int key,int isRunTime);											// Process debug key (Win only)
void HWIWriteDisplay(BYTE8 display);												// Write to display.
BYTE8 *HWIGetVideoMemory(void);														// Access VRAM.

#ifdef INCLUDE_DEBUGGING_SUPPORT													// Only required for debugging

typedef struct _CPUSTATUS {
	int a,b,c,d,e,h,l,zFlag,pFlag,cFlag,sFlag,hFlag;								// 8008 registers
	int pc,stack[8],stackDepth,interruptEnabled;									// PC and Stack.
	int cycles;																		// Elapsed cycles
	int hl,m;																		// Helper stuff.
} CPUSTATUS;

CPUSTATUS *CPUGetStatus(void);														// Access CPU State
void CPULoadBinary(char *fileName);													// Load Binary in.
BYTE8 CPURead(WORD16 address);														// Access RAM
BYTE8 CPUExecute(WORD16 break1,WORD16 break2);										// Run to break point(s)
WORD16 CPUGetStepOverBreakpoint(void);												// Get step over breakpoint

#endif
#endif