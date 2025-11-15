#pragma once
#include "..\core\PoseHandler.hpp"
#include "CmderOrchestrator.hpp"
#include <functional> // functional提供函数包装器

namespace adas
{

// 现在src\cmder\Command.hpp的里面的各种Command类不再直接依赖ActionGroup了，而是依赖CmderOrchestrator适配器
class MoveCommand final
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        return orchestrator.Move(poseHandler);
    }
};

class TurnLeftCommand final
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        return orchestrator.TurnLeft(poseHandler);
    }
};

class TurnRightCommand final //: public ICommand
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        return orchestrator.TurnRight(poseHandler);
    }
};

class FastCommand final //: public ICommand
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_FAST_ACTION);
        return actionGroup;
    }
};

class ReverseCommand final
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);
        return actionGroup;
    }
};

class TurnRoundCommand final
{
  public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        return orchestrator.TurnRound(poseHandler);
    }
};

} // namespace adas