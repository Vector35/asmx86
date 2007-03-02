// Copyright (c) 2006, Rusty Wagner
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that
// the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, this list of conditions and the
//      following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
//      the following disclaimer in the documentation and/or other materials provided with the distribution.
//    * Neither the name of the author nor the names of its contributors may be used to endorse or promote
//      products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef __ASMX86_H__
#define __ASMX86_H__

#ifndef _MSC_VER
	#ifndef __cplusplus
		#include <stdbool.h>
	#endif
	#include <sys/types.h>
#else
	#ifndef __cplusplus
		typedef unsigned char bool;
		#define true 1
		#define false 0
	#endif
	typedef ptrdiff_t ssize_t;
#endif

#ifndef WIN32
#include <unistd.h>
#endif

#undef IN
#undef OUT


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;


#define X86_FLAG_LOCK		1
#define X86_FLAG_REP		2
#define X86_FLAG_REPNE		4
#define X86_FLAG_REPE		8
#define X86_FLAG_OPSIZE		16
#define X86_FLAG_ADDRSIZE	32

#define X86_FLAG_ANY_REP	(X86_FLAG_REP | X86_FLAG_REPE | X86_FLAG_REPNE)


#ifdef __cplusplus
namespace x86
{
#endif
	enum InstructionOperation
	{
		// Independent operations
		INVALID = 0, AAA, AAD, AAM, AAS, ADD, ADC, AND, ARPL, BOUND, BSF, BSR, BSWAP, BT, BTC, BTR, BTS,
		CALLF, CALLN, CLC, CLD, CLI,
		CLTS, CMC, CMP, CMPXCH16B, CMPXCH8B, CMPXCHG, CPUID, DAA, DAS, DEC, DIV, ENTER,
		F2XM1, FABS, FADD, FADDP, FBLD, FBSTP, FCHS, FCLEX,
		FCMOVB, FCMOVBE, FCMOVE, FCMOVNB, FCMOVNBE, FCMOVNE, FCMOVNU, FCMOVU,
		FCOM, FCOMI, FCOMIP, FCOMP, FCOMPP, FCOS,
		FDECSTP, FDISI, FDIV, FDIVP, FDIVR, FDIVRP, FEMMS, FENI, FFREE, FFREEP, FIADD, FICOM, FICOMP, FIDIV, FIDIVR, FILD,
		FIMUL, FINCSTP, FINIT, FIST, FISTP, FISTTP, FISUB, FISUBR,
		FLD, FLD1, FLDCW, FLDENV, FLDL2E, FLDL2T, FLDLG2, FLDLN2, FLDPI, FLDZ,
		FMUL, FMULP, FNOP, FPATAN, FPREM, FPREM1, FPTAN, FRICHOP, FRINEAR, FRINT2, FRNDINT, FRSTOR, FRSTPM,
		FSAVE, FSCALE, FSETPM, FSIN, FSINCOS, FSQRT,
		FST, FSTCW, FSTDW, FSTENV, FSTP, FSTSG, FSTSW, FSUB, FSUBP, FSUBR, FSUBRP,
		FTST, FUCOM, FUCOMI, FUCOMIP, FUCOMP, FUCOMPP, FWAIT, FXAM, FXCH, FXTRACT, FYL2X, FYL2XP1,
		HLT, IDIV, IMUL, IN, INC, INT, INT1, INT3, INTO, INVD, INVLPG, IRET, JMPF, JMPN,
		LAHF, LAR, LDS, LEA, LEAVE, LES, LFS, LGDT, LGS, LIDT, LLDT, LMSW,
		LOOP, LOOPE, LOOPNE, LSL, LSS, LTR, MMXNOP, MOV, MOVDDUP, MOVHLPS,
		MOVLHPS, MOVSHDUP, MOVSLDUP, MOVSS, MOVSX, MOVUPD, MOVUPS, MOVZX,
		MUL, NEG, NOP, NOT,
		OR, OUT, PAUSE, PAVGUSB, PF2ID, PF2IW, PFACC, PFADD, PFCMPEQ, PFCMPGE, PFCMPGT, PFMAX, PFMIN,
		PFMUL, PFNACC, PFPNACC, PFRCP, PFRCPIT1, PFRCPIT2, PFRCPV, PFRSQIT1, PFRSQRT, PFRSQRTV, PFSUB,
		PFSUBR, PI2FD, PI2FW, PMULHRW, PSWAPD,
		POP, PREFETCH, PREFETCHNTA, PREFETCHT0, PREFETCHT1, PREFETCHT2, PREFETCHW,
		PUSH, RETF, RETN, RCL, RCR, ROL, ROR, SAHF, SALC, SAR, SBB, SGDT, SHL, SHLD, SHR, SHRD,
		SIDT, SLDT, SMSW, STR, SUB,
		STC, STD, STI, TEST, UD2,
		VERR, VERW, WBINVD, XCHG, XLAT, XADD, XOR,

		// Grouped operations (ordering within each line is critical)
		CBW, CWDE, CDQE,
		CMPSB, CMPSW, CMPSD, CMPSQ,
		CWD, CDQ, CQO,
		INSB, INSW, INSD, INSQ,
		JCXZ, JECXZ, JRCXZ,
		JO, JNO, JB, JAE, JE, JNE, JBE, JA, JS, JNS, JPE, JPO, JL, JGE, JLE, JG,
		LODSB, LODSW, LODSD, LODSQ,
		MOVHPS, MOVHPD,
		MOVLPS, MOVLPD,
		MOVSB, MOVSW, MOVSD, MOVSQ,
		OUTSB, OUTSW, OUTSD, OUTSQ,
		POPA, POPAD,
		POPF, POPFD, POPFQ,
		PUSHA, PUSHAD,
		PUSHF, PUSHFD, PUSHFQ,
		SCASB, SCASW, SCASD, SCASQ,
		SETO, SETNO, SETB, SETAE, SETE, SETNE, SETBE, SETA, SETS, SETNS, SETPE, SETPO, SETL, SETGE, SETLE, SETG,
		STOSB, STOSW, STOSD, STOSQ,
		UNPCKHPS, UNPCKHPD,
		UNPCKLPS, UNPCKLPD,
	};
#ifndef __cplusplus
	typedef enum InstructionOperation InstructionOperation;
#endif


	enum SegmentRegister
	{
		SEG_ES = 0, SEG_CS = 1, SEG_SS = 2, SEG_DS = 3, SEG_FS = 4, SEG_GS = 5,
		SEG_DEFAULT = 7
	};
#ifndef __cplusplus
	typedef enum SegmentRegister SegmentRegister;
#endif


	enum OperandType
	{
		NONE = 0, IMM, MEM,
		REG_AL, REG_CL, REG_DL, REG_BL, REG_AH, REG_CH, REG_DH, REG_BH,
		REG_SPL, REG_BPL, REG_SIL, REG_DIL,
		REG_R8B, REG_R9B, REG_R10B, REG_R11B, REG_R12B, REG_R13B, REG_R14B, REG_R15B,
		REG_AX, REG_CX, REG_DX, REG_BX, REG_SP, REG_BP, REG_SI, REG_DI,
		REG_R8W, REG_R9W, REG_R10W, REG_R11W, REG_R12W, REG_R13W, REG_R14W, REG_R15W,
		REG_EAX, REG_ECX, REG_EDX, REG_EBX, REG_ESP, REG_EBP, REG_ESI, REG_EDI,
		REG_R8D, REG_R9D, REG_R10D, REG_R11D, REG_R12D, REG_R13D, REG_R14D, REG_R15D,
		REG_RAX, REG_RCX, REG_RDX, REG_RBX, REG_RSP, REG_RBP, REG_RSI, REG_RDI,
		REG_R8, REG_R9, REG_R10, REG_R11, REG_R12, REG_R13, REG_R14, REG_R15,
		REG_ST0, REG_ST1, REG_ST2, REG_ST3, REG_ST4, REG_ST5, REG_ST6, REG_ST7,
		REG_MM0, REG_MM1, REG_MM2, REG_MM3, REG_MM4, REG_MM5, REG_MM6, REG_MM7,
		REG_XMM0, REG_XMM1, REG_XMM2, REG_XMM3, REG_XMM4, REG_XMM5, REG_XMM6, REG_XMM7,
		REG_XMM8, REG_XMM9, REG_XMM10, REG_XMM11, REG_XMM12, REG_XMM13, REG_XMM14, REG_XMM15,
		REG_CR0, REG_CR1, REG_CR2, REG_CR3, REG_CR4, REG_CR5, REG_CR6, REG_CR7,
		REG_CR8, REG_CR9, REG_CR10, REG_CR11, REG_CR12, REG_CR13, REG_CR14, REG_CR15,
		REG_DR0, REG_DR1, REG_DR2, REG_DR3, REG_DR4, REG_DR5, REG_DR6, REG_DR7,
		REG_DR8, REG_DR9, REG_DR10, REG_DR11, REG_DR12, REG_DR13, REG_DR14, REG_DR15,
		REG_TR0, REG_TR1, REG_TR2, REG_TR3, REG_TR4, REG_TR5, REG_TR6, REG_TR7,
		REG_TR8, REG_TR9, REG_TR10, REG_TR11, REG_TR12, REG_TR13, REG_TR14, REG_TR15,
		REG_ES, REG_CS, REG_SS, REG_DS, REG_FS, REG_GS
	};
#ifndef __cplusplus
	typedef enum OperandType OperandType;
#endif


	struct InstructionOperand
	{
		OperandType operand;
		OperandType components[2];
		uint8 scale;
		uint8 size;
		int64 immediate;
		SegmentRegister segment;
	};
#ifndef __cplusplus
	typedef struct InstructionOperand InstructionOperand;
#endif


	struct Instruction
	{
		InstructionOperation operation;
		InstructionOperand operands[3];
		uint32 flags;
		SegmentRegister segment;
		size_t length;
	};
#ifndef __cplusplus
	typedef struct Instruction Instruction;
#endif


#ifdef __cplusplus
	extern "C"
	{
#endif
		bool Disassemble16(const uint8* opcode, uint64 addr, size_t maxLen, Instruction* result);
		bool Disassemble32(const uint8* opcode, uint64 addr, size_t maxLen, Instruction* result);
		bool Disassemble64(const uint8* opcode, uint64 addr, size_t maxLen, Instruction* result);

		size_t FormatInstructionString(char* out, size_t outMaxLen, const char* fmt, const uint8* opcode,
			uint64 addr, const Instruction* instr);

		size_t DisassembleToString16(char* out, size_t outMaxLen, const char* fmt, const uint8* opcode,
			uint64 addr, size_t maxLen, Instruction* instr);
		size_t DisassembleToString32(char* out, size_t outMaxLen, const char* fmt, const uint8* opcode,
			uint64 addr, size_t maxLen, Instruction* instr);
		size_t DisassembleToString64(char* out, size_t outMaxLen, const char* fmt, const uint8* opcode,
			uint64 addr, size_t maxLen, Instruction* instr);
#ifdef __cplusplus
	}
}
#endif


#define __CODEGENX86_32BIT
#include "codegenx86.h"
#undef __CODEGENX86_32BIT

#define __CODEGENX86_64BIT
#include "codegenx86.h"
#undef __CODEGENX86_64BIT


#endif

