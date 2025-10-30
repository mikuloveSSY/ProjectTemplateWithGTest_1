#include "ExecutorImpl.hpp"
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
    if (cmd == 'M') {
      Move();
    } else if (cmd == 'L') {
      TurnLeft();
    } else if (cmd == 'R') {
      TurnRight();
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