#include <engine/color.h>

Color operator*(const Color& color, double other) {
  auto colcopy = color;
  return colcopy *= other;
}

Color operator*(double other, const Color& color) {
  auto colcopy = color;
  return colcopy *= other;
}

Color operator+(const Color& left, const Color& right) {
  auto colcopy = left;
  return colcopy += right;
}

std::ostream& operator<<(std::ostream& stream, const Color& color) {
  return stream << "rgba(" << (static_cast<unsigned int>(color.GetR()) & 0xFFu)
                << ", " << (static_cast<unsigned int>(color.GetG()) & 0xFFu)
                << ", " << (static_cast<unsigned int>(color.GetB()) & 0xFFu)
                << ", " << (static_cast<unsigned int>(color.GetA()) & 0xFFu)
                << ") "
                << "0x" << std::hex << color.value;
}
