#include "lua_helpers.hpp"

void set_meta(lua_State *L, int ind, const char * name){
  lua_getglobal(L, "Game");
  lua_getfield(L, -1, name);
  lua_setmetatable(L, ind - 2);
  lua_pop(L, 1);
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

int l_meta_indexer(lua_State *L){
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

void callLuaVoid(lua_State *L, const char *name){
  lua_getglobal(L, name);  /* function to be called */
  if (lua_pcall(L, 0, 0, 0) != 0)
    printf("we fucked up calling:%s error:%s\n", name, lua_tostring(L, -1));
}
