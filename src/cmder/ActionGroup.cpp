#include "ActionGroup.hpp"
#include "CmderFactory.hpp"

#include <algorithm>
#include <vector>

namespace adas
{
class ForwardAction final
{
  public:
    void operator()(PoseHandler &posHandler) const noexcept
    {
        posHandler.Forward();
    }
};

class BackwardAction final
{
  public:
    void operator()(PoseHandler &posHandler) const noexcept
    {
        posHandler.Backward();
    }
};

class TurnLeftAction final
{
  public:
    void operator()(PoseHandler &posHandler) const noexcept
    {
        posHandler.TurnLeft();
    }
};

class ReverseTurnLeftAction final
{
  public:
    void operator()(PoseHandler &posHandler) const noexcept
    {
        posHandler.TurnRight();
    }
};

class TurnRightAction final
{
  public:
    void operator()(PoseHandler &posHandler) const noexcept
    {
        posHandler.TurnRight();
    }
};

class ReverseTurnRightAction final
{
  public:
    void operator()(PoseHandler &posHandler) const noexcept
    {
        posHandler.TurnLeft();
    }
};

class BeReverseAction final
{
  public:
    void operator()(PoseHandler &posHandler) const noexcept
    {
        posHandler.Reverse();
    }
};

class BeFastAction final
{
  public:
    void operator()(PoseHandler &posHandler) const noexcept
    {
        posHandler.Fast();
    }
};

ActionGroup::ActionGroup(const std::list<ActionType> &actions) noexcept : actions(actions)
{
}

void ActionGroup::PushAction(const ActionType ActionType) noexcept
{
    actions.push_back(ActionType);
}

void ActionGroup::DoOperate(PoseHandler &poseHandler) const noexcept
{
    static std::vector<std::function<void(PoseHandler & poseHandler)>> actionVec = {
        ForwardAction(),   BackwardAction(),         TurnLeftAction(), ReverseTurnLeftAction(),
        TurnRightAction(), ReverseTurnRightAction(), BeFastAction(),   BeReverseAction(),
    };
    std::for_each(actions.begin(), actions.end(), [&poseHandler](const ActionType ActionType) mutable noexcept {
        // 根据对应的指令值，执行对应操作
        actionVec[static_cast<uint16_t>(ActionType)](poseHandler);
    });
}

} // namespace adas