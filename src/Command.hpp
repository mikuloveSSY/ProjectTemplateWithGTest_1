#pragma once
#include "PoseHandler.hpp"
#include <functional>
// functional提供函数包装器

namespace adas
{
// 下面三个类虽然是把执行动作封装了，但还是有执行动作的函数接口重复，所以这个类的目的就是把调用这三个类的执行动作的‘接口’抽象化从而达到多态运行
// class ICommand
// {
//   public:
//     // 析构函数也要虚，因为多态运行时，析构执行时的对象也是多态类型的
//     virtual ~ICommand() noexcept = default;
//     virtual void DoOperate(PoseHandler &poseHandler) const noexcept = 0; // 纯虚
// };
// 注意，对于加速状态的判断也用函数来调用，这也是面对对象编程的习惯：不随意使用private数据成员
class MoveCommand final //: public ICommand
{
  public:
    // // 执行Move动作，委托给一个执行器来完成动作(override表示强制重写虚函数)
    // void DoOperate(PoseHandler &poseHandler) const noexcept override
    // {
    //     if (poseHandler.IsFast())
    //     {
    //         poseHandler.Move();
    //     }
    //     poseHandler.Move();
    // }

    // 定义函数对象operate,接受参数PoseHandler，返回void
    const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept {
        if (poseHandler.IsFast())
        {
            poseHandler.Move();
        }
        poseHandler.Move();
    };
};
class TurnLeftCommand final //: public ICommand
{
  public:
    const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept {
        if (poseHandler.IsFast())
        {
            poseHandler.Move();
        }
        poseHandler.TurnLeft();
    };
};
class TurnRightCommand final //: public ICommand
{
  public:
    const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept {
        if (poseHandler.IsFast())
        {
            poseHandler.Move();
        }
        poseHandler.TurnRight();
    };
};
class FastCommand final //: public ICommand
{
  public:
    const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept {
        poseHandler.Fast();
    };
};

} // namespace adas