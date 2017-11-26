#include "lua_sprites.hpp"

static void set_meta(lua_State *L, int ind, const char * name){
  lua_getglobal(L, "Game");
  lua_getfield(L, -1, name);
  lua_setmetatable(L, ind - 2);
  lua_pop(L, 1);
}

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

void printLuaStack(lua_State *L, const char *name){
  int args = lua_gettop(L);
  size_t s;
  printf("top at(%s): %i\n", name, args);
  for(int i = 0; i < args; ++i){
    printf("arg %i %s\n", i, luaL_tolstring(L, -args + i, &s));
    lua_pop(L, 1);
  }
}

static int l_meta_indexer(lua_State *L){
  //printLuaStack(L, "meta_index");
  lua_getmetatable(L, -2);
  //table
  //str
  //meta
  lua_replace(L, -3);
  //meta
  //str
  lua_gettable(L, -2);
  //meta
  //val
  lua_replace(L, -2);
  //val
  return 1;
}

static int l_draw_sprite(lua_State *L){
  Sprite *s;
  if (!lua_isuserdata(L, -1)){
    lua_pop(L, 1);
    return 0;
  }
  s = *(Sprite **)lua_touserdata(L, -1);
  lua_pop(L, 1);
  s->draw();
  return 0;
}

static int l_new_texture(lua_State *L){
  //printLuaStack(L, "new_tex");
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
  //printLuaStack(L, "new_sprite");
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
  //  printf("x %i, y %i, w %i, h %i\n", x,y,w,h);
  tex = (SDL_Texture *)lua_touserdata(L, -1);
  lua_pop(L, 1);
  s = new Sprite();
  *reinterpret_cast<Sprite **>(lua_newuserdata(L, sizeof(Sprite*))) = s;
  s->init(tex, x, y, w, h);
  /*for(int l = 0; l < sizeof(Sprite); l++){
    printf("c: %i/%ld v: %i\n", l, sizeof(Sprite), *(c++));
    }*/
  s->draw();
  set_meta(L, -1, "Sprite");
  return 1;
}

static const struct luaL_Reg spritemeta [] = {
  {"new", l_new_sprite},
  {"draw", l_draw_sprite},
  {"__index", l_meta_indexer},
  {NULL, NULL}
};

static const struct luaL_Reg texturemeta [] = {
  {"new", l_new_texture},
  {"destroy", l_free_texture},
  {NULL, NULL}
};

static const struct luaClassList game [] = {
  {"Texture", texturemeta},
  {"Sprite", spritemeta},
  {NULL, NULL}
};

int luaopen_sprites (lua_State *L) {
  int count = 0;
  lua_newtable(L);
  struct luaClassList *ptr = (struct luaClassList *)game;
  while(ptr->name != NULL){
    ++count;
    lua_newtable(L);
    luaL_setfuncs(L, ptr->meta, 0);
    lua_setfield(L, -2, ptr->name);
    ++ptr;
  }
  return 1;
}

