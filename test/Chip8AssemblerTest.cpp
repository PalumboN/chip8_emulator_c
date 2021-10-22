#include "gtest/gtest.h"

extern "C" {
	#include "chip8/assembler.h"
}

TEST(Chip8Assembler, Initial) {
	chip8_program program;
	program = chip8_assembler_init();
	chip8_jump(program, 0x789);

	EXPECT_EQ(chip8_get_program_start(program)[0], 0x17);
	EXPECT_EQ(chip8_get_program_start(program)[1], 0x89);

	chip8_assembler_destroy(program);
}

TEST(Chip8Assembler, ChainJumps) {
	chip8_program program;
	program = chip8_assembler_init();
	chip8_jump(program, 0x789);
	chip8_jump(program, 0x654);

	EXPECT_EQ(chip8_get_program_start(program)[0], 0x17);
	EXPECT_EQ(chip8_get_program_start(program)[1], 0x89);
	EXPECT_EQ(chip8_get_program_start(program)[2], 0x16);
	EXPECT_EQ(chip8_get_program_start(program)[3], 0x54);

	chip8_assembler_destroy(program);
}

TEST(Chip8Assembler, RawData) {
	chip8_program program;
	program = chip8_assembler_init();
	chip8_raw_data(program, 0x66);
	chip8_raw_data(program, 0x77);

	ASSERT_EQ(chip8_get_program_start(program)[0], 0x66);
	ASSERT_EQ(chip8_get_program_start(program)[1], 0x77);

	chip8_assembler_destroy(program);
}

TEST(Chip8Assembler, Sprite) {
	chip8_program program;
	program = chip8_assembler_init();
	chip8_sprite(program, 0xA, 0x7, 0xF);


	ASSERT_EQ(chip8_get_program_start(program)[0], 0xDA);
	ASSERT_EQ(chip8_get_program_start(program)[1], 0x7F);

	chip8_assembler_destroy(program);
}

TEST(Chip8Assembler, SpriteAvancesStream) {
	chip8_program program;
	program = chip8_assembler_init();
	chip8_sprite(program, 0xA, 0x7, 0xF);

	ASSERT_GT(chip8_get_program_next(program), chip8_get_program_start(program));

	chip8_assembler_destroy(program);
}

TEST(Chip8Assembler, RawDataAvancesStream) {
	chip8_program program = chip8_assembler_init();
	chip8_raw_data(program, 0xA);

	ASSERT_GT(chip8_get_program_next(program), chip8_get_program_start(program));

	chip8_assembler_destroy(program);
}
