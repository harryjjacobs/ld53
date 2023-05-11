#pragma once

#include <engine/camera.h>
#include <engine/object.h>
#include <engine/object_meta.h>

#include <vector>

class SceneObjects;

class Scene : public Object {
 public:
  Scene();

  void Update(double dt) override;

  const Camera* GetCamera() const;

  SceneObjects& GetSceneObjects() { return scene_objects_; }

  const SceneObjects& GetSceneObjects() const { return scene_objects_; }

  void QueueForDeletion(std::unique_ptr<Object>&& object);

 protected:
  SceneObjects scene_objects_;
  std::vector<std::unique_ptr<Object>> deletion_queue_;
};