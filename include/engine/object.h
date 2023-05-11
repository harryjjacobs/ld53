#pragma once

#include <engine/object_meta.h>
#include <engine/ray.h>
#include <engine/renderable.h>
#include <engine/scene_objects.h>

#include <Eigen/Geometry>
#include <memory>
#include <vector>

class Scene;

class Object {
 public:
  Object(Object* parent, ObjectType type);
  ~Object() = default;

  virtual void Update(double dt);

  template <typename TObject>
  inline TObject* AddChild(std::unique_ptr<TObject>&& child) {
    child->parent_ = this;
    auto* child_ptr = child.get();
    GetSceneObjects().RegisterObject<TObject>(child_ptr);
    children_.push_back(std::move(child));
    return child_ptr;
  }

  template <typename TObject>
  std::unique_ptr<TObject> DetachChild(TObject* child) {
    for (auto it = children_.begin(); it != children_.end(); ++it) {
      if (it->get() == child) {
        children_.erase(it);
        GetSceneObjects().UnRegisterObject<TObject>(child);
        return std::move(*it);
      }
    }
    return nullptr;
  }

  void QueueFree();

  Scene* GetRoot();

  const Scene* GetRoot() const;

  SceneObjects& GetSceneObjects();

  const SceneObjects& GetSceneObjects() const;

  template <typename T>
  const T* FindChild() const {
    for (const auto& child : children_) {
      if (child->type_ == ObjectTraits<T>::type) {
        return dynamic_cast<T*>(child.get());
      } else {
        return child->FindChild<T>();
      }
    }
    return nullptr;
  }

  const std::vector<Object*> RecurseAllChildren() const {
    std::vector<Object*> children;
    for (const auto& child : children_) {
      auto child_children = child->RecurseAllChildren();
      children.insert(children.end(), child_children.begin(),
                      child_children.end());
    }
    return children;
  }

  Eigen::Affine3d GetWorldTransform() const { return world_transform_; }

  Eigen::Affine3d GetLocalTransform() const { return local_transform_; }

  void SetLocalTransform(const Eigen::Affine3d& transform) {
    local_transform_ = transform;
    UpdateWorldTransform();
  }

 protected:
  void UpdateWorldTransform();

  ObjectType type_;
  Object* parent_;
  std::vector<std::unique_ptr<Object>> children_;
  Eigen::Affine3d local_transform_;
  Eigen::Affine3d world_transform_;
  bool world_transform_dirty_;
};
