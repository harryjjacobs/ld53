#pragma once

#include <engine/material.h>
#include <engine/ray.h>

class Renderable {
 public:
  virtual bool RayIntersection(const Ray& ray) const = 0;

  void SetMaterial(const Material& material) { material_ = material; }
  Material GetMaterial() { return material_; }

 protected:
  Material material_;
};
