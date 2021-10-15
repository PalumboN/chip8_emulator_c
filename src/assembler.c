/*
 * assembler.c
 *
 *  Created on: Oct 15, 2021
 *      Author: guille
 */

#include "chip8/assembler.h"

struct chip8_program chip8_assembler_init(){
	struct chip8_program program;
	size_t allocatedSize = 200;

	program.start = malloc(allocatedSize);
	program.next = program.start;
	program.size = allocatedSize;

	return program;
}

struct chip8_program chip8_jump(struct chip8_program program, uint16_t jump_target){
	program.next[0] = ((jump_target >> 8) & 0x0F) + 0x10;
	program.next[1] = jump_target & 0xFF;
	program.next += 2;
	return program;
}

void chip8_assembler_destroy(struct chip8_program p){
	free(p.start);
}
