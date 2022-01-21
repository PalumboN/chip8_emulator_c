#include <stdio.h>
#include "chip8/assembler.h"

int main(int argc, char **argv) {
	// Testing dependency
	chip8_program_ptr program;
	program = chip8_assembler_init();
	chip8_jump(program, 0x789);
	// Testing dependency

	printf("Hello world");
	return 0;
}
