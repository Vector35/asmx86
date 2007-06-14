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

#define X86_FLAG_INSUFFICIENT_LENGTH	0x80000000

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
		PUSH, RDMSR, RDPMC, RDTSC, RETF, RETN, RCL, RCR, ROL, ROR, SAHF, SALC, SAR, SBB, SGDT, SHL, SHLD, SHR, SHRD,
		SIDT, SLDT, SMSW, STR, SUB,
		STC, STD, STI, SYSENTER, SYSEXIT, TEST, UD2,
		VERR, VERW, WBINVD, WRMSR, XCHG, XLAT, XADD, XOR,

		// Grouped operations (ordering within each line is critical)
		CBW, CWDE, CDQE,
		CMPSB, CMPSW, CMPSD, CMPSQ,
		CMOVO, CMOVNO, CMOVB, CMOVAE, CMOVE, CMOVNE, CMOVBE, CMOVA, CMOVS, CMOVNS, CMOVPE, CMOVPO, CMOVL, CMOVGE, CMOVLE, CMOVG,
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


#ifdef X86_ALT_OPERAND_NAMES
#define __X86_OPER(n) X86_ ## n
#else
#define __X86_OPER(n) n
#endif

	enum OperandType
	{
		NONE = 0, IMM, MEM,
		__X86_OPER(REG_AL), __X86_OPER(REG_CL), __X86_OPER(REG_DL), __X86_OPER(REG_BL), __X86_OPER(REG_AH), __X86_OPER(REG_CH), __X86_OPER(REG_DH), __X86_OPER(REG_BH),
		__X86_OPER(REG_SPL), __X86_OPER(REG_BPL), __X86_OPER(REG_SIL), __X86_OPER(REG_DIL),
		__X86_OPER(REG_R8B), __X86_OPER(REG_R9B), __X86_OPER(REG_R10B), __X86_OPER(REG_R11B), __X86_OPER(REG_R12B), __X86_OPER(REG_R13B), __X86_OPER(REG_R14B), __X86_OPER(REG_R15B),
		__X86_OPER(REG_AX), __X86_OPER(REG_CX), __X86_OPER(REG_DX), __X86_OPER(REG_BX), __X86_OPER(REG_SP), __X86_OPER(REG_BP), __X86_OPER(REG_SI), __X86_OPER(REG_DI),
		__X86_OPER(REG_R8W), __X86_OPER(REG_R9W), __X86_OPER(REG_R10W), __X86_OPER(REG_R11W), __X86_OPER(REG_R12W), __X86_OPER(REG_R13W), __X86_OPER(REG_R14W), __X86_OPER(REG_R15W),
		__X86_OPER(REG_EAX), __X86_OPER(REG_ECX), __X86_OPER(REG_EDX), __X86_OPER(REG_EBX), __X86_OPER(REG_ESP), __X86_OPER(REG_EBP), __X86_OPER(REG_ESI), __X86_OPER(REG_EDI),
		__X86_OPER(REG_R8D), __X86_OPER(REG_R9D), __X86_OPER(REG_R10D), __X86_OPER(REG_R11D), __X86_OPER(REG_R12D), __X86_OPER(REG_R13D), __X86_OPER(REG_R14D), __X86_OPER(REG_R15D),
		__X86_OPER(REG_RAX), __X86_OPER(REG_RCX), __X86_OPER(REG_RDX), __X86_OPER(REG_RBX), __X86_OPER(REG_RSP), __X86_OPER(REG_RBP), __X86_OPER(REG_RSI), __X86_OPER(REG_RDI),
		__X86_OPER(REG_R8), __X86_OPER(REG_R9), __X86_OPER(REG_R10), __X86_OPER(REG_R11), __X86_OPER(REG_R12), __X86_OPER(REG_R13), __X86_OPER(REG_R14), __X86_OPER(REG_R15),
		__X86_OPER(REG_ST0), __X86_OPER(REG_ST1), __X86_OPER(REG_ST2), __X86_OPER(REG_ST3), __X86_OPER(REG_ST4), __X86_OPER(REG_ST5), __X86_OPER(REG_ST6), __X86_OPER(REG_ST7),
		__X86_OPER(REG_MM0), __X86_OPER(REG_MM1), __X86_OPER(REG_MM2), __X86_OPER(REG_MM3), __X86_OPER(REG_MM4), __X86_OPER(REG_MM5), __X86_OPER(REG_MM6), __X86_OPER(REG_MM7),
		__X86_OPER(REG_XMM0), __X86_OPER(REG_XMM1), __X86_OPER(REG_XMM2), __X86_OPER(REG_XMM3), __X86_OPER(REG_XMM4), __X86_OPER(REG_XMM5), __X86_OPER(REG_XMM6), __X86_OPER(REG_XMM7),
		__X86_OPER(REG_XMM8), __X86_OPER(REG_XMM9), __X86_OPER(REG_XMM10), __X86_OPER(REG_XMM11), __X86_OPER(REG_XMM12), __X86_OPER(REG_XMM13), __X86_OPER(REG_XMM14), __X86_OPER(REG_XMM15),
		__X86_OPER(REG_CR0), __X86_OPER(REG_CR1), __X86_OPER(REG_CR2), __X86_OPER(REG_CR3), __X86_OPER(REG_CR4), __X86_OPER(REG_CR5), __X86_OPER(REG_CR6), __X86_OPER(REG_CR7),
		__X86_OPER(REG_CR8), __X86_OPER(REG_CR9), __X86_OPER(REG_CR10), __X86_OPER(REG_CR11), __X86_OPER(REG_CR12), __X86_OPER(REG_CR13), __X86_OPER(REG_CR14), __X86_OPER(REG_CR15),
		__X86_OPER(REG_DR0), __X86_OPER(REG_DR1), __X86_OPER(REG_DR2), __X86_OPER(REG_DR3), __X86_OPER(REG_DR4), __X86_OPER(REG_DR5), __X86_OPER(REG_DR6), __X86_OPER(REG_DR7),
		__X86_OPER(REG_DR8), __X86_OPER(REG_DR9), __X86_OPER(REG_DR10), __X86_OPER(REG_DR11), __X86_OPER(REG_DR12), __X86_OPER(REG_DR13), __X86_OPER(REG_DR14), __X86_OPER(REG_DR15),
		__X86_OPER(REG_TR0), __X86_OPER(REG_TR1), __X86_OPER(REG_TR2), __X86_OPER(REG_TR3), __X86_OPER(REG_TR4), __X86_OPER(REG_TR5), __X86_OPER(REG_TR6), __X86_OPER(REG_TR7),
		__X86_OPER(REG_TR8), __X86_OPER(REG_TR9), __X86_OPER(REG_TR10), __X86_OPER(REG_TR11), __X86_OPER(REG_TR12), __X86_OPER(REG_TR13), __X86_OPER(REG_TR14), __X86_OPER(REG_TR15),
		__X86_OPER(REG_ES), __X86_OPER(REG_CS), __X86_OPER(REG_SS), __X86_OPER(REG_DS), __X86_OPER(REG_FS), __X86_OPER(REG_GS)
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


#ifndef X86_ALT_OPERAND_NAMES // Code generator does not support altername naming

#define __CODEGENX86_32BIT
#include "codegenx86.h"
#undef __CODEGENX86_32BIT

#define __CODEGENX86_64BIT
#include "codegenx86.h"
#undef __CODEGENX86_64BIT

#endif


#endif

