#pragma once

#include "Point.hpp"

namespace adas
{
// 方向类
class Direction final
{
  public:
    // 根据字符确定方向
    static const Direction &GetDirection(const char heading) noexcept;

  public:
    Direction(const unsigned index, const char heading) noexcept;

  public:
    // 移动
    const Point &Move(void) const noexcept;
    // 左右转向
    const Direction &LeftOne(void) const noexcept;
    const Direction &RightOne(void) const noexcept;

    const char GetHeading(void) const noexcept;

  private:
    unsigned index; // 方向索引
    char heading;   // 方向字符
};
} // namespace adas