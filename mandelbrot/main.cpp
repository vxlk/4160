#include <iostream>
#include <SDL2/SDL_ttf.h>
//#include "frameGenerator.h"
#include "mandelbrot.h"

const std::string TITLE = "Tyler Small";
const std::string NAME = "tsmall";

const int WIDTH = 640;
const int HEIGHT = 480;

#define PaletteSize 12 //32
enum { Width = 1280, Height = 720 };


/*
NAME
*/
void writeName(SDL_Renderer* renderer) {
  TTF_Init();
  TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24);
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  SDL_Color textColor = {0xff, 0, 0, 0};
  SDL_Surface* surface = 
    TTF_RenderText_Solid(font, TITLE.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {20, HEIGHT-40, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL_Init(SDL_INIT_VIDEO)\n";
    return -1;
  }


  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window, &renderer);
  SDL_SetWindowPosition(window, 65, 126);

  MandelBrot myClass(12, 1280, 720);

  //test assignment
  MandelBrot anotherClass(0,0,0);
  anotherClass = myClass;

    for (int x = 0; x < 1; ++x)
    {                                                                                                  //4
      myClass.paint(renderer);
    }
//------------

  writeName(renderer);
  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
  frameGen.makeFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
