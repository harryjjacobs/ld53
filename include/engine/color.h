#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>

/**
 * @brief Represents a color with r, g, b, a channels
 *
 * Stored internally as a 32 bit int with the following structure: aabbggrr
 *
 */
struct Color {
  Color() : value(0x00000000) {}
  Color(const Color& other) : value(other.value) {}
  Color(uint32_t value) : value(value) {}
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
      : value((a << 24) | (b << 16) | (g << 8) | r) {}

  void SetA(uint8_t a) {
    const auto mask = 0x00FFFFFF;
    value &= mask;
    value |= (a << 24);
  }

  void SetB(uint8_t b) {
    const auto mask = 0xFF00FFFF;
    value &= mask;
    value |= (b << 16);
  }

  void SetG(uint8_t g) {
    const auto mask = 0xFFFF00FF;
    value &= mask;
    value |= (g << 8);
  }

  void SetR(uint8_t r) {
    const auto mask = 0xFFFFFF00;
    value &= mask;
    value |= r;
  }

  uint8_t GetA() const { return static_cast<uint8_t>((value >> 24) & 0xFF); }

  uint8_t GetB() const { return static_cast<uint8_t>((value >> 16) & 0xFF); }

  uint8_t GetG() const { return static_cast<uint8_t>((value >> 8) & 0xFF); }

  uint8_t GetR() const { return static_cast<uint8_t>(value & 0xFF); }

  operator uint32_t() const { return value; }

  Color& operator*=(const double other) {
    const auto r = static_cast<uint8_t>(
        std::min(std::max(static_cast<uint32_t>(GetR() * other), 0u), 0xFFu));
    const auto g = static_cast<uint8_t>(
        std::min(std::max(static_cast<uint32_t>(GetG() * other), 0u), 0xFFu));
    const auto b = static_cast<uint8_t>(
        std::min(std::max(static_cast<uint32_t>(GetB() * other), 0u), 0xFFu));
    const auto a = static_cast<uint8_t>(
        std::min(std::max(static_cast<uint32_t>(GetA() * other), 0u), 0xFFu));

    SetR(r);
    SetG(g);
    SetB(b);
    SetA(a);

    return *this;
  }

  Color& operator+=(const Color& other) {
    const auto r = static_cast<uint8_t>(std::min(
        std::max(static_cast<uint32_t>(GetR()) + other.GetR(), 0u), 0xFFu));
    const auto g = static_cast<uint8_t>(std::min(
        std::max(static_cast<uint32_t>(GetG()) + other.GetG(), 0u), 0xFFu));
    const auto b = static_cast<uint8_t>(std::min(
        std::max(static_cast<uint32_t>(GetB()) + other.GetB(), 0u), 0xFFu));
    const auto a = static_cast<uint8_t>(std::min(
        std::max(static_cast<uint32_t>(GetA()) + other.GetA(), 0u), 0xFFu));

    SetR(r);
    SetG(g);
    SetB(b);
    SetA(a);

    return *this;
  }

  friend Color operator*(const Color& color, double other);
  friend Color operator*(double other, const Color& color);

  friend Color operator+(const Color& left, const Color& right);

  friend std::ostream& operator<<(std::ostream& stream, const Color& color);

  // aabbggrr
  uint32_t value;
};