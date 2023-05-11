#include <engine/ray.h>

std::ostream& operator<<(std::ostream& stream, const Ray& ray) {
  return stream << ray.orig << " -> " << ray.dir;
}