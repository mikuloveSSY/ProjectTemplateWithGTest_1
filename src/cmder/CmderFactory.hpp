#pragma once

#include <functional>
#include <list>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{
// 使用using来简化定义名称（功能类似于typedef）
using Cmder = std::function<ActionGroup(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator)>;
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
    CmderList GetCmders(const std::string &commands) const noexcept;

  private:
    // string_view表示该类型不会为数据分配存储空间，而且该数据类型只能用来读。
    std::string ParseCommandString(std::string_view commands) const noexcept;
    void ReplaceAll(std::string &inout, std::string_view what, std::string_view with) const noexcept;

  private:
    // 注意，表面上mao的值是对象，但实际上创建完对象后，这些Command对象被隐转换成了里面的成员函数（参考自定义的Cmder类型），所以最终map的值存的是各自的成员函数
    std::unordered_map<char, Cmder> cmderMap{
        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()},  {'Z', TurnRoundCommand()},
    };
};
} // namespace adas