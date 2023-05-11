#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <engine/ray.h>
#include <engine/renderer.h>
#include <engine/scene.h>

#include <chrono>
#include <vector>

struct GameParams {
  GameParams() {}
  GameParams(size_t width, size_t height, double vfov)
      : width(width), height(height), vfov(vfov) {}
  size_t width;
  size_t height;
  double vfov;
};

class Game {
 public:
  Game(const GameParams& params);
  ~Game(){};

  void Run();

  bool AnimationFrameLoopCallback(double time);

 protected:
  GameParams params_;
  Scene scene_;
  Renderer renderer_;
  double last_loop_time_;
};

// Binding code
