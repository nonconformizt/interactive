#include "header.h"

bool SDL_Start(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Initialization failed! \n";
        return false;
    }
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    *window = SDL_CreateWindow("Interactive",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH,
                               WINDOW_HEIGHT,
                               SDL_WINDOW_ALLOW_HIGHDPI);
    if (*window == nullptr) {
        cout << "Cannot create window\n";
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr) {
        cout << "Cannot create renderer\n";
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }
    SDL_RenderClear(*renderer);
    SDL_RenderPresent(*renderer);
    return true;
}

void SDL_Exit(SDL_Window * w, SDL_Renderer * r)
{
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
}

SDL_Texture *get_text_texture(SDL_Renderer * renderer, char * text, TTF_Font * font)
{
    SDL_Surface *textSurface = nullptr;

    SDL_Color fore_color = { 210, 210, 210};
    SDL_Color back_color = { 188, 155, 166, 1};

    textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}

SDL_Texture *get_ball_text_texture(SDL_Renderer * renderer, char * text, TTF_Font * font)
{
    SDL_Surface *textSurface = nullptr;

    SDL_Color fore_color = { 0, 0, 0, 0 };
    SDL_Color back_color = { 0, 0, 0, 1 };

    textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}

void init_balls(SDL_Rect balls[], int prices[], int count)
{
    srand(time(nullptr));

    for (int i = 0; i < count; i++) {
        balls[i] = {
                rand() % (WINDOW_WIDTH - 20),
                rand() % (WINDOW_HEIGHT - 20),
                50 + 10 * i,
                50 + 10 * i
        };
        prices[i] = rand() % 8 + 1;
    }
}

void draw_balls(SDL_Renderer* renderer, SDL_Rect balls[],
                int count, SDL_Texture* texture)
{
    for (int i = 0; i < count; i++)
    {
        if (balls[i].w == 0) continue;
        SDL_RenderCopy(renderer, texture, nullptr, &balls[i]);
    }
}

void draw_text(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_Rect rect = { 0,0, 70, 100};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void draw_ball_text(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect ball_rect)
{
    SDL_RenderCopy(renderer, texture, nullptr, &ball_rect);
}

bool is_ball_hit(SDL_Rect ball, int x, int y)
{
    if (ball.w == 0) return false;
    int centerX = ball.x + ball.w / 2;
    int centerY = ball.y + ball.h / 2;
    int radius = ball.w / 2;
    return sqrt((centerX - x)*(centerX - x) + (centerY - y)*(centerY - y)) < radius;
}
