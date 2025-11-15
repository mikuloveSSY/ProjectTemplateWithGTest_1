#pragma once
#include "Executor.hpp"
#include "cmder/CmderOrchestrator.hpp" //因为要按照车的类型让ExecutorImpl确定适配器，所以要引入
#include "core/PoseHandler.hpp"
#include <memory>
#include <string>

namespace adas
{

// Executor的具体实现（Impl全称就是Implementation，即“实现”）,这里的final关键字表示该类不能被继承
class ExecutorImpl final : public Executor
{
  public:
    // 构造函数声明（带explicit是让编译器不能隐式转换参数去调用构造函数）
    explicit ExecutorImpl(const Pose &pose, CmderOrchestrator *orchestrator) noexcept;
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
    PoseHandler poseHandler;                         // 状态管理类
    std::unique_ptr<CmderOrchestrator> orchestrator; // 车类型适配器（基类指针指向子类，从而达成多态性）
};

} // namespace adas