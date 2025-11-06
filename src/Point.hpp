#pragma once

namespace adas
{
class Point final
{
  public:
    // 构造
    Point(const int x, const int y) noexcept;
    Point(const Point &rhs) noexcept;
    Point &operator=(const Point &rhs) noexcept;
    Point &operator+=(const Point &rhs) noexcept;

  public:
    int GetX(void) const noexcept;
    int GetY(void) const noexcept;

  private:
    int x;
    int y;
};
} // namespace adas