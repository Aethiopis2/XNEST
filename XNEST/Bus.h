//=========================================================================================================|
// Project:
//	In typical Von Nuemann Architecture the components of a computer system are connected through the bus,
//	which is really a group of wires (in the physical sense), in this emulator the bus is also used to connect
//	components and exchange info albit of some software based modifications.
//
//	In the NES the bus is connected to an 8-bit CPU (6502), 2KB of RAM space
// 
// Inspired By:
//	One Lone Coder projects, courtesy of Javidx9.
//
// Program Author:
//	Aethiopis II ben Zahab
//
// Date Created:
//	14th of November 2022, Monday
//
// Last Update:
//	15th of Novemeber 2022, Tuesday
//
// Compiled On:
//	HP Pavallion (Areselaliyur) running on Intel Core I7 16GB RAM on Microsoft's Windows 11. 
//	Microsoft's Visual Studio 2022 Community IDE
//=========================================================================================================|
#ifndef BUS_H
#define BUS_H

//=========================================================================================================|
// INCLUDES
//=========================================================================================================|
#include <cstdint>
#include <memory.h>
#include "CPU6502.h"


//=========================================================================================================|
// DEFINES
//=========================================================================================================|
#define RAM_SIZE		65536



//=========================================================================================================|
// TYPES
//=========================================================================================================|
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;



//=========================================================================================================|
// CLASS DEFINTION
//=========================================================================================================|
class Bus
{
public:

	Bus();
	~Bus();
	
	void Write(u16 addr, u8 data);
	uint8_t Read(u16 addr, bool bread_only = false);

//private:

	CPU6502 cpu6502;			// 6502 8-bit CPU
	uint8_t ram[RAM_SIZE];		// I'm using plain old array's, suck it up C++, I like it in C style...
};


#endif
//=========================================================================================================|
//			THE END
//=========================================================================================================|