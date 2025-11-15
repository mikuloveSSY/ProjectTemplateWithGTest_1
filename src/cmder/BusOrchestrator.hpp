#pragma once
#include "NormalOrchestrator.hpp"

namespace adas
{
class BusOrchestrator : public NormalOrchestrator
{
  public:
    ActionGroup Move(const PoseHandler &poseHandler) const noexcept override
    {
        ActionGroup actionGroup;
        actionGroup += OnFast(poseHandler);
        actionGroup.PushAction(GetStepAction(poseHandler));
        return actionGroup;
    }

    ActionGroup TurnLeft(const PoseHandler &poseHandler) const noexcept override
    {
        ActionGroup actionGroup;
        actionGroup += OnFast(poseHandler);
        actionGroup.PushAction(GetStepAction(poseHandler));
        const auto action = poseHandler.IsReverse() ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION;
        actionGroup.PushAction(action);
        return actionGroup;
    }

    ActionGroup TurnRight(const PoseHandler &poseHandler) const noexcept override
    {
        ActionGroup actionGroup;
        actionGroup += OnFast(poseHandler);
        actionGroup.PushAction(GetStepAction(poseHandler));
        const auto action =
            poseHandler.IsReverse() ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION;
        actionGroup.PushAction(action);
        return actionGroup;
    }
};

} // namespace adas