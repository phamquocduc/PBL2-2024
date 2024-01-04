#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include<stdio.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;

class Button {
public:
    Button(SDL_Renderer* renderer, string text, TTF_Font* font, SDL_Color textColor, SDL_Color buttonColor, int x, int y, int w, int h) {
        TTF_SizeText(font, text.c_str(), &rect.w, &rect.h);
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;

        this->buttonColor = buttonColor;
    }

    ~Button() {
        SDL_DestroyTexture(texture);
    }

    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void changeColor(SDL_Renderer* renderer, SDL_Color t) {
        SDL_SetRenderDrawColor(renderer, t.r, t.g, t.b, t.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    bool isClicked(int x, int y) {
        return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
    }

    bool isHovered(int x, int y) {
        return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
    }

    void drawReact(SDL_Renderer* renderer, SDL_Color textColor) {
        SDL_SetRenderDrawColor(renderer, textColor.r, textColor.g, textColor.b, textColor.a);
        SDL_RenderDrawRect(renderer, &rect);
    }
    SDL_Rect getReact() {
        return  rect;
    }

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Color buttonColor;
};
#endif // !BUTTON_H

