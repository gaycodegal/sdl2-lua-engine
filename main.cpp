#include "main.hpp"
#define SDL_ACTIVE
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window;
SDL_Surface* screenSurface;
SDL_Renderer *globalRenderer;

int start(){
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }
  /* initialize TTF */
  if( TTF_Init() == -1 ){
    printf("Could not initialize SDLTTF SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }
  Uint32 initopts = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
  
  window = SDL_CreateWindow( "SDL Tutorial", 0, 0, /*SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED*/ SCREEN_WIDTH, SCREEN_HEIGHT, initopts );
  if( window == NULL ){
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }
  globalRenderer = SDL_CreateRenderer(window, -1, 0);
  if (!globalRenderer) {
    printf("Could not create renderer SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }
  return 0;
}

int end(){
  if(window != NULL)
    SDL_DestroyWindow( window );
  SDL_Quit();
  return 0;
}

int main( int argc, char* args[] ){
  lua_State *L;
  #ifdef SDL_ACTIVE
  if(start() != 0){
    end();
    return 1;
  }
  #endif
  L = luaL_newstate();
  luaL_openlibs(L);
  luaL_requiref(L, LUA_LIBNAME, luaopen_sprites, 1);
  
  //screenSurface = SDL_GetWindowSurface( window );
  
  //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
  if(luaL_loadfile(L, "load.lua")){
    printf("load fuck 2\n");
    return 1;
  }
  if (lua_pcall(L, 0, 0, 0)){
    /* PRIMING RUN. FORGET THIS AND YOU'RE TOAST */
    printf("0,0,0 fuck 2\n");
    return 1;
  }
  callLuaVoid(L, "loadScene");
  int t = 50;
  while(t--){
    SDL_RenderClear( globalRenderer );
    callLuaVoid(L, "Update");
    SDL_RenderPresent( globalRenderer );
  }
  callLuaVoid(L, "endScene");
  lua_close(L);
  end();
  return 0;
}
