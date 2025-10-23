#pragma once
#include <string>
/*virtual修饰的函数表示虚函数，相当于其在基类中只是一个声明，并没有任何实质上的定义
其真正的实现是在子类（派生类）中
优势：让子类对象在运行时动态地继承和修改父类的成员函数，实现多态运行
另一方面，虚函数的存在也使得Executor成为一个抽象类，无法实例化，其本身也没有任何数据成员
*/
namespace adas {
// 汽车姿态
struct Pose {
  int x;
  int y;
  char heading;
};
// 驾驶动作执行器接口
class Executor {
 public:
  static Executor *NewExecutor(const Pose &pose = {0, 0, 'N'}) noexcept;

 public:
  // 默认构造函数
  Executor(void) = default;
  // 默认虚析构函数
  virtual ~Executor(void) = default;
  // 不能拷贝
  Executor(const Executor &) = delete;
  // 不能赋值
  Executor &operator=(const Executor &) = delete;

 public:
  // 查询当前汽车的姿态，纯虚函数，给子类实现
  virtual Pose Query(void) const noexcept = 0;
};
}  // namespace adas