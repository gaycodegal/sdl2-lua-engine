#ifndef _LUA_HELPERS_HPP_
#define _LUA_HELPERS_HPP_
#include "main.hpp"
#define LUA_LIBNAME "Game"

int loadLuaFile(lua_State *L, const char *fname);

int globalTypeExists(lua_State *L, int type, const char *name);

/**
   calls a lua funciton as if it were a void
 */
void callLuaVoid(lua_State *L, const char *name);

/**
   Sets the metatable of an object to LUA_LIBNAME.<name>
 */
void set_meta(lua_State *L, int ind, const char * name);

/**
   prints the entire lua stack, which is normally
   empty save for the current arguments to/stack
   manupulations done within a c funciton 
 */
void printLuaStack(lua_State *L, const char *name);

/**
   a function meant to be the __index funciton of
   a metatable on userdata. It will fetch any propety
   of it's own metatable as if it were the property
   of the userdata. Basically useful for accessing
   class methods (and static class vars/functions).
 */
int l_meta_indexer(lua_State *L);

#endif
