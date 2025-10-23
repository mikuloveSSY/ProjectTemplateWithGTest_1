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
// 3
TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E) {
  std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
  // 调用executor的Execute方法执行指令
  executor->Execute("M");
  // 标准结果
  const Pose target({1, 0, 'E'});
  ASSERT_EQ(target, executor->Query());
}
} // namespace adas

/*tips:
虽然还没给出Executor的子类实现，但是先写好测试用例代码
这是业界强调的“测试驱动开发”
*/