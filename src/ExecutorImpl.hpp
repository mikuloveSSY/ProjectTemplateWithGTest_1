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
  bool isfast{false}; //(c++11)非静态成员初始化

private:
  // 私有函数
  void Move(void) noexcept;
  void TurnLeft(void) noexcept;
  void TurnRight(void) noexcept;
  void Fast(void) noexcept;
  bool IsFast(void) const noexcept;

private:
  // 下面三个类虽然是把执行动作封装了，但还是有执行动作的函数接口重复，所以这个类的目的就是把调用这三个类的执行动作的‘接口’抽象化从而达到多态运行
  class ICommand {
  public:
    // 析构函数也要虚，因为多态运行时，析构执行时的对象也是多态类型的
    virtual ~ICommand() noexcept = default;
    virtual void DoOperate(ExecutorImpl &executor) const noexcept = 0; // 纯虚
  };

private:
  // 私有嵌套类，作用域在外部类内，但是两者是相对独立的，不能互通访问
  // 只有遇到外部类的静态成员时，由于静态成员是独立于对象的类本身，而嵌套类的作用域又在外部类内，所以可以访问
  class MoveCommand final : public ICommand { // 嵌套类
  public:
    // 执行Move动作，委托给一个执行器来完成动作(override表示强制重写虚函数)
    void DoOperate(ExecutorImpl &executor) const noexcept override {
      if (executor.isfast) {
        executor.Move();
      }
      executor.Move();
    }
  };
  class TurnLeftCommand final : public ICommand {
  public:
    void DoOperate(ExecutorImpl &executor) const noexcept override {
      if (executor.isfast) {
        executor.Move();
      }
      executor.TurnLeft();
    }
  };
  class TurnRightCommand final : public ICommand {
  public:
    void DoOperate(ExecutorImpl &executor) const noexcept override {
      if (executor.isfast) {
        executor.Move();
      }
      executor.TurnRight();
    }
  };
};

} // namespace adas