OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CC = g++
COMPILER_FLAGS = -L/media/removable/UNTITLED/lua-5.3.4/src -I/media/removable/UNTITLED/lua-5.3.4/src
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua -ldl -lm
OBJ_NAME = main
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
clean:
	rm -f $(OBJS) $(wildcard *~)
fclean:
	rm -f $(OBJS) $(OBJ_NAME) $(wildcard *~)
re:
	make clean all
