#pragma once

#include <engine/object.h>
#include <engine/renderable.h>

class Sphere : public Object, public Renderable {
 public:
  Sphere(Object* parent, double radius = 1)
      : Object(parent, ObjectType::Sphere), radius_(radius) {}

  void SetRadius(double radius) { radius_ = radius; }

  double GetRadius() { return radius_; }

  bool RayIntersection(const Ray& ray) const override {
    // https://raytracing.github.io/books/RayTracingInOneWeekend.html
    // x^2 + y^2 + z^2 = R^2
    // (ray(t) - world_position)^2 = R^2
    // we want to find all the values of t where the ray intersects the sphere
    // (ray(t) - world_position)^2 can be turned into a quadratic equation that
    // we can check the discriminant of to see if there is a solution that
    // satisfies the above equation (a value of t exists for which the ray
    // passes through the sphere).
    // See: https://raytracing.github.io/images/fig-1.04-ray-sphere.jpg

    // The final quadratic equation (where b is direction and )
    // b⋅b*t^2 + 2b⋅(A−C)*t + (A−C)⋅(A−C)−r^2 = 0

    const auto sphere_origin = (ray.Origin() - world_transform_.translation());

    // quadratic term
    auto a = ray.Direction().dot(ray.Direction());
    auto b = 2.0 * sphere_origin.dot(ray.Direction());
    auto c = sphere_origin.dot(sphere_origin) - radius_ * radius_;

    auto discriminant = b * b - 4 * a * c;

    return discriminant > 0;  // 1 or 2 roots
  }

 protected:
  double radius_;
};

template <>
struct ObjectTraits<Sphere> {
  static constexpr ObjectType type = ObjectType::Sphere;
  static constexpr bool renderable = true;
};
