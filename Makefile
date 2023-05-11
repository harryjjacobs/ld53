ENGINE_SRC := src/engine/renderer.cpp src/engine/object.cpp src/engine/scene.cpp src/engine/ray.cpp src/engine/color.cpp
ENGINE_OBJ := $(patsubst src/%,bin/%,$(ENGINE_SRC:.cpp=.o))

all: bin/bindings.js

bin/bindings.js: bin/engine/libengine.a src/bindings.cpp src/game.cpp
	emcc -Lbin/engine -lembind -lengine -Iinclude -I/usr/local/include -I/usr/include/eigen3 -o bin/bindings.js src/bindings.cpp src/game.cpp

bin/engine/libengine.a: $(ENGINE_OBJ)
	emar rcs $@ $^

# TODO: .h file changes not picked up by make
bin/%.o: src/%.cpp include/%.h
	@mkdir -p $(@D)
	emcc -I/usr/local/include -I/usr/include/eigen3 -Iinclude -c $< -o $@

clean:
	rm -rf bin