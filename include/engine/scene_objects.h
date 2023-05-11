#pragma once

#include <engine/object_meta.h>
#include <engine/renderable.h>

class Scene;
class Object;

class SceneObjects {
 public:
  SceneObjects(Scene& scene) : scene_(scene) {}

  template <typename ObjectT>
  void RegisterObject(ObjectT* object) {
    if (ObjectTraits<ObjectT>::renderable) {
      renderable_.push_back(dynamic_cast<Renderable*>(object));
    }
  }

  template <typename ObjectT>
  void UnRegisterObject(ObjectT* object) {
    if (ObjectTraits<ObjectT>::renderable) {
      Erase(renderable_, dynamic_cast<Renderable*>(object));
    }
    Erase(all_, object);
  }

  std::vector<Renderable*>::iterator BeginRenderableObjects() {
    return renderable_.begin();
  }

  std::vector<Renderable*>::iterator EndRenderableObjects() {
    return renderable_.end();
  }

  std::vector<Object*>::iterator Begin() { return all_.begin(); }

  std::vector<Object*>::iterator End() { return all_.end(); }

 protected:
  template <typename ObjectT>
  void Erase(std::vector<ObjectT*>& objects, ObjectT* object) {
    auto object_it = std::find(objects.begin(), objects.end(), object);
    if (object_it != objects.end()) {
      objects.erase(object_it);
    }
  }

  std::vector<Object*> all_;
  std::vector<Renderable*> renderable_;
  Scene& scene_;
};