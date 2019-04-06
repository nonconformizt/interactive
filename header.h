/* Libraries */
#include <iostream>
#include <cmath>
#include <time.h>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>


#undef main

using namespace std;

#define WINDOW_WIDTH (960)
#define WINDOW_HEIGHT (720)

#define START_X int(WINDOW_WIDTH / 2)
#define START_Y int(WINDOW_HEIGHT / 2)

#define BALL_COUNT 5

bool SDL_Start(SDL_Window ** window, SDL_Renderer ** renderer);
void SDL_Exit(SDL_Window * w, SDL_Renderer * r);
SDL_Texture *get_text_texture(SDL_Renderer *renderer, char *text, TTF_Font *font);
SDL_Texture *get_ball_text_texture(SDL_Renderer * renderer, char * text, TTF_Font * font);
void init_balls(SDL_Rect balls[], int prices[], int count);
void draw_text(SDL_Renderer* renderer, SDL_Texture* texture);
void draw_balls(SDL_Renderer* renderer, SDL_Rect balls[], int count, SDL_Texture* texture);
bool is_ball_hit(SDL_Rect ball, int x, int y);
