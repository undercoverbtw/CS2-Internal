#pragma once

#include "types/adress.h"

#include <optional>
#include <string_view>

namespace memory {
    Address find_pattern(std::wstring_view module_name, std::string_view pattern);
}