#pragma once
#include "ActionGroup.hpp"

namespace adas
{
// 移动适配器，用于使移动指令适配不同种类的车
/*
适配器只声明4种抽象方法，前进、左转、右转、调头。具体车型的具体方法如何分解为对应的原子移动，由子类具体实现
注意返回的都是ActionGroup
*/
class CmderOrchestrator
{
  public:
    virtual ~CmderOrchestrator() = default;

  public:
    virtual ActionGroup Move(const PoseHandler &poseHandler) const noexcept = 0;
    virtual ActionGroup TurnLeft(const PoseHandler &poseHandler) const noexcept = 0;
    virtual ActionGroup TurnRight(const PoseHandler &posHandler) const noexcept = 0;
    virtual ActionGroup TurnRound(const PoseHandler &poseHandler) const noexcept = 0;
};
} // namespace adas
