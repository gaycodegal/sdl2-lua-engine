#include "lua_sprites.hpp"

static int l_free_texture(lua_State *L){
  SDL_Texture *tex;
  if (!lua_islightuserdata(L, -1)){
    lua_pop(L, 1);
    return 0;
  }
  tex = (SDL_Texture *)lua_touserdata(L, -1);
  lua_pop(L, 1);
  SDL_DestroyTexture(tex);
  return 0;
}

static int l_free_sprite(lua_State *L){
  Sprite *s;
  if (!lua_islightuserdata(L, -1)){
    lua_pop(L, 1);
    return 0;
  }
  s = (Sprite *)lua_touserdata(L, -1);
  lua_pop(L, 1);
  delete s;
  return 0;
}

static int l_draw_sprite(lua_State *L){
  Sprite *s;
  if (!lua_islightuserdata(L, -1)){
    lua_pop(L, 1);
    return 0;
  }
  s = (Sprite *)lua_touserdata(L, -1);
  lua_pop(L, 1);
  s->draw();
  printf("drawn\n");
  return 0;
}

static int l_new_texture(lua_State *L){
  char * path;
  if (!lua_isstring(L, -1)){
    lua_pop(L, 1);
    lua_pushnil(L);
    return 1;
  }
  path = (char *)lua_tostring(L, -1);
  lua_pop(L, 1);
  lua_pushlightuserdata(L, (void *)loadTexture(path));
  return 1;
}

static int l_new_sprite(lua_State *L){
  int x, y, w, h;
  SDL_Texture *tex;
  Sprite *s;
  if (!lua_isnumber(L, -1)){
    lua_pop(L, 2);
    lua_pushnil(L);
    return 1;
  }
  h = (int)lua_tonumber(L, -1);
  lua_pop(L, 1);
  if (!lua_isnumber(L, -1)){
    lua_pop(L, 3);
    lua_pushnil(L);
    return 1;
  }
  w = (int)lua_tonumber(L, -1);
  lua_pop(L, 1);
  if (!lua_isnumber(L, -1)){
    lua_pop(L, 4);
    lua_pushnil(L);
    return 1;
  }
  y = (int)lua_tonumber(L, -1);
  lua_pop(L, 1);
  if (!lua_isnumber(L, -1)){
    lua_pop(L, 5);
    lua_pushnil(L);
    return 1;
  }
  x = (int)lua_tonumber(L, -1);
  lua_pop(L, 1);
  if (!lua_islightuserdata(L, -1)){
    lua_pop(L, 1);
    lua_pushnil(L);
    return 1;
  }
  printf("x %i, y %i, w %i, h %i\n", x,y,w,h);
  tex = (SDL_Texture *)lua_touserdata(L, -1);
  lua_pop(L, 1);  
  s = new Sprite(tex, x, y, w, h);
  s->draw();
  lua_pushlightuserdata(L, (void *)s);
  return 1;
}

static const struct luaL_Reg arraylib [] = {
  {"Sprite", l_new_sprite},
  {"Draw", l_draw_sprite},
  {"Texture", l_new_texture},
  {"DestroySprite", l_free_sprite},
  {"DestroyTexture", l_free_texture},
  {NULL, NULL}
};

int luaopen_sprites (lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, arraylib, 0);
  return 1;
}
