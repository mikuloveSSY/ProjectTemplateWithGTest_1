#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <memory>
#include <new>
#include <unordered_map>

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
    // 表驱动
    std::unordered_map<char, std::function<void(PoseHandler & PoseHandler)>> cmderMap{
        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()},
    };
    // 建立操作与指令的映射关系,智能指针的值就存储在键值对里
    // cmderMap.emplace('M', MoveCommand());
    // cmderMap.emplace('L', TurnLeftCommand());
    // cmderMap.emplace('R', TurnRightCommand());
    // cmderMap.emplace('F', FastCommand());
    // cmderMap.emplace('B', std::make_unique<ReverseCommand>());
    // 解析字符串，执行指令
    for (const auto cmd : commands)
    {
        // find返回该键值对（即map元素的迭代器）
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end())
        {
            it->second(poseHandler);
        }
    }
}

} // namespace adas