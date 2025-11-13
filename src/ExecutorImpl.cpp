#include "ExecutorImpl.hpp"
// #include "Command.hpp"
#include "cmder\CmderFactory.hpp"
#include "core\Singleton.hpp"
#include <algorithm> //要用for_each函数
// #include <memory>
// #include <new>
// #include <unordered_map>

namespace adas
{
// 构造函数
ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : poseHandler(pose)
{
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}

/*
std::nothrow是标准库里的一个常量，用于指示分配内存时不抛出异常
它是std::nothrow_t类型的实例
比如内存分配器分配失败时不再抛出异常，而是返回一个空指针
*/
Executor *Executor::NewExecutor(const Pose &pose) noexcept
{
    // （c++17）创建一个对象，若内存不足，返回空指针
    return new (std::nothrow) ExecutorImpl(pose);
}

void ExecutorImpl::Execute(const std::string &commands) noexcept
{
    // 获取操作顺序链表
    const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);
    // lambda表达式，对于链表遍历到的每一个元素，执行该表达式
    // 这样每一个字符对应的操作都对posHandler执行了
    std::for_each(cmders.begin(), cmders.end(),
                  // 注意，为了表达式里能访问ExecutorIml类的成员，要捕获外部的this指针
                  [this](const Cmder &cmder) noexcept { cmder(poseHandler).DoOperate(poseHandler); });
}

} // namespace adas