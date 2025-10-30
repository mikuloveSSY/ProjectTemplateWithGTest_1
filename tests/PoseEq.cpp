#include "PoseEq.hpp"
#include "Executor.hpp"
#include <tuple>

namespace adas {
// 把重载Pose的==独立出来，从而每个测试文件都能共享
bool operator==(const Pose &lhs, const Pose &rhs) {
  // tie用于创建元组接受多值进行比较，按照字段顺序逐个比较
  return std::tie(lhs.x, lhs.y, lhs.heading) ==
         std::tie(rhs.x, rhs.y, rhs.heading);
}
} // namespace adas
