//=========================================================================================================|
// CPU6502.h
//	The NES CPU core is based on the 6502 processor and runs at approximately 1.79 MHz (1.66 MHz in a PAL NES).
//		It was an 8-bit processor that was degined by Ricoh and lacks MOS6502 Decimal flag. It had 12 addressing
//		modes with 56 documented (legal opcodes). 
// 
//  The programming model is easy to work with as there are only limited number of register sets and sizes:
//		A : accumulator register (8-bits)
//		X : Index register (8-bits)
//		Y : Index Y register (8-bits)
//		sp: stack pointer (8-bits)
//		pc: program counter/Instruction pointer (16-bits)
//
//  The aim is plain and simple, the little CPU does the following steps in a loop (at the tick of every
//	clock cycle according to the specs for 6502 machine instruction cycles):
//		1. Read the program counter for the next instruction
//		2. Decode the addressing mode
//		3. Fetch data for the decoded address (if required)
//		4. Execute the instruction
//		5. Reduce the clock count
// 
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
//	23rd of Novemeber 2022, Wednesday
//
// Compiled On:
//	HP Pavallion (Areselaliyur) running on Intel Core I7 16GB RAM on Microsoft's Windows 11. 
//	Microsoft's Visual Studio 2022 Community IDE
//=========================================================================================================|
#ifndef CPU6502_H
#define CPU6502_H


//=========================================================================================================|
// INCLUDES
//=========================================================================================================|
#include <cstdint>
#include <string>
#include <vector>


//=========================================================================================================|
// TYPES
//=========================================================================================================|
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;



//=========================================================================================================|
// GLOBALS
//=========================================================================================================|
// the 8-bit flags/status register
#define C (1 << 0)		// carry
#define Z (1 << 1)		// zero
#define I (1 << 2)		// Interrupt
#define D (1 << 3)		// Decimal (NES console does not actually use this feature)
#define B (1 << 4)		// break
#define U (1 << 5)		// undefined
#define V (1 << 6)		// overflow
#define N (1 << 7)		// Negative

// helper macros
#define SET_FLAG(r8, f, b)	(b ? r8 |= f : r8 &= ~f)
#define GET_FLAG(r8, f)		((r8 & f) > 0) ? 1 : 0



// forward declare the bus
class Bus;


//=========================================================================================================|
// CLASS DEFINTION
//=========================================================================================================|
class CPU6502
{
public:

	CPU6502();
	~CPU6502();

	void Connect_Bus(Bus* pn);


	// 6502 signals
	void Clock();
	void Reset();
	void IRQ();
	void NMI();

private:

	Bus* pbus;

	// 6502 registers
	u8 a;			// the Accumulator
	u8 x;			// the (x) indeX register
	u8 y;			// y index register
	u8 sp;			// the stack pointer
	u16 pc;			// the program counter/instruction pointer
	u8 status;		// 8-bit status registers


	void Write(u16 addr, u8 data);
	uint8_t Read(u16 addr);


	// the 12 addressing modes for a 6502 CPU
	u8 IMP(); u8 IMM(); u8 ZP0(); u8 ZPX();
	u8 ZPY(); u8 REL(); u8 ABS(); u8 ABX();
	u8 ABY(); u8 IND(); u8 IZX(); u8 IZY();

	// the 56 legal opcodes (the documented ones)
	u8 ADC();	u8 AND();	u8 ASL();	u8 BCC();
	u8 BCS();	u8 BEQ();	u8 BIT();	u8 BMI();
	u8 BNE();	u8 BPL();	u8 BRK();	u8 BVC();
	u8 BVS();	u8 CLC();	u8 CLD();	u8 CLI();
	u8 CLV();	u8 CMP();	u8 CPX();	u8 CPY();
	u8 DEC();	u8 DEX();	u8 DEY();	u8 EOR();
	u8 INC();	u8 INX();	u8 INY();	u8 JMP();
	u8 JSR();	u8 LDA();	u8 LDX();	u8 LDY();
	u8 LSR();	u8 NOP();	u8 ORA();	u8 PHA();
	u8 PHP();	u8 PLA();	u8 PLP();	u8 ROL();
	u8 ROR();	u8 RTI();	u8 RTS();	u8 SBC();
	u8 SEC();	u8 SED();	u8 SEI();	u8 STA();
	u8 STX();	u8 STY();	u8 TAX();	u8 TAY();
	u8 TSX();	u8 TXA();	u8 TXS();	u8 TYA();

	// I capture all "unofficial" opcodes with this function. It is
	// functionally identical to a NOP
	u8 UNK();

	// utilities
	inline u8 Fetch();
	u8 fetched;

	u16 addr_abs;
	u16 addr_rel;
	u8 opcode;
	u8 cycles;

	// a lookup table
	struct INSTRUCTION
	{
		std::string name;		// opcode name
		u8(CPU6502::* Operate)(void) = nullptr;
		u8(CPU6502::* Addrmode)(void) = nullptr;
		u8 cycles{ 0 };
	};

	std::vector<INSTRUCTION> lookup;
};


#endif
//=========================================================================================================|
//			THE END
//=========================================================================================================|

