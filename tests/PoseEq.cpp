#include "PoseEq.hpp"
#include "Executor.hpp"
#include <tuple>

/*
把重载Pose的==独立出来，从而每个测试文件都能直接通过引用其声明的头文件来使用重载
一般都把声明与实现分开，是为了:
1.避免重复定义：如果在头文件中定义非内联函数，多个源文件包含该头文件会导致重复定义错误。
2.隐藏实现：将定义放在源文件中，只暴露声明在头文件，可以隐藏实现细节，实现接口和实现的分离
*/
namespace adas {
bool operator==(const Pose &lhs, const Pose &rhs) {
  // tie用于创建元组接受多值进行比较，按照字段顺序逐个比较
  return std::tie(lhs.x, lhs.y, lhs.heading) ==
         std::tie(rhs.x, rhs.y, rhs.heading);
}
} // namespace adas
