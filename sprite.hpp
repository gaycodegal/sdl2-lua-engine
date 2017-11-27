#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_
#include "main.hpp"
SDL_Texture* loadTexture( const char *path );

class Drawable{
public:
  Drawable(){}
  virtual ~Drawable(){}
  virtual void draw()=0;
};

class Sprite: public Drawable{
private:
  SDL_Rect dest;
  SDL_Rect source;
  SDL_Texture* texture;
public:
  void init(SDL_Texture *tex, int x, int y, int w, int h);
  void size(int w, int h);
  void move(int x, int y);
  void draw();
};

#endif
