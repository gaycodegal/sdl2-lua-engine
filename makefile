INC=./headers
SRC=./source
CPPS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(CPPS))
CC = g++
DEPS = $(wildcard $(INC)/*.hpp)
COMPILER_FLAGS = -L/media/removable/UNTITLED/lua-5.3.4/src -I/media/removable/UNTITLED/lua-5.3.4/src -I$(INC)
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua -ldl -lm
OBJ_NAME = main
all:
	$(CC) $(CPPS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
clean:
	rm -f $(OBJS) $(wildcard *~) $(wildcard $(SRC)/*~) $(wildcard $(INC)/*~)
fclean:
	rm -f $(OBJS) $(OBJ_NAME) $(wildcard *~)
re:
	make clean all
