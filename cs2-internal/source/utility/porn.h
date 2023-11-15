#pragma once

#include <optional>
#include <string>
#include <vector>

namespace porn {

    struct ModuleInfo {
        std::wstring name;
        std::uintptr_t base;
        std::uint32_t size;
    };

    std::optional<std::vector<ModuleInfo>> get_loaded_modules();

    std::optional<ModuleInfo> get_module_by_name(std::wstring_view module_name);
}