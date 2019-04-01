#include <cmath>
#include "drawable.h"
#include "playerSprite.h"
#include "smartSprite.h"

class CollisionStrategy {
public:
  virtual bool execute(const PlayerSprite&, const SmartSprite&) const = 0;
  virtual void draw() const = 0;
  virtual ~CollisionStrategy() {}
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
  virtual bool execute(const PlayerSprite&, const SmartSprite&) const;
  virtual void draw() const;
  virtual ~RectangularCollisionStrategy() {}
};
