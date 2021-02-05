#include "../include/highscoreWindow.h"
#include "../include/background.h"
#include "SDL2/SDL_ttf.h"
#include "../include/label.h"
#include <sstream>

#define WOLFSTEIN_TTF_ROOT "../../resources/fuentes/joystix.monospace.ttf"
#define BACKGROUND_IMAGE_ROOT "../../client/resources/images/backgroundHighscore.jpg"
#define FONT_SIZE_TITLE 40
#define FONT_SIZE_SUBTITLE 25
#define FONT_SIZE_NAMES 18

HighscoreWindow::HighscoreWindow() {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    this->window = SDL_CreateWindow("Wolfstein 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, windowFlags);

    if (!this->window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    if (TTF_Init() == -1) {
        printf("Failed to init TTF\n");
        exit(1);
    }

    fonts.addFont("wolfstein-title", WOLFSTEIN_TTF_ROOT, FONT_SIZE_TITLE);
    fonts.addFont("wolfstein-subtitle", WOLFSTEIN_TTF_ROOT, FONT_SIZE_SUBTITLE);
    fonts.addFont("wolfstein-names", WOLFSTEIN_TTF_ROOT, FONT_SIZE_NAMES);

    this->renderer = SDL_CreateRenderer(this->window, -1, rendererFlags);

    if (!this->renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

}

void display_text(std::string text, TTF_Font *font, SDL_Renderer *renderer, int w, int h) {
    SDL_Color white = {255, 255, 255, 255};
    Label label(w,
                h,
                text,
                font,
                white,
                renderer);
    label.setLabelText();
    label.draw();
}

void show_highscores(SDL_Renderer *renderer, Fonts fonts) {
    Background background(BACKGROUND_IMAGE_ROOT, renderer);
    SDL_Event e;
    int pressed = false;
    while (!pressed) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    pressed = true;
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();
        display_text("HIGHSCORES", fonts.getFont("wolfstein-title"), renderer, SCREEN_WIDTH / 2, 10);

        display_text("Top kills", fonts.getFont("wolfstein-subtitle"), renderer, SCREEN_WIDTH / 3,
                     50 + FONT_SIZE_TITLE);
        for (int i = 1; i < 6; i++) {
            display_text("#" + std::to_string(i) + " - Ketchup", fonts.getFont("wolfstein-names"), renderer,
                         SCREEN_WIDTH / 3,
                         70 + FONT_SIZE_TITLE + FONT_SIZE_SUBTITLE * i * 1.3);
        }

        display_text("Top score", fonts.getFont("wolfstein-subtitle"), renderer, SCREEN_WIDTH * 8 / 15,
                     50 + FONT_SIZE_TITLE);
        for (int i = 1; i < 6; i++) {
            display_text("#" + std::to_string(i) + " - Alioli", fonts.getFont("wolfstein-names"), renderer,
                         SCREEN_WIDTH * 8 / 15,
                         70 + FONT_SIZE_TITLE + FONT_SIZE_SUBTITLE * i * 1.3);
        }

        display_text("Top shooter", fonts.getFont("wolfstein-subtitle"), renderer, SCREEN_WIDTH * 9 / 12,
                     50 + FONT_SIZE_TITLE);
        for (int i = 1; i < 6; i++) {
            display_text("#" + std::to_string(i) + " - Cami", fonts.getFont("wolfstein-names"), renderer,
                         SCREEN_WIDTH * 9 / 12,
                         70 + FONT_SIZE_TITLE + FONT_SIZE_SUBTITLE * i * 1.3);
        }

        SDL_RenderPresent(renderer);
    }
}

void HighscoreWindow::run() {
    Background background(BACKGROUND_IMAGE_ROOT, this->renderer);
    background.drawBackground();
    while (1) {
        SDL_Event e;
        show_highscores(this->renderer, this->fonts);
    }
}

HighscoreWindow::~HighscoreWindow() {
    SDL_DestroyRenderer(this->renderer);

    SDL_DestroyWindow(this->window);

    SDL_Quit();
}
