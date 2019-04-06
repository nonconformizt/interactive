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
    SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
    SDL_Texture * ball = SDL_CreateTextureFromSurface(rend, ballImage);
    SDL_FreeSurface(ballImage);


    SDL_Event e;
    bool close = false;
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
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN) {
                    cout << "Down pressed!";
                    balls[activated_ball].y += STEP;
                }
                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP) {
                    cout << "Up pressed!";
                    balls[activated_ball].y -= STEP;
                }
                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT) {
                    cout << "Right pressed!";
                    balls[activated_ball].x += STEP;
                }
                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT) {
                    cout << "Left pressed!";
                    balls[activated_ball].x -= STEP;
                }
                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_DOWN) {
                    cout << "Down released!";
                    balls[activated_ball].y += STEP;
                }
                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_UP) {
                    cout << "Up released!";
                    balls[activated_ball].y -= STEP;
                }
                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RIGHT) {
                    cout << "Right released!";
                    balls[activated_ball].x += STEP;
                }
                else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_LEFT) {
                    cout << "Left released!";
                    balls[activated_ball].x -= STEP;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                for (int i = 0; i < BALL_COUNT; i++)
                    // если нажали на мячик, то сделать его активным
                    if (is_mouse_hit(balls[i], e.button.x, e.button.y)) {
//                        balls[i].w = balls[i].h = 0;
//                        k += prices[i];
//                        _itoa(k, text_val, 10);
//                        SDL_DestroyTexture(text);
//                        text = get_text_texture(rend, text_val, my_font);
                        activated_ball = i;
                    }

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderClear(rend);

        draw_balls(rend, balls, BALL_COUNT, ball);
        for (int j = 0; j < BALL_COUNT; j++) {
            _itoa(prices[j], text_val, 10);
            ball_text[j] = get_ball_text_texture(rend, text_val, my_font);
            draw_ball_text(rend, ball_text[j], balls[j]);
        }
        draw_text(rend, text);

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