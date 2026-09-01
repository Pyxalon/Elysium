#pragma once
#include "BaseObj.hpp"

namespace Elysium
{
    class Folder final : public BaseObj
    {
    public:
        Folder(const std::filesystem::path& folder);

    };
}
