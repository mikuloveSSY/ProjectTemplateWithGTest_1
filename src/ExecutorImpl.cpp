#include "ExecutorImpl.hpp"
#include <new>

namespace adas {

ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose) {}
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
void ExecutorImpl::Execute(const std::string &command) noexcept {}
} // namespace adas