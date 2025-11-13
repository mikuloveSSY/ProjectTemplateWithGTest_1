#pragma once
#include "..\core\PoseHandler.hpp"
#include "ActionGroup.hpp"
#include <functional> // functional提供函数包装器

namespace adas
{
// operator() 是一个特殊的函数，称为函数调用运算符。它允许一个对象像函数一样被调用。
// 当你定义了一个重载了operator()的类时，你可以创建一个类的实例，然后像调用函数一样调用它。
class MoveCommand final
{
  public:
    // 现在MoveCommand不再直接调用poseHandler的操作了，而是提供对应的指令的枚举值，并以ActionGroup形式返回
    // 所有的操作的真正执行都转移到了ActionGroup里面
    ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto action =
            poseHandler.IsReverse() ? ActionType::BACKWORD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        if (poseHandler.IsFast())
        {
            actionGroup.PushAction(action);
        }
        actionGroup.PushAction(action);
        return actionGroup;
    }
};

class TurnLeftCommand final
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto action1 =
            poseHandler.IsReverse() ? ActionType::BACKWORD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        const auto action2 =
            poseHandler.IsReverse() ? ActionType::REVERSE_TEUNLEFT_ACTION : ActionType::TURNLEFT_ACTION;
        if (poseHandler.IsFast())
        {
            actionGroup.PushAction(action1);
        }
        actionGroup.PushAction(action2);
        return actionGroup;
    }
};

class TurnRightCommand final //: public ICommand
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto action1 =
            poseHandler.IsReverse() ? ActionType::BACKWORD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        const auto action2 =
            poseHandler.IsReverse() ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION;
        if (poseHandler.IsFast())
        {
            actionGroup.PushAction(action1);
        }
        actionGroup.PushAction(action2);
        return actionGroup;
    }
};

class FastCommand final //: public ICommand
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_FAST_ACTION);
        return actionGroup;
    }
};

class ReverseCommand final
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);
        return actionGroup;
    }
};

class TurnRoundCommand final
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    {
        if (poseHandler.IsReverse())
        {
            // 倒车状态下不动
            return ActionGroup();
        }
        else
        { // 返回倒车的指令值集对象
            if (poseHandler.IsFast())
            {
                return ActionGroup({
                    ActionType::FORWARD_1_STEP_ACTION,
                    ActionType::TURNLEFT_ACTION,
                    ActionType::FORWARD_1_STEP_ACTION,
                    ActionType::TURNLEFT_ACTION,
                });
            }
            else
            {
                return ActionGroup({
                    ActionType::TURNLEFT_ACTION,
                    ActionType::FORWARD_1_STEP_ACTION,
                    ActionType::TURNLEFT_ACTION,
                });
            }
        }
    }
};
} // namespace adas