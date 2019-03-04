#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
//#include "multisprite.h"
#include "rotationSprite.h"
#include "twoWayMultiSprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  //delete star;
  //delete spinningStar;
  for(unsigned long int i = 0; i < drawables.size(); ++i)
    delete drawables[i];
  drawables.clear();
  
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  //drawables ({ new Sprite("YellowStar"), new MultiSprite("SpinningStar") }),
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc.getRenderer() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  clouds("clouds", Gamedata::getInstance().getXmlInt("clouds/factor") ),
  viewport( Viewport::getInstance() ),
  //star(new Sprite("YellowStar")),
  //spinningStar(new MultiSprite("SpinningStar")),
  drawables ({ new Sprite("YellowStar"), new TwoWayMultiSprite("AnimationF", "AnimationB"),
               new Sprite("YellowStar"), new TwoWayMultiSprite("AnimationF", "AnimationB"),
               new RotationSprite("Tank"), new RotationSprite("SpinningStar"),
               new Sprite("YellowStar"), new RotationSprite("SpinningStar"),
               new Sprite("YellowStar"), new RotationSprite("SpinningStar"),
               new Sprite("YellowStar"), new RotationSprite("SpinningStar")
             }),
  currentSprite(0),
  makeVideo( false )
{
  //add to vector
  //drawables.emplace_back(new Sprite("YellowStar"));
  //drawables.emplace_back(new MultiSprite("SpinningStar"));

  //star->setScale(1.5); 
  drawables[0]->setScale(1.5);
  drawables[3]->setScale(5.0);
  Viewport::getInstance().setObjectToTrack(drawables[3]);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  world.draw();
  clouds.draw();

  for(unsigned long int i = 0; i < drawables.size(); ++i)
    drawables[i]->draw();
  //star->draw();
  //spinningStar->draw();
  
  //SDL_Color c = {80, 90, 70, 255};
  //drawFPS(50,50, c); //change color
  //drawName(100,100, c);

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::drawFPS(const int &x, const int &y, const SDL_Color& c) const
{
  std::stringstream ss;
  ss << this->clock.getFps();
  this->io.writeText(ss.str(), x, y, c);
}

void Engine::drawName(const int& x, const int& y, const SDL_Color& c) const
{
  this->io.writeText(this->name, x, y, c);
}

void Engine::update(Uint32 ticks) {
  //star->update(ticks);
  //spinningStar->update(ticks);
  
  for(unsigned long int i = 0; i < drawables.size(); ++i)
    drawables[i]->update(ticks);
  
  world.update();
  clouds.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 2;
  /*
  if ( currentSprite ) {
    Viewport::getInstance().setObjectToTrack(spinningStar);
  }
  else {
    Viewport::getInstance().setObjectToTrack(star);
  }
  */
  Viewport::getInstance().setObjectToTrack(drawables[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
