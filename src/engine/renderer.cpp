#include <engine/color.h>
#include <engine/renderer.h>
#include <engine/scene.h>

#include <iostream>
#include <vector>

Color SkyboxColor(const Ray& r) {
  auto unit_direction = r.Direction().normalized();
  auto t = 0.5 * (unit_direction.y() + 1.0);
  auto col = 0xffffffff;
  return (1.0 - t) * Color(0xFF, 0xFF, 0xFF, 0xFF) +
         Color(0x77, 0xAA, 0xFF, 0xFF) * t;
}

Renderer::Renderer() : buffer_() {}

Renderer::~Renderer() {}

std::vector<uint32_t> Renderer::Render(const Camera* camera) {
  const auto width = camera->GetWidth();
  const auto height = camera->GetHeight();
  buffer_.resize(width * height);

  auto scene_objects = camera->GetRoot()->GetSceneObjects();
  auto begin_renderable_objects = scene_objects.BeginRenderableObjects();
  auto end_renderable_objects = scene_objects.EndRenderableObjects();

  for (auto i = 0u; i < width; i++) {
    for (auto j = 0u; j < height; j++) {
      auto ray = camera->GetRay(static_cast<double>(i) / (width - 1),
                                static_cast<double>(j) / (height - 1));
      auto k = (height - j) * width + i;
      const auto sky_color = SkyboxColor(ray);
      buffer_[k] = sky_color;

      for (auto it = begin_renderable_objects; it != end_renderable_objects;
           it++) {
        auto intersects = (*it)->RayIntersection(ray);
        if (intersects) {
          buffer_[k] = (*it)->GetMaterial().color;
          break;
        }
      }
    }
  }

  return buffer_;
}