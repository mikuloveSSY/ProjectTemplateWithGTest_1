#pragma once

#include <functional>
#include <list>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{
// 使用using来简化定义名称（功能类似于typedef）
using Cmder = std::function<ActionGroup(PoseHandler &poseHandler)>;
using CmderList = std::list<Cmder>;
// 该类将被用于单例模式
class CmderFactory final
{
  public:
    // 删除构造函数与析构函数，防止生成多个实例
    CmderFactory(void) = default;
    ~CmderFactory(void) = default;
    CmderFactory(const CmderFactory &) = delete;
    CmderFactory &operator=(const CmderFactory &) = delete;

  public:
    // 将命令这种字符串转化成一系列的由操作的GroupAction执行对象构成的顺序链表，再由这些对象各自完成自己对应的具体操作
    CmderList GetCmders(const std::string &commands) const noexcept
    {
        CmderList list;
        for (auto i : commands)
        {
            auto cmd = cmderMap.find(i);
            if (cmd != cmderMap.end())
            {
                list.push_back(cmd->second);
            }
        }
        return list;
    }

  private:
    // 注意，原先map里的存储的值对应的是直接的操作函数，现在这些值则是对应生成的ActionGroup对象
    std::unordered_map<char, Cmder> cmderMap{
        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()},
    };
};
} // namespace adas