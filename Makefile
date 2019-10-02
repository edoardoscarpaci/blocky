TARGET=main
INCLUDE_DIR= -I./ -I./usr/include/ -Iinclude/  -I/usr/include/glad/  -I/usr/include/glm/  -I/usr/local/include/GLFW/
SRC_DIR = -Isrc/
FLAGS= -Wall -pthread -ggdb -g3 -D DEBUG  -ldl  `pkg-config --static --libs x11 xrandr xi xxf86vm glfw3` -lpng
LINKER=  
OBJECTS= $(OBJECT_DIR)main.o $(OBJECT_DIR)block.o $(OBJECT_DIR)cube.o $(OBJECT_DIR)camera.o $(OBJECT_DIR)vertexarray.o $(OBJECT_DIR)buffer.o $(OBJECT_DIR)window.o $(OBJECT_DIR)indexarray.o $(OBJECT_DIR)vbo.o $(OBJECT_DIR)texture.o $(OBJECT_DIR)shader.o $(OBJECT_DIR)renderer.o $(OBJECT_DIR)keybinding.o $(OBJECT_DIR)timer.o $(OBJECT_DIR)callback.o $(OBJECT_DIR)gamemanager.o $(OBJECT_DIR)datatype.o $(OBJECT_DIR)entity.o $(OBJECT_DIR)player.o $(OBJECT_DIR)dynamic.o $(OBJECT_DIR)glad.o
FILE_SRC= main.cpp block.cpp cube.cpp camera.cpp vertexarray.cpp buffer.cpp window.cpp indexarray.cpp vbo.cpp texture.cpp shader.cpp renderer.cpp keybinding.cpp timer.cpp callback.cpp gamemanager.cpp datatype.cpp entity.cpp player.cpp dynamic.cpp 
FILE_INCLUDE= macro.h block.hpp vbo.hpp cube.hpp buffer.hpp texture.hpp camera.hpp shader.hpp window.hpp renderable.hpp vertexarray.hpp renderer.hpp common.hpp indexarray.hpp keybinding.hpp callback.hpp datatype.hpp timer.hpp gamemanager.hpp dynamic.hpp entity.hpp player.hpp 
BUILD_DIR= build/
OBJECT_DIR= build/object/


default : $(BUILD_DIR)$(TARGET)
$(BUILD_DIR)$(TARGET) : $(OBJECTS) 
	g++ $(OBJECTS) $(FLAGS) $(LINKER) -o $(BUILD_DIR)$(TARGET)

$(OBJECT_DIR)glad.o: /usr/local/src/glad.c 
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c /usr/local/src/glad.c -o $(OBJECT_DIR)glad.o

$(OBJECT_DIR)main.o: src/main.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/main.cpp -o $(OBJECT_DIR)main.o

$(OBJECT_DIR)block.o: src/Block/block.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Block/block.cpp -o $(OBJECT_DIR)block.o

$(OBJECT_DIR)cube.o: src/Graphics/cube.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/cube.cpp -o $(OBJECT_DIR)cube.o

$(OBJECT_DIR)camera.o: src/Graphics/camera.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/camera.cpp -o $(OBJECT_DIR)camera.o

$(OBJECT_DIR)vertexarray.o: src/Graphics/vertexarray.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/vertexarray.cpp -o $(OBJECT_DIR)vertexarray.o

$(OBJECT_DIR)buffer.o: src/Graphics/buffer.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/buffer.cpp -o $(OBJECT_DIR)buffer.o

$(OBJECT_DIR)window.o: src/Graphics/window.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/window.cpp -o $(OBJECT_DIR)window.o

$(OBJECT_DIR)indexarray.o: src/Graphics/indexarray.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/indexarray.cpp -o $(OBJECT_DIR)indexarray.o

$(OBJECT_DIR)vbo.o: src/Graphics/vbo.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/vbo.cpp -o $(OBJECT_DIR)vbo.o

$(OBJECT_DIR)texture.o: src/Graphics/texture.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/texture.cpp -o $(OBJECT_DIR)texture.o

$(OBJECT_DIR)shader.o: src/Graphics/shader.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/shader.cpp -o $(OBJECT_DIR)shader.o

$(OBJECT_DIR)renderer.o: src/Graphics/renderer.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Graphics/renderer.cpp -o $(OBJECT_DIR)renderer.o

$(OBJECT_DIR)keybinding.o: src/util/keybinding.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/util/keybinding.cpp -o $(OBJECT_DIR)keybinding.o

$(OBJECT_DIR)timer.o: src/util/timer.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/util/timer.cpp -o $(OBJECT_DIR)timer.o

$(OBJECT_DIR)callback.o: src/util/callback.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/util/callback.cpp -o $(OBJECT_DIR)callback.o

$(OBJECT_DIR)gamemanager.o: src/util/gamemanager.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/util/gamemanager.cpp -o $(OBJECT_DIR)gamemanager.o

$(OBJECT_DIR)datatype.o: src/util/datatype.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/util/datatype.cpp -o $(OBJECT_DIR)datatype.o

$(OBJECT_DIR)entity.o: src/Entity/entity.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Entity/entity.cpp -o $(OBJECT_DIR)entity.o

$(OBJECT_DIR)player.o: src/Entity/player.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Entity/player.cpp -o $(OBJECT_DIR)player.o

$(OBJECT_DIR)dynamic.o: src/Entity/dynamic.cpp
	g++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c src/Entity/dynamic.cpp -o $(OBJECT_DIR)dynamic.o

clean : 
	 rm -f $(OBJECT_DIR)*.o