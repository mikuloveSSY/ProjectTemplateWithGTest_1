#include "Executor.hpp"
#include "PoseEq.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace adas
{
// 根据正交分解，并忽略方向的影响（因为与车辆的朝向无关），可以发现只要测试FM.FL.FR.FFM这四种情况（FFL与FFR省略，因为只要FFM能说明可以取消F状态即可）
TEST(ExecutorFastTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E)
{
    // 智能指针方便自动管理
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    executor->Execute("FM"); // FM: F状态下Move

    const Pose target{2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}
// FL
TEST(ExecutorFastTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    executor->Execute("FL");
    const Pose target{1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}
// FR
TEST(ExecutorFastTest, should_return_S_and_x_plus_1_given_status_is_fast_given_command_is_R_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    executor->Execute("FR");
    const Pose target{1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}
// FFM
TEST(ExecutorFastTest, should_return_y_plus_1_given_command_is_FFM_and_facing_is_N)
{
    // 默认起始状态是{0,0,'N'}
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->Execute("FFM"); // FFM等价于M
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}
} // namespace adas