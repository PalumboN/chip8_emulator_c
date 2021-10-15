#include "gtest/gtest.h"

extern "C" {
	#include "chip8/chip8.h"
}

TEST(Chip8Interpreter, InitialRegisterState) {
	chip8_init();
	EXPECT_EQ(chip8_get_register_value_unsafe(0), 0);
}

TEST(Chip8Interpreter, AccessInvalidRegister) {
	chip8_init();
	// 255 is an invalid register. Register range [0,15]
	EXPECT_EQ(chip8_get_register_value_safe(255).status, 1);
}

TEST(Chip8Interpreter, ModifyRegisters) {
	chip8_init();
	chip8_set_register_value(0, 1);
	EXPECT_EQ(chip8_get_register_value_unsafe(0), 1);
}

TEST(Chip8Interpreter, InitialInstructionPointer) {
	chip8_init();
	EXPECT_EQ(chip8_instruction_pointer, 200);
}

TEST(Chip8Interpreter, StepAdvancesProgramCounter) {
	chip8_init();

	// Clear instruction
	uint8_t bytes[2] = { 0x00, 0xE0 };
	chip8_load(bytes, 2);

	int previousInstructionPointer = chip8_instruction_pointer;
	chip8_step();
	EXPECT_EQ(chip8_instruction_pointer, previousInstructionPointer + 2);
}

TEST(Chip8Interpreter, StepOnJumpMovesProgramCounter) {
	chip8_init();

	// Jump 789
	uint8_t bytes[2] = { 0x17, 0x89 };
	chip8_load(bytes, 2);

	chip8_step();
	EXPECT_EQ(chip8_instruction_pointer, 0x789);
}

TEST(Chip8Interpreter, StepOnJumpToZero) {
	chip8_init();

	// Jump 000
	uint8_t bytes[2] = { 0x10, 0x00 };
	chip8_load(bytes, 2);

	chip8_step();
	EXPECT_EQ(chip8_instruction_pointer, 0x000);
}

TEST(Chip8Interpreter, StepOnJumpToEnd) {
	chip8_init();

	// Jump 0xFFF
	uint8_t bytes[2] = { 0x1F, 0xFF };
	chip8_load(bytes, 2);

	chip8_step();
	EXPECT_EQ(chip8_instruction_pointer, 0xFFF);
}

TEST(Chip8Interpreter, StepOnRegisterAccumulator) {
	chip8_init();

	chip8_set_register_value(1, 17);
	chip8_set_register_value(2, 42);

	// V1 += V2
	uint8_t bytes[2] = { 0x81, 0x24 };
	chip8_load(bytes, 2);

	chip8_step();
	EXPECT_EQ(chip8_get_register_value_unsafe(1), 59);
}

TEST(Chip8Interpreter, StepOnRegisterAccumulatorWithOverflow) {
	chip8_init();

	chip8_set_register_value(1, 0xFF);
	chip8_set_register_value(2, 0x01);

	// V1 += V2
	uint8_t bytes[2] = { 0x81, 0x24 };
	chip8_load(bytes, 2);

	chip8_step();
	EXPECT_EQ(chip8_overflow_register, 1);
	EXPECT_EQ(chip8_get_register_value_unsafe(1), 0);
}

TEST(Chip8Interpreter, StepOnRegisterAccumulatorAdvancesInstructionPointer) {
	chip8_init();

	chip8_set_register_value(1, 0xFF);
	chip8_set_register_value(2, 0x01);

	// V1 += V2
	uint8_t bytes[2] = { 0x81, 0x24 };
	chip8_load(bytes, 2);

	int previousInstructionPointer = chip8_instruction_pointer;
	chip8_step();
	EXPECT_EQ(chip8_instruction_pointer, previousInstructionPointer + 2);
}