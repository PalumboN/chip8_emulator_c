/*
 * chip8.c
 *
 *  Created on: Oct 7, 2021
 *      Author: guille
 */

#include "chip8/chip8.h"
#include <string.h>

int chip8_instruction_pointer;
int chip8_overflow_register;
uint8_t memory[4096];
uint8_t chip8_registers[16];


void chip8_init(){
	chip8_instruction_pointer = 200;
}

void chip8_load(const uint8_t* program, size_t size){
	memcpy(&memory[200], program, size);
}

uint8_t chip8_get_register_value_unsafe(uint8_t register_id) {
	return chip8_get_register_value_safe(register_id).value;
}

struct register_read_status chip8_get_register_value_safe(uint8_t register_id){
	struct register_read_status status;
	if (register_id > 15) {
		status.status = 1; //Error
	} else {
		status.value = chip8_registers[register_id];
		status.status = 0; //Success
	}
	return status;
}

uint8_t chip8_get_register_value_safe2(uint8_t register_id, uint8_t *value_holder){
	struct register_read_status status;
	if (register_id > 15) {
		//Error
		return 1;
	}
	*value_holder = chip8_registers[register_id];
	return 0;
}

void chip8_set_register_value(uint8_t register_id, uint8_t value) {
	chip8_registers[register_id] = value;
}

void chip8_step(){
	uint8_t higher = memory[chip8_instruction_pointer];
	uint8_t lower = memory[chip8_instruction_pointer + 1];
	uint16_t currentInstruction = (higher << 8) + lower;

	//If this is a JUMP
	if ((currentInstruction & 0xF000) == 0x1000){
		chip8_instruction_pointer = currentInstruction & 0x0FFF;
	} else if ((currentInstruction & 0xF000) == 0x8000) {
		// VX += VY
		uint8_t left_register_id = (currentInstruction & 0x0F00) >> 8;
		uint8_t right_register_id = (currentInstruction & 0x00F0) >> 4;
		uint8_t left_value = chip8_get_register_value_unsafe(left_register_id);
		uint8_t right_value = chip8_get_register_value_unsafe(right_register_id);

		uint16_t result = left_value + right_value;
		chip8_overflow_register = (result & 0xFF00) > 0 ? 1 : 0;

		chip8_set_register_value(left_register_id, result & 0xFF);
		chip8_instruction_pointer += 2;
	} else{
		chip8_instruction_pointer += 2;
	}
}
