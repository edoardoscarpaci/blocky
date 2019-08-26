TARGET= main
INCLUDE_DIR= -I./ -Iinclude/  -I/usr/include/glad/  -I/usr/include/glm/  -I/usr/local/include/GLFW 
SRC_DIR = -Isrc/
FLAGS= -Wall -pthread -g -D DEBUG  -ldl  `pkg-config --static --libs x11 xrandr xi xxf86vm glfw3`
LINKER=  
OBJECTS= main.o datatype.o cube.o vbo.o buffer.o window.o renderable.o renderer.o vertexarray.o indexarray.o block.o glad.o
FILE_SRC= main.cpp datatype.cpp cube.cpp vbo.cpp buffer.cpp window.cpp renderable.cpp renderer.cpp vertexarray.cpp indexarray.cpp block.cpp 
FILE_INCLUDE= macro.h datatype.hpp vbo.hpp common.hpp buffer.hpp renderer.hpp renderable.hpp indexarray.hpp window.hpp vertexarray.hpp cube.hpp block.hpp 
BUILD_DIR= build/


default : $(BUILD_DIR)$(TARGET)
$(BUILD_DIR)$(TARGET) : $(OBJECTS) 
	g++ $(OBJECTS) $(FLAGS) $(LINKER) -o $(BUILD_DIR)$(TARGET)

glad.o: /usr/local/src/glad.c 
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c /usr/local/src/glad.c 

main.o: src/main.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/main.cpp

datatype.o: src/util/datatype.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/util/datatype.cpp

cube.o: src/Graphics/cube.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/cube.cpp

vbo.o: src/Graphics/vbo.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/vbo.cpp

buffer.o: src/Graphics/buffer.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/buffer.cpp

window.o: src/Graphics/window.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/window.cpp

renderable.o: src/Graphics/renderable.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/renderable.cpp

renderer.o: src/Graphics/renderer.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/renderer.cpp

vertexarray.o: src/Graphics/vertexarray.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/vertexarray.cpp

indexarray.o: src/Graphics/indexarray.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/indexarray.cpp

block.o: src/Block/block.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Block/block.cpp

clean : 
	 rm -f *.o