#pragma once

#include <stdint.h>
#include <stddef.h>

struct chip8_program {
	uint8_t* start;
	uint8_t* next;
	size_t size;
};

struct chip8_program chip8_assembler_init();
void chip8_assembler_destroy(struct chip8_program p);
struct chip8_program chip8_jump(struct chip8_program program, uint16_t jump_target);
