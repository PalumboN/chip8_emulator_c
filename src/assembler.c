/*
 * assembler.c
 *
 *  Created on: Oct 15, 2021
 *      Author: guille
 */

#include "chip8/assembler.h"
#include <stdlib.h>

//Data access Functions

uint8_t* chip8_get_program_start(chip8_program_ptr program){
	return program->start;
}

uint8_t* chip8_get_program_next(chip8_program_ptr program){
	return program->next;
}

uint16_t chip8_get_program_size(chip8_program_ptr program){
	return program->size;
}

//Intitialization Functions

chip8_program_ptr chip8_assembler_init(){
	chip8_program_ptr program = (chip8_program_ptr) malloc(sizeof(chip8_program_str));
	size_t allocatedSize = 200;

	program->start = malloc(allocatedSize);
	program->next = program->start;
	program->size = allocatedSize;

	return program;
}

chip8_program_ptr chip8_jump(chip8_program_ptr program, uint16_t jump_target){
	program->next[0] = ((jump_target >> 8) & 0x0F) + 0x10;
	program->next[1] = jump_target & 0xFF;
	program->next += 2;
	return program;
}

chip8_program_ptr chip8_sprite(chip8_program_ptr program, uint8_t x_register_id, uint8_t y_register_id, uint8_t height){
	program->next[0] = 0xD0 + x_register_id;
	program->next[1] = (y_register_id << 4) + (height & 0xF);
	program->next += 2;
	return program;
}

chip8_program_ptr chip8_raw_data(chip8_program_ptr program, uint8_t data){
	program->next[0] = data;
	program->next += 1;
	return program;
}

void chip8_assembler_destroy(chip8_program_ptr p){
	free(p->start);
	free(p);
}
