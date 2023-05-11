#pragma once

#include <engine/object.h>

class Light : public Object {
 public:
  Light(Object* parent) : Object(parent, ObjectType::Light) {}
};

template <>
struct ObjectTraits<Light> {
  static constexpr ObjectType type = ObjectType::Light;
  static constexpr bool renderable = false;
};
