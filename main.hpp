#ifndef _MAIN_HPP_
#define _MAIN_HPP_
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
};
#include <stdio.h>
#include "sprite.hpp"
#include "lua_sprites.hpp"

struct luaClassList {
  const char * name;
  const struct luaL_Reg * meta;
};

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern SDL_Renderer *globalRenderer;
#endif
