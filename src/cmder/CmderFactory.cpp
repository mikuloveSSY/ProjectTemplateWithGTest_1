#include "CmderFactory.hpp"

namespace adas
{
CmderList CmderFactory::GetCmders(const std::string &commands) const noexcept
{
    CmderList list;
    for (auto i : ParseCommandString(commands))
    {
        auto cmd = cmderMap.find(i);
        if (cmd != cmderMap.end())
        {
            list.push_back(cmd->second);
        }
    }
    return list;
}
std::string CmderFactory::ParseCommandString(std::string_view commands) const noexcept
{
    std::string result(commands);
    ReplaceAll(result, "TR", "Z");
    return result;
}
// 将“TR”替换成“Z”
void CmderFactory::ReplaceAll(std::string &inout, std::string_view what, std::string_view with) const noexcept
{
    for (std::string::size_type pos{}; inout.npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length())
    {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
}

} // namespace adas