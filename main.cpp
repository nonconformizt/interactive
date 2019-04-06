#include "header.h"


int main(int argc, char **argv) {
    SDL_Window *win;
    SDL_Renderer *rend;

    SDL_Start(&win, &rend);

    TTF_Init();
    TTF_Font *my_font = TTF_OpenFont("font.ttf", 100);
    SDL_Texture *text;

    int k = 0;
    char text_val[10];
    _itoa(k, text_val, 10);
    text = get_text_texture(rend, text_val, my_font);

    SDL_Rect balls[BALL_COUNT];
    int prices[BALL_COUNT];
    SDL_Texture * ball_text[BALL_COUNT];
    init_balls(balls, prices, BALL_COUNT);

    SDL_Surface *ballImage = IMG_Load("ball.png");
    SDL_Texture * ball = SDL_CreateTextureFromSurface(rend, ballImage);
    SDL_FreeSurface(ballImage);

    ballImage = IMG_Load("active.png");
    SDL_Texture * active = SDL_CreateTextureFromSurface(rend, ballImage);
    SDL_FreeSurface(ballImage);


    SDL_Event e;
    bool close = false,
        is_down = false,
        is_up = false,
        is_right = false,
        is_left = false;
    int activated_ball = BALL_COUNT; // if == BALL_COUNT, than inactive

    auto begin = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    int dur_ms = (int) chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    while (!close) {
        begin = chrono::high_resolution_clock::now();

        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                close = true;
            // если есть активный мячик
            else if (activated_ball != BALL_COUNT)
            {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
                    is_down = true;
                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
                    is_up = true;
                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
                    is_right = true;
                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
                    is_left = true;
                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_DOWN)
                    is_down = false;
                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_UP)
                    is_up = false;
                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RIGHT)
                    is_right = false;
                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_LEFT)
                    is_left = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                for (int i = 0; i < BALL_COUNT; i++)
                    // если нажали на мячик, то сделать его активным
                    if (is_mouse_hit(balls[i], e.button.x, e.button.y))
                        activated_ball = i;

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderClear(rend);

        if (is_down)
            balls[activated_ball].y += STEP;
        if (is_up)
            balls[activated_ball].y -= STEP;
        if (is_right)
            balls[activated_ball].x += STEP;
        if (is_left)
            balls[activated_ball].x -= STEP;

        if (activated_ball != BALL_COUNT) {
            for (int i = 0; i < BALL_COUNT; i++)
                if (i == activated_ball)
                    continue;
                else if (is_balls_hit(balls[i], balls[activated_ball])) {
                    balls[i].w = balls[i].h = 0;
                    k += prices[i];
                    _itoa(k, text_val, 10);
                    SDL_DestroyTexture(text);
                    text = get_text_texture(rend, text_val, my_font);
                }
        }

        draw_balls(rend, balls, BALL_COUNT, ball);
        for (int j = 0; j < BALL_COUNT; j++) {
            if(j == activated_ball)
                continue;
            _itoa(prices[j], text_val, 10);
            ball_text[j] = get_ball_text_texture(rend, text_val, my_font);
            draw_ball_text(rend, ball_text[j], balls[j]);
        }
        draw_text(rend, text);

        // draw activated
        if (activated_ball != BALL_COUNT) {
            SDL_RenderCopy(rend, active, nullptr, &balls[activated_ball]);
        }

            SDL_RenderPresent(rend);

        {
            end = chrono::high_resolution_clock::now();
            dur = end - begin;
            dur_ms = (int) chrono::duration_cast<std::chrono::milliseconds>(dur).count();
            SDL_Delay(Uint32(16 - dur_ms < 0 ? 0 : 16 - dur_ms));
        }
    }


    TTF_CloseFont(my_font);
    TTF_Quit();

}