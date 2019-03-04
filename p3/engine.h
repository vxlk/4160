#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
private:
  const RenderContext& rc; //*
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  World clouds;
  Viewport& viewport;

  std::vector<Drawable*> drawables;
  //Drawable* star;
  //Drawable* spinningStar;
  int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void drawFPS(const int &x, const int &y, const SDL_Color& c) const;
  void drawName(const int& x, const int& y, const SDL_Color& c) const;

  void printScales() const;
  void checkForCollisions();

  const std::string name = "Tyler Small";
};
