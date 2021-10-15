#include "gtest/gtest.h"

extern "C" {
	#include "chip8/assembler.h"
}

TEST(Chip8Assembler, Initial) {
	struct chip8_program program;
	program = chip8_assembler_init();
	program = chip8_jump(program, 0x789);

	EXPECT_EQ(program.start[0], 0x17);
	EXPECT_EQ(program.start[1], 0x89);

	chip8_assembler_destroy(program);
}

TEST(Chip8Assembler, ChainJumps) {
	struct chip8_program program;
	program = chip8_assembler_init();
	program = chip8_jump(program, 0x789);
	program = chip8_jump(program, 0x654);

	EXPECT_EQ(program.start[0], 0x17);
	EXPECT_EQ(program.start[1], 0x89);
	EXPECT_EQ(program.start[2], 0x16);
	EXPECT_EQ(program.start[3], 0x54);

	chip8_assembler_destroy(program);
}
