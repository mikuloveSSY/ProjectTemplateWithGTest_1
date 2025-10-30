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
  void Move(void) noexcept;
  void TurnLeft(void) noexcept;
  void TurnRight(void) noexcept;
};

} // namespace adas