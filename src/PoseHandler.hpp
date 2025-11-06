#pragma once
#include "Direction.hpp"
#include "Executor.hpp"

// 由于ExcecutorImpl与ICommand里面的函数都用到了对方的类，互相依赖，这不好，所以要把造成依赖的共同成员抽离出来
namespace adas
{
class PoseHandler final
{
  public:
    PoseHandler(const Pose &pose) noexcept;
    PoseHandler(const PoseHandler &) = delete;            // 禁止拷贝构造
    PoseHandler &operator=(const PoseHandler &) = delete; // 禁止拷贝赋值
  public:
    void Forward(void) noexcept;
    void Backward(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;

    void Reverse(void) noexcept;
    bool IsReverse(void) const noexcept;

    Pose Query(void) const noexcept;

  private:
    // 使用point与direction替换pose，使变换更整体
    Point point;
    const Direction *facing;
    bool isfast{false};
    bool isreverse{false};
};

} // namespace adas
