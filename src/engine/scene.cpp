#include <engine/object.h>
#include <engine/scene.h>
#include <engine/scene_objects.h>

Scene::Scene() : Object(nullptr, ObjectType::Scene), scene_objects_(*this) {}

void Scene::Update(double dt) {
  Object::Update(dt);
  // free deleted objects at end of update frame when safe to do so
  for (auto& object : deletion_queue_) {
    scene_objects_.UnRegisterObject(object.get());
    object.reset();
  }
  deletion_queue_.clear();
}

const Camera* Scene::GetCamera() const { return FindChild<Camera>(); }

void Scene::QueueForDeletion(std::unique_ptr<Object>&& object) {
  deletion_queue_.push_back(std::move(object));
}