#pragma once

#include <engine/object.h>
#include <engine/renderable.h>

class Torus : public Object, public Renderable {
 public:
  Torus(Object* parent, double r0, double r1)
      : Object(parent, ObjectType::Sphere), r0_(r0), r1_(r1) {}

  bool RayIntersection(const Ray& ray) const override {
    const auto origin = world_transform_.translation();

    // quadratic term

    // parametric equation of a torus
    // (x^2 + y^2 + z^2 - r^2)^2 - 4R^2 * (x^2 + y^2) = 0
  }

 protected:
  double r0_;
  double r1_;
};

template <>
struct ObjectTraits<Torus> {
  static constexpr ObjectType type = ObjectType::Torus;
  static constexpr bool renderable = true;
};
