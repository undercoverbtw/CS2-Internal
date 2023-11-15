#pragma once

#include "../utility/types/fnv1a.h"

namespace schemas {
    bool initialize();

    std::uint16_t get_offset_impl(fnv1a::Hash hash);

    template <std::size_t N>
    __forceinline constexpr std::uint16_t get_offset(const char(&name)[N]) {
        return get_offset_impl(fnv1a::fnv_hash_const(name));
    }
}