#include "Point.hpp"

namespace adas
{
Point::Point(const int x0, const int y0) noexcept : x(x0), y(y0)
{
}
Point::Point(const Point &rhs) noexcept : x(rhs.GetX()), y(rhs.GetY())
{
}
Point &Point::operator=(const Point &rhs) noexcept
{
    x = rhs.GetX(), y = rhs.GetY();
    return *this;
}
Point &Point::operator+=(const Point &rhs) noexcept
{
    x += rhs.GetX();
    y += rhs.GetY();
    return *this;
}
Point &Point::operator-=(const Point &rhs) noexcept
{
    x -= rhs.GetX();
    y -= rhs.GetY();
    return *this;
}
int Point::GetX() const noexcept
{
    return x;
}
int Point::GetY() const noexcept
{
    return y;
}
} // namespace adas