#ifndef ROTATIONSPRITE__H
#define ROTATIONSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class RotationSprite : public Drawable
{
public:
    RotationSprite(const std::string&);
    RotationSprite(const RotationSprite&) = delete;
    RotationSprite& operator=(const RotationSprite&) = delete;
    virtual void draw() const override;
    virtual void update(Uint32 ticks) override;

    virtual int getScaledWidth()  const override 
    { 
    return getScale()*images[currentFrame]->getWidth(); 
    } 
    virtual int getScaledHeight()  const override 
    { 
    return getScale()*images[currentFrame]->getHeight(); 
    } 

    virtual const Image* getImage() const override { return images[currentFrame]; }
    virtual const SDL_Surface* getSurface() const override 
    { 
    return images[currentFrame]->getSurface();
    }

protected:
    std::vector<Image *> images;
    inline void updateRotation() { rotationAmount = ((rotationAmount + 1) % 360); }
    //std::vector<Image *> imagesBackward;

    int rotationAmount;
    unsigned currentFrame;
    unsigned numberOfFrames;
    unsigned frameInterval;
    float timeSinceLastFrame;
    int worldWidth;
    int worldHeight;

    void advanceFrame(Uint32 ticks);
};

#endif