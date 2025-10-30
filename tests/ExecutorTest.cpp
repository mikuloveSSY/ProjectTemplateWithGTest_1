#include <gtest/gtest.h> //提供googletest测试框架

#include <memory>
#include <tuple>

#include "Executor.hpp"

namespace adas {
// 重载Pose的==
bool operator==(const Pose &lhs, const Pose &rhs) {
  // tie用于创建元组接受多值进行比较，按照字段顺序逐个比较
  return std::tie(lhs.x, lhs.y, lhs.heading) ==
         std::tie(rhs.x, rhs.y, rhs.heading);
}
// TEST是一个宏，包括两个参数：测试套件，测试名（注意不是字符串，不需要""），一个测试套件可以包括多个测试
//  下面两个测试用例
//  1
TEST(ExecutorTest, should_return_init_pose_when_without_command) {
  // 这里给出初始姿态
  // unique_ptr就是智能指针，这样不需要手动去delete了
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
  // 构造一个姿势对象
  const Pose target({0, 0, 'E'});
  // 理论上，这么设置后，executor->Queury()返回的应该与target相同，从而可以判断executor对象的实现有无问题
  // ASSERT_EQ 是 GoogleTest框架中的一个断言宏
  // 用于在测试中验证两个值是否相等。如果两个值不相等，测试将立即终止，并标记为失败。
  ASSERT_EQ(target, executor->Query());
}
// 2
// 与1是同个测试套件里的
TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor());
  const Pose target({0, 0, 'N'});
  ASSERT_EQ(target, executor->Query());
}
// 3.1 M
TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
  // 调用executor的Execute方法执行指令
  executor->Execute("M");
  // 标准结果
  const Pose target({1, 0, 'E'});
  ASSERT_EQ(target, executor->Query());
}
// 3.2 M
TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));
  executor->Execute("M");
  const Pose target({-1, 0, 'W'});
  ASSERT_EQ(target, executor->Query());
}
// 3.3 M
TEST(ExecutorTest, should_return_y_plus_1_given_command_is_M_and_facing_is_N) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
  executor->Execute("M");
  const Pose target({0, 1, 'N'});
  ASSERT_EQ(target, executor->Query());
}
// 3.4 M
TEST(ExecutorTest, should_return_y_minus_1_given_command_is_M_and_facing_is_S) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));
  executor->Execute("M");
  const Pose target({0, -1, 'S'});
  ASSERT_EQ(target, executor->Query());
}
// 3.5 L
TEST(ExecutorTest, should_return_facing_N_given_command_is_L_and_facing_is_E) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
  executor->Execute("L");
  const Pose target({0, 0, 'N'});
  ASSERT_EQ(target, executor->Query());
}
// 3.6 L
TEST(ExecutorTest, should_return_facing_W_given_command_is_L_and_facing_is_N) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
  executor->Execute("L");
  const Pose target({0, 0, 'W'});
  ASSERT_EQ(target, executor->Query());
}
// 3.7 L
TEST(ExecutorTest, should_return_facing_S_given_command_is_L_and_facing_is_W) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));
  executor->Execute("L");
  const Pose target({0, 0, 'S'});
  ASSERT_EQ(target, executor->Query());
}
// 3.8 L
TEST(ExecutorTest, should_return_facing_E_given_command_is_L_and_facing_is_S) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));
  executor->Execute("L");
  const Pose target({0, 0, 'E'});
  ASSERT_EQ(target, executor->Query());
}
// 3.9 R
TEST(ExecutorTest, should_return_facing_S_given_command_is_R_and_facing_is_E) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
  executor->Execute("R");
  const Pose target({0, 0, 'S'});
  ASSERT_EQ(target, executor->Query());
}
// 3.10 R
TEST(ExecutorTest, should_return_facing_W_given_command_is_R_and_facing_is_S) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));
  executor->Execute("R");
  const Pose target({0, 0, 'W'});
  ASSERT_EQ(target, executor->Query());
}
// 3.11 R
TEST(ExecutorTest, should_return_facing_N_given_command_is_R_and_facing_is_W) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));
  executor->Execute("R");
  const Pose target({0, 0, 'N'});
  ASSERT_EQ(target, executor->Query());
}
// 3.12 R
TEST(ExecutorTest, should_return_facing_E_given_command_is_R_and_facing_is_N) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
  executor->Execute("R");
  const Pose target({0, 0, 'E'});
  ASSERT_EQ(target, executor->Query());
}
} // namespace adas

/*tips:
在最早构建工程代码的时候
虽然还没给出Executor的子类实现，但是先写好测试用例代码
这是业界强调的“测试驱动开发”
*/