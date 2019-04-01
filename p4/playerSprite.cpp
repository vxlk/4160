#include "playerSprite.h"
#include "gameData.h"

PlayerSprite::PlayerSprite( const std::string& name) :
  observers(),
  sprite(name),
  collision(false),
  initialVelocity(sprite.getVelocity()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

void PlayerSprite::stop() { 
  sprite.setVelocity( Vector2f(0, 0) );
  //sprite.setVelocityX( 0.93*sprite.getVelocityX() );
  //sprite.setVelocityY(0);
}


void PlayerSprite::detach( SmartSprite* o ) {
  
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
  
}

void PlayerSprite::right() { 
  if ( sprite.getX() < worldWidth-getScaledWidth()) {
    sprite.setVelocityX(initialVelocity[0]);
  }
} 
void PlayerSprite::left()  { 
  if ( sprite.getX() > 0) {
    sprite.setVelocityX(-initialVelocity[0]);
  }
} 
void PlayerSprite::up()    { 
  if ( sprite.getY() > 0) {
    sprite.setVelocityY( -initialVelocity[1] );
  }
} 
void PlayerSprite::down()  { 
  if ( sprite.getY() < worldHeight-getScaledHeight()) {
    sprite.setVelocityY( initialVelocity[1] );
  }
}

void PlayerSprite::update(Uint32 ticks) { 
  sprite.update(ticks);
  stop();
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    int offset = rand()%5;
    offset = offset*(rand()%2?-1:1);
    const Vector2f off(offset, offset);
    (*ptr)->setPlayerPos( getPosition()+off );
    ++ptr;
  }
}

void PlayerSprite::rotateLeft()
{
    this->sprite.updateRotation(RotationDirections::LEFT);
}

void PlayerSprite::rotateRight()
{
    this->sprite.updateRotation(RotationDirections::RIGHT);
}
