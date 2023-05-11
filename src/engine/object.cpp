#include <engine/object.h>
#include <engine/scene.h>

Object::Object(Object* parent, ObjectType type)
    : parent_(parent),
      type_(type),
      local_transform_(Eigen::Affine3d::Identity()),
      world_transform_(Eigen::Affine3d::Identity()){};

void Object::Update(double dt) {
  bool set_child_world_transform_dirty = world_transform_dirty_;
  if (world_transform_dirty_) {
    UpdateWorldTransform();
    world_transform_dirty_ = false;
  }
  for (auto& child : children_) {
    if (set_child_world_transform_dirty) {
      child->world_transform_dirty_ = true;
    }
    child->Update(dt);
  }
}

Scene* Object::GetRoot() {
  if (parent_ == nullptr) {
    return dynamic_cast<Scene*>(this);
  }
  return dynamic_cast<Scene*>(parent_->GetRoot());
}

const Scene* Object::GetRoot() const {
  if (parent_ == nullptr) {
    return dynamic_cast<const Scene*>(this);
  }
  return dynamic_cast<const Scene*>(parent_->GetRoot());
}

SceneObjects& Object::GetSceneObjects() { return GetRoot()->GetSceneObjects(); }

const SceneObjects& Object::GetSceneObjects() const {
  return GetRoot()->GetSceneObjects();
}

void Object::QueueFree() {
  GetRoot()->QueueForDeletion(std::move(parent_->DetachChild(this)));
}

// protected and private methods

void Object::UpdateWorldTransform() {
  if (parent_ == nullptr) {
    world_transform_ = local_transform_;
    return;
  }
  world_transform_ = parent_->GetWorldTransform() * local_transform_;
}
