#pragma once
#include "sdk/sdk.h"

namespace interfaces {
    bool initialize();

    void* get_interface_impl(fnv1a::Hash hash);

    template <class T>
    __forceinline constexpr T* get_interface() {
        return static_cast<T*>(get_interface_impl(fnv1a::fnv_hash_type<T>()));
    }

    template <class T>
    __forceinline constexpr T* get() {
        return get_interface<T>();
    }
}
