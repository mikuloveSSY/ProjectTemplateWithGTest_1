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

// operator() 是一个特殊的函数，称为函数调用运算符。它允许一个对象像函数一样被调用。
// 当你定义了一个重载了operator()的类时，你可以创建一个类的实例，然后像调用函数一样调用它。
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
    void operator()(PoseHandler &poseHandler) noexcept
    {
        if (poseHandler.IsFast())
        {
            if (poseHandler.IsReverse())
            {
                poseHandler.Backward();
            }
            else
            {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse())
        {
            poseHandler.Backward();
        }
        else
        {
            poseHandler.Forward();
        }
    };
};
class TurnLeftCommand final //: public ICommand
{
  public:
    void operator()(PoseHandler &poseHandler) noexcept
    {
        if (poseHandler.IsFast())
        {
            if (poseHandler.IsReverse())
            {
                poseHandler.Backward();
            }
            else
            {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse())
        {
            poseHandler.TurnRight();
        }
        else
        {
            poseHandler.TurnLeft();
        }
    };
};
class TurnRightCommand final //: public ICommand
{
  public:
    void operator()(PoseHandler &poseHandler) noexcept
    {
        if (poseHandler.IsFast())
        {
            if (poseHandler.IsReverse())
            {
                poseHandler.Backward();
            }
            else
            {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse())
        {
            poseHandler.TurnLeft();
        }
        else
        {
            poseHandler.TurnRight();
        }
    }
};
class FastCommand final //: public ICommand
{
  public:
    void operator()(PoseHandler &poseHandler) noexcept
    {
        poseHandler.Fast();
    };
};
class ReverseCommand final
{
  public:
    void operator()(PoseHandler &poseHandler) noexcept
    {
        poseHandler.Reverse();
    };
};
} // namespace adas