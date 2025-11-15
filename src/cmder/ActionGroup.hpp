#pragma once
#include "..\core\PoseHandler.hpp"
#include <list>

namespace adas
{
// enum class，则该枚举的作用域仅在该类内
enum class ActionType : uint16_t
{
    // 原子操作枚举值
    FORWARD_1_STEP_ACTION = 0,
    BACKWORD_1_STEP_ACTION,
    TURNLEFT_ACTION,
    REVERSE_TURNLEFT_ACTION,
    TURNRIGHT_ACTION,
    REVERSE_TURNRIGHT_ACTION,
    BE_FAST_ACTION,
    BE_REVERSE_ACTION,
};

class ActionGroup final
{
  public:
    ActionGroup(void) = default;
    explicit ActionGroup(const std::list<ActionType> &actions) noexcept;
    ~ActionGroup() = default;
    ActionGroup &operator+=(const ActionGroup &rhs) noexcept
    {
        for (auto i : rhs.actions)
        {
            actions.push_back(i);
        }
        return *this;
    }

  public:
    void PushAction(const ActionType ActionType) noexcept;
    void DoOperate(PoseHandler &poseHandler) const noexcept;

  private:
    std::list<ActionType> actions;
};
} // namespace adas