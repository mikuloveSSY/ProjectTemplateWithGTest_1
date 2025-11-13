#pragma once
namespace adas
{
// 单例模板
// 泛型支持
template <typename T> class Singleton
{
  public:
    // 单例模式
    static T &Instance(void) noexcept
    {
        static T instance;
        return instance;
    }
    // 删除构造方式，确保单例
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

  private:
    Singleton(void) = default;
    ~Singleton(void) = default;
};
} // namespace adas