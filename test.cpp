#include <stdio.h>
#include "asmx86.h"

using namespace x86;


int main()
{
	x86::Instruction instr;
	uint8* code = (uint8*)main;
	char str[512];
	while (true)
	{
		Disassemble64(code, (uint64)code, 15, &instr);
		FormatInstructionString(str, 512, "%a  %8b  %7i %o", code, (uint64)code, &instr);
		printf("%s\n", str);
		code += instr.length;
		if (instr.operation == x86::RETN)
			break;
	}
	return 0;
}
