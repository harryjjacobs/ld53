#pragma once

#include <engine/object.h>
#include <engine/object_meta.h>
#include <engine/ray.h>

#include <Eigen/Geometry>
#include <iostream>

class Camera : public Object {
 public:
  /**
   * @brief Construct a new Camera object
   *
   * @param vfov Vertical field of view theta
   * @param aspect_ratio
   */
  Camera(Object* parent, const Eigen::Vector2i& viewport_size, double vfov)
      : Object(parent, ObjectType::Camera),
        viewport_size_(viewport_size),
        vfov_(vfov),
        aspect_ratio_(static_cast<double>(viewport_size[0]) / viewport_size[1]),
        focal_length_(viewport_size[1] / (2 * tan(vfov))) {}

  double GetWidth() const { return viewport_size_[0]; }

  double GetHeight() const { return viewport_size_[1]; }

  Eigen::Vector2i GetSize() const { return viewport_size_; }

  Ray GetRay(double u, double v) const {
    const auto origin = Eigen::Vector3d(world_transform_.translation());
    // std::cout << "origin: " << origin << std::endl;
    const auto lower_left_corner = Eigen::Vector3d(
        -viewport_size_[0] / 2, -viewport_size_[1] / 2, aspect_ratio_);
    // std::cout << "lower_left_corner: " << lower_left_corner << std::endl;

    const auto viewport_position =
        lower_left_corner + Eigen::Vector3d(viewport_size_[0] * u,
                                            viewport_size_[1] * v,
                                            focal_length_);

    // std::cout << "viewport_position: " << viewport_position << std::endl;

    const auto direction =
        (world_transform_ * Eigen::Translation3d(viewport_position))
            .translation();

    // std::cout << "direction: " << direction << std::endl;

    return Ray(origin, direction);
  }

 private:
  double vfov_;
  const double aspect_ratio_;
  double focal_length_;
  Eigen::Vector2i viewport_size_;
};

template <>
struct ObjectTraits<Camera> {
  static constexpr ObjectType type = ObjectType::Camera;
  static constexpr bool renderable = false;
};
