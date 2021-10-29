#include <stdio.h>
#include "SDL.h"
#include "chip8/chip8.h"

#define PIXEL_SIZE 10

int r,g,b = 0;
int x , y = 10;
SDL_Window * window;

SDL_Renderer * initialize_graphics(){
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
			"SDL2Test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			64 * PIXEL_SIZE,
			32 * PIXEL_SIZE,
			0
	);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	return renderer;
}

void manage_events(){
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT){
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(0);
	}
}

void draw(SDL_Renderer *renderer){
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );

	// The graphical Memory is 64 cells wide and 32 high
	for(int x = 0; x < 64; x++){
		for(int y = 0; y < 32; y++){
			int pixel = chip8_graphical_memory[x][y];
			//If the pixel is on, we should draw it
			if (pixel > 0){
				SDL_Rect fillRect = { x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
				SDL_RenderFillRect( renderer, &fillRect );
			}
		}
	}

	SDL_RenderPresent( renderer );
}

int main(int argc, char **argv) {

	SDL_Renderer *renderer = initialize_graphics();
	chip8_init();
	chip8_set_register_value(0, 0);
	chip8_index = CHIP8_PROGRAM_START + 2;

	// sprite v0 v0 5
	uint8_t bytes[7] = { 0xD0, 0x05, 0x18, 0x24, 0x3C, 0x24, 0x24 };
	chip8_load(bytes, 7);

	chip8_step();

	while (1) {
		manage_events();
		draw(renderer);
	}

	return 0;
}
