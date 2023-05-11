#include <emscripten/bind.h>
#include <game/game.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(game) {
  class_<GameParams>("GameParams")
      .constructor()
      .constructor<size_t, size_t, double>();

  class_<Game>("Game").constructor<const GameParams &>().function("Run",
                                                                  &Game::Run);
  // .property("x", &MyClass::getX, &MyClass::setX)
}
