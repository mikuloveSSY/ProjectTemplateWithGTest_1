#include "ExecutorImpl.hpp"
#include <memory>
#include <new>

namespace adas {

// 由于头文件里只有声明，所以这里要类外定义构造函数
ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept
    : pose(pose), isfast(false) {}
Pose ExecutorImpl::Query(void) const noexcept { return pose; }
void ExecutorImpl::Fast(void) noexcept { isfast = !isfast; }
bool ExecutorImpl::IsFast(void) const noexcept { return isfast; }
/*
std::nothrow是标准库里的一个常量，用于指示分配内存时不抛出异常
它是std::nothrow_t类型的实例
比如内存分配器分配失败时不再抛出异常，而是返回一个空指针
*/
Executor *Executor::NewExecutor(const Pose &pose) noexcept {
  // （c++17）创建一个对象，若内存不足，返回空指针
  return new (std::nothrow) ExecutorImpl(pose);
}
void ExecutorImpl::Execute(const std::string &commands) noexcept {
  // 解析字符串，执行指令
  for (const auto cmd : commands) {
    std::unique_ptr<ICommand> cmder;
    // 父类指针指向不同子类，类似于子类隐式转换成父类的样子
    if (cmd == 'M') {
      cmder = std::make_unique<MoveCommand>();
    } else if (cmd == 'L') {
      cmder = std::make_unique<TurnLeftCommand>();
    } else if (cmd == 'R') {
      cmder = std::make_unique<TurnRightCommand>();
    } else if (cmd == 'F') {
      Fast();
    }
    if (cmder) {
      // 多态，cmder作为父类指向不同子类，调用的是各自下的命令
      cmder->DoOperate(*this);
    }
  }
}

// 动作函数
void ExecutorImpl::Move() noexcept {
  if (pose.heading == 'E') {
    ++pose.x;
  } else if (pose.heading == 'W') {
    --pose.x;
  } else if (pose.heading == 'N') {
    ++pose.y;
  } else if (pose.heading == 'S') {
    --pose.y;
  }
}
void ExecutorImpl::TurnLeft() noexcept {
  if (pose.heading == 'E') {
    pose.heading = 'N';
  } else if (pose.heading == 'W') {
    pose.heading = 'S';
  } else if (pose.heading == 'N') {
    pose.heading = 'W';
  } else if (pose.heading == 'S') {
    pose.heading = 'E';
  }
}
void ExecutorImpl::TurnRight() noexcept {
  if (pose.heading == 'E') {
    pose.heading = 'S';
  } else if (pose.heading == 'W') {
    pose.heading = 'N';
  } else if (pose.heading == 'N') {
    pose.heading = 'E';
  } else if (pose.heading == 'S') {
    pose.heading = 'W';
  }
}
} // namespace adas