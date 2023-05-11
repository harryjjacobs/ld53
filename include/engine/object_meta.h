#pragma once

enum class ObjectType {
  Object,
  Scene,
  Camera,
  Light,
  Sphere,
  Torus,
  Cuboid,
  Mesh,
};

template <typename T>
struct ObjectTraits {
  static constexpr ObjectType type = ObjectType::Object;
  static constexpr bool renderable = false;
};
