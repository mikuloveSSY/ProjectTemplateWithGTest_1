#pragma once
#include <string>

#include "Executor.hpp"

namespace adas {

// Executor的具体实现（Impl全称就是Implementation，即“实现”）,这里的final关键字表示该类不能被继承
class ExecutorImpl final : public Executor {
public:
  // 构造函数（带explicit是让编译器不能隐式转换参数去调用构造函数）
  explicit ExecutorImpl(const Pose &pose) noexcept;
  // 让编译器默认析构函数
  ~ExecutorImpl() noexcept = default;
  // 不能拷贝
  ExecutorImpl(const ExecutorImpl &) = delete;
  // 不能赋值
  ExecutorImpl &operator=(const ExecutorImpl &) = delete;

public:
  // 查询当前汽车姿态
  // override是用于显式地标记派生类中重写基类虚函数的函数，增加易读性，且便于编译器的识别
  Pose Query(void) const noexcept override;
  // 第二阶段新增纯虚函数，用于执行指令
  void Execute(const std::string &command) noexcept override;

private:
  // 私有成员
  Pose pose;
  bool isFast;

private:
  // 私有函数
  void Move(void) noexcept;
  void TurnLeft(void) noexcept;
  void TurnRight(void) noexcept;

  // 把执行动作封装到类里是为了后面的多态运行，不用重复得调用同几个语句了
private:
  // 私有内部类，只能靠内部的函数或者指针来创建并调用
  class MoveCommand final { // 嵌套类
  public:
    // 执行Move动作，委托给一个执行器来完成动作
    void DoOperate(ExecutorImpl &executor) const noexcept { executor.Move(); }
  };
  class TurnLeftCommand final {
  public:
    void DoOperate(ExecutorImpl &executor) const noexcept {
      executor.TurnLeft();
    }
  };
  class TurnRightCommand final {
  public:
    void DoOperate(ExecutorImpl &executor) const noexcept {
      executor.TurnRight();
    }
  };
};

} // namespace adas