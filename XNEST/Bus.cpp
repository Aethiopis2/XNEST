//=========================================================================================================|
// Bus.cpp:
//	Defintion for Bus class that emulates NES bus.
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


//=========================================================================================================|
// INCLUDES
//=========================================================================================================|
#include "Bus.h"


//=========================================================================================================|
// DEFINES
//=========================================================================================================|



//=========================================================================================================|
// CLASS DEFINTION
//=========================================================================================================|
/**
 * Clear's the RAM (main memory); this is a software emulation baby!
 */
Bus::Bus()
{
	memset(ram, 0, RAM_SIZE);
	cpu6502.Connect_Bus(this);
} // end Consturctor


//=========================================================================================================|
/**
 * Destructor
 */
Bus::~Bus()
{

} // end Destructor


//=========================================================================================================|
/**
 * Writes an 8-bit value on the address provided
 */
void Bus::Write(u16 addr, u8 data)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		ram[addr] = data;
} // end Write


//=========================================================================================================|
/**
 * Read's the 8-bit value stored at the 16-bit address.
 */
u8 Bus::Read(u16 addr, bool bread_only)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		return ram[addr];
	return 0;
} // end Read


//=========================================================================================================|
//			THE END
//=========================================================================================================|