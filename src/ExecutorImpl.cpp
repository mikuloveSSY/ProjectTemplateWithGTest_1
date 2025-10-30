#include "ExecutorImpl.hpp"
#include <memory>
#include <new>

namespace adas {

// 由于头文件里只有声明，所以这里要类外定义构造函数
ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept
    : pose(pose), isFast(false) {}
Pose ExecutorImpl::Query(void) const noexcept { return pose; }

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
    // 用上类后，每一句都有cmder->DoOperate(*this); 已经接近多态了
    if (cmd == 'M') {
      // 利用智能指针来创建并使用智能指针来管理，利于避免内存泄漏
      std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();
      // 通过内部类的智能指针调用内部类的函数
      cmder->DoOperate(*this);
    } else if (cmd == 'L') {
      std::unique_ptr<TurnLeftCommand> cmder =
          std::make_unique<TurnLeftCommand>();
      cmder->DoOperate(*this);
    } else if (cmd == 'R') {
      std::unique_ptr<TurnRightCommand> cmder =
          std::make_unique<TurnRightCommand>();
      cmder->DoOperate(*this);
    } else if (cmd == 'F') {
      isFast = !isFast;
    }
  }
}

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