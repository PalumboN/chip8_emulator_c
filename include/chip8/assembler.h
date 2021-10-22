#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct _chip8_program {
	uint8_t* start;
	uint8_t* next;
	size_t size;
} chip8_program_str;

typedef chip8_program_str* chip8_program;

uint8_t* chip8_get_program_start(chip8_program program);
uint16_t chip8_get_program_size(chip8_program program);
uint8_t* chip8_get_program_next(chip8_program program);

chip8_program chip8_assembler_init();
void chip8_assembler_destroy(chip8_program p);

chip8_program chip8_jump(chip8_program program, uint16_t jump_target);
chip8_program chip8_sprite(chip8_program program, uint8_t x_register_id, uint8_t y_register_id, uint8_t height);
chip8_program chip8_raw_data(chip8_program program, uint8_t data);
