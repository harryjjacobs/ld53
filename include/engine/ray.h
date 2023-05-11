#pragma once

#include <Eigen/Geometry>

struct Ray {
  Ray() {}
  Ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction)
      : orig(origin), dir(direction) {}

  Eigen::Vector3d Origin() const { return orig; }
  Eigen::Vector3d Direction() const { return dir; }
  Eigen::Vector3d At(double t) const { return orig + t * dir; }

 private:
  Eigen::Vector3d orig;
  Eigen::Vector3d dir;

  friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);
};
