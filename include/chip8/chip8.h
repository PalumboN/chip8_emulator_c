#ifndef __CHIP8__
#define __CHIP8__

#include <stdint.h>
#include <stddef.h>

struct register_read_status{
	uint8_t status;
	uint8_t value;
};

extern int chip8_instruction_pointer;
extern int chip8_overflow_register;
extern int chip8_index;
extern uint8_t chip8_graphical_memory[32][64];

// Initialize the emulator
void chip8_init();

// Load a program in the emulator
// We should define what happens if the size does not match the byte array
void chip8_load(const uint8_t* program, size_t size);

// Execute one instruction
void chip8_step();

// Access the register values
void chip8_set_register_value(uint8_t register_id, uint8_t value);
uint8_t chip8_get_register_value_unsafe(uint8_t register_id);

// Access the value of a register
// Returns a structure with an exit status (0 success, 1 error)
// If it is a success, the field value contains the read value
// If it is an error, the field value has an undefined value
struct register_read_status chip8_get_register_value_safe(uint8_t register_id);

// Version with out parameter
// The user sends as second argument a pointer to a value holder big enough for a uint8_t
// Return 0 if success, 1 if error
uint8_t chip8_get_register_value_safe2(uint8_t register_id, uint8_t *value);

#endif
