// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		sys_processor.cpp
//		Purpose:	Processor Emulation.
//		Created:	26th October 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifdef WINDOWS
#include <stdio.h>
#endif
#include "sys_processor.h"

// *******************************************************************************************************************************
//														Main Memory/CPU
// *******************************************************************************************************************************

static BYTE8 ramMemory[RAMSIZE];													// RAM memory
static BYTE8 interruptEnabled,interruptRequest;
#include "__8008_macros.h"

// *******************************************************************************************************************************
//													Memory read and write macros.
// *******************************************************************************************************************************

#define READ(a) 	ramMemory[(a) & MEMORYMASK]
#define WRITE(a,d) 	ramMemory[(a) & MEMORYMASK] = (d)

// *******************************************************************************************************************************
//														I/O Port connections
// *******************************************************************************************************************************

#define INPORT00()	( interruptEnabled = (A & 0x02) >> 1,1) 						// Port 00 : if bit 1 set enable int, return 1
#define INPORT01()	HWIReadKeyboard()												// Port 01 : Keyboard in.
#define OUTPORT08(d) HWIWriteDisplay(d)												// Port 08 : Video Display

// *******************************************************************************************************************************
//													  Port interfaces
// *******************************************************************************************************************************

void CPUReset(void) {
	Reset8008();
	interruptRequest = 0;interruptEnabled = 0;
	HWIReset();
}

// *******************************************************************************************************************************
//												    Request an interrupt
// *******************************************************************************************************************************

void CPUInterruptRequest(void) {
	interruptRequest = 1;
}

// *******************************************************************************************************************************
//													 Execute a single phase.
// *******************************************************************************************************************************

#include <stdlib.h>
#include <stdio.h>

#include "__8008_ports.h"															// Hoover up any undefined ports.

BYTE8 CPUExecuteInstruction(void) {
	if (interruptRequest != 0) {													// Interrupted.
		interruptRequest = 0;														// Clear IRQ flag
		if (interruptEnabled != 0) {												// Is interrupt enabled.
			Halt = 0;																// Clear Halt flag.
			PC[++PCP] = 0;															// Do a RST 0.
			PCP = PCP & 7;
			return 0;
		}
	}
	if (Halt == 0) {																// CPU is running (not halt)
		switch(FETCH()) {															// Do the selected opcode and phase.
			#include "__8008_opcodes.h"
		}
	}	
	if (Halt == 0 && Cycles < CYCLES_PER_FRAME) return 0;							// Frame in progress, return 0.
	Cycles -= CYCLES_PER_FRAME;														// Adjust cycle counter
	if (Halt != 0) Cycles = 0;														// Fix up for HALT.
	HWIEndFrame();																	// Hardware stuff.
	return FRAME_RATE;																// Return the frame rate for sync speed.
}

#ifdef INCLUDE_DEBUGGING_SUPPORT

// *******************************************************************************************************************************
//										 Get the step over breakpoint value
// *******************************************************************************************************************************

WORD16 CPUGetStepOverBreakpoint(void) {
	BYTE8 opcode = CPURead(PCTR);												// Read opcode.
	if ((opcode & 0xC7) == 0x07) return ((PCTR+1) & 0x3FFF);						// RST xx
	if ((opcode & 0xC3) == 0x42) return ((PCTR+3) & 0x3FFF);						// CALL xxxx (various calls)
	return 0xFFFF;
}

// *******************************************************************************************************************************
//										Run continuously till breakpoints / Halt.
// *******************************************************************************************************************************

BYTE8 CPUExecute(WORD16 break1,WORD16 break2) {
	BYTE8 rate = 0;
	while(1) {
		rate = CPUExecuteInstruction();												// Execute one instruction phase.
		if (rate != 0) {															// If end of frame, return rate.
			return rate;													
		}
		if (PCTR == break1 || PCTR == break2) return 0;
	} 																				// Until hit a breakpoint or HLT.
}

// *******************************************************************************************************************************
//												Load a binary file into RAM
// *******************************************************************************************************************************

void CPULoadBinary(char *fileName) {
	FILE *f = fopen(fileName,"rb");
	fread(ramMemory,RAMSIZE,1,f);
	fclose(f);
}

// *******************************************************************************************************************************
//												Gets a pointer to RAM memory
// *******************************************************************************************************************************
	
BYTE8 CPURead(WORD16 address) {
	return READ(address);
}

// *******************************************************************************************************************************
//											Retrieve a snapshot of the processor
// *******************************************************************************************************************************

static CPUSTATUS s;																	// Status area

CPUSTATUS *CPUGetStatus(void) {
	s.a = A;s.b = B;s.c = C;s.d = D;s.e = E;s.h = H;s.l = L;						// 8 bit registers
	s.zFlag = (pszValue == 0);s.cFlag = (Carry != 0);s.hFlag = (Halt != 0);			// Flags
	s.pFlag = (__parity(pszValue) == 0);s.sFlag = ((pszValue & 0x80) != 0);
	s.interruptEnabled = interruptEnabled;
	s.cycles = Cycles;																// Number of cycles.
	s.pc = PCTR;																	// Save PC.
	s.hl = (s.h << 8) | s.l;s.m = CPURead(s.hl & 0x3FFF);							// Helpers
	s.stackDepth = 8;																// Copy stack.
	for (int i = 0;i < 8;i++)
		s.stack[i] = PC[(PCP-i) & 7];
	return &s;
}
#endif
