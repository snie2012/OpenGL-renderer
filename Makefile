CC = c++ 

STD_LIB = -std=c++11

OBJ_DIR =  ObjectFile/

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR), $(notdir $(CPP_FILES:.cpp=.o)))

# Default: HPATH=-I /usr/local/include/
HPATH += -I GLEW -framework OpenGL

# Default LDFLAGS=-L /usr/local/lib/
LIBPATH =
LIBS = -lGLEW.2.0.0 
LIBS += -lglfw3.2.1

OBJECTS = $(CPP_FILES:.cpp=.o)

EXECUTABLE = main

$(OBJ_DIR)%.o: %.cpp
	$(CC) $(STD_LIB) -c -o $@ $<
    
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) -o $@ $(OBJ_FILES) $(HPATH) $(LIBPATH) $(LIBS)

clean:
	@rm $(OBJ_DIR)*o $(EXECUTABLE)
