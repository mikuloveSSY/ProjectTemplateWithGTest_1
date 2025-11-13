#pragma once

#include <functional>
#include <list>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{
// 使用using来简化定义名称（功能类似于typedef）
using Cmder = std::function<void(PoseHandler &posHandler)>;
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
    // 将命令转化成一系列的操作构成的顺序链表
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
    std::unordered_map<char, Cmder> cmderMap{
        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()},
    };
};
} // namespace adas