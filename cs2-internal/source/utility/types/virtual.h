#pragma once

#include <algorithm>

template <std::size_t Index, typename ReturnType, typename... Args>
__forceinline ReturnType call_virtual(void* base_class, Args... args) {
    using Fn = ReturnType(__thiscall*)(void*, decltype(args)...);

    const auto fn = (*static_cast<Fn**>(base_class))[Index];

    return fn(base_class, args...);
}