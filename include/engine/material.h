#pragma once

#include <engine/color.h>

struct Material {
  Material() = default;
  Material(const Color& color) : color(color) {}

  Color color;
};
