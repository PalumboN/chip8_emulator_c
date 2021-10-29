#include <stdio.h>
#include "SDL.h"

int main(int argc, char **argv) {

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(
			"SDL2Test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640,
			480,
			0
	);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	int r,g,b = 0;
	int x , y =10;
	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT){
			SDL_DestroyWindow(window);
			SDL_Quit();
			return 0;
		}

		r += 50;
		g += 70;
		b += 20;

		x += 1;
		y += 2;

		x %=200;
		y %=200;

		SDL_Rect fillRect = { x, y, x + 10, y + 10 };

		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(renderer);

		//Redraw
		SDL_SetRenderDrawColor( renderer, r, g, b, 0xFF );
		SDL_RenderFillRect( renderer, &fillRect );
		SDL_RenderPresent( renderer );

	}

	return 0;
}
