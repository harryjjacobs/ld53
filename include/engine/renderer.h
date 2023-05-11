#pragma once

#include <engine/camera.h>

#include <vector>

class Renderer {
 public:
  Renderer();
  ~Renderer();
  std::vector<uint32_t> Render(const Camera* camera);

 private:
  std::vector<uint32_t> buffer_;
};
