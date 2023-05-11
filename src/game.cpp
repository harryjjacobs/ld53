#include <emscripten/bind.h>
#include <engine/camera.h>
#include <engine/color.h>
#include <engine/light.h>
#include <engine/sphere.h>
#include <engine/torus.h>
#include <game/game.h>

#include <iostream>

using emscripten::val;

// Use thread_local when you want to retrieve & cache a global JS variable once
// per thread.
thread_local const val worker = val::global("worker");

EM_JS(void, UpdateFps, (double fps), {
  // clang-format off
  Module['setFps'](fps);
  // clang-format on
});

EM_JS(void, SetDataToCanvas, (uint32_t * ptr, size_t width, size_t height), {
  // clang-format off
  let data = Module.HEAPU8.slice(ptr, ptr + width * height * 4);
  let context = Module['canvas'].getContext('2d');
  let imageData = context.getImageData(0, 0, width, height);
  imageData.data.set(data);
  context.putImageData(imageData, 0, 0);
  // clang-format on
});

static EM_BOOL AnimationFrameLoopCallback(double time, void* userData) {
  auto* klass = static_cast<Game*>(userData);
  return klass->AnimationFrameLoopCallback(time) ? EM_TRUE : EM_FALSE;
}

Game::Game(const GameParams& params) : params_(params), last_loop_time_(0) {
  std::cout << "Initialising game" << std::endl;
  std::cout << "width: " << params_.width << ", height: " << params_.height
            << ", vfov:" << params_.vfov << std::endl;

  auto color1 = Color(0xFF, 0xFF, 0xFF, 0xFF);
  auto color2 = Color(0x77, 0xAA, 0xFF, 0xFF);

  double t = 0.5;
  auto color3 = (1.0 - t) * color1 + color2 * t;

  std::cout << color1 << std::endl;
  std::cout << color2 << std::endl;
  std::cout << color3 << std::endl;

  auto* camera = scene_.AddChild(std::make_unique<Camera>(
      &scene_, Eigen::Vector2i(params_.width, params_.height), 90.0));
  camera->SetLocalTransform(Eigen::Affine3d::Identity());

  auto* light = scene_.AddChild(std::make_unique<Light>(&scene_));

  // auto* sphere = scene_.AddChild(std::make_unique<Sphere>(&scene_, 1));
  // sphere->SetMaterial(Material(Color(0xFF, 0x00, 0x00, 0xFF)));
  // sphere->SetLocalTransform(
  //     sphere->GetLocalTransform().translate(Eigen::Vector3d(0, 0, 2)));

  auto* torus = scene_.AddChild(std::make_unique<Torus>(&scene_, 0.5, 0.2));
  torus->SetMaterial(Material(Color(0xFF, 0x00, 0x00, 0xFF)));
  torus->SetLocalTransform(
      torus->GetLocalTransform().translate(Eigen::Vector3d(0, 0, 3)));
}

void Game::Run() {
  emscripten_request_animation_frame_loop(&::AnimationFrameLoopCallback, this);
}

bool Game::AnimationFrameLoopCallback(double time) {
  double dt = time / 1000.0 - last_loop_time_;
  UpdateFps(1.0 / dt);
  scene_.Update(dt);
  const auto* camera = scene_.GetCamera();
  auto output = renderer_.Render(camera);
  // std::cout << "after render" << std::endl;
  // std::cout << output.size() << std::endl;
  SetDataToCanvas(output.data(), params_.width, params_.height);
  last_loop_time_ = time / 1000.0;
  return true;
}
