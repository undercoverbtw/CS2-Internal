#pragma once

#include <cstddef>
#include <cstdint>

class Address {
public:
    Address() = default;

    explicit Address(const std::uintptr_t address) : address_(address) {}
    explicit Address(void* address) : Address(reinterpret_cast<std::uintptr_t>(address)) {}
    explicit Address(const void* address) : Address(reinterpret_cast<std::uintptr_t>(address)) {}

    [[nodiscard]] __forceinline Address abs(const std::size_t length = 7) const {
        std::uintptr_t base = address_;

        const auto displacement = *reinterpret_cast<std::int32_t*>(base + 0x3);

        base += displacement;
        base += length;

        return Address(base);
    }

    [[nodiscard]] __forceinline Address add(const std::ptrdiff_t value) const {
        return Address(address_ + value);
    }

    [[nodiscard]] __forceinline std::uintptr_t address() const {
        return address_;
    }

    template <typename T = Address>
    __forceinline T find_opcode(const std::uint8_t opcode, const std::ptrdiff_t offset = 0x0) const {
        std::uintptr_t base = address_;

        while (true) {
            if (*reinterpret_cast<std::uint8_t*>(base) == opcode)
                break;

            base += 0x1;
        }

        base += offset;

        return T(base);
    }

    template <typename T = Address>
    __forceinline T get(const std::size_t times = 1) const {
        std::uintptr_t result = address_;

        for (std::size_t i = 0; i < times; ++i)
            result = *reinterpret_cast<std::uintptr_t*>(result);

        return T(result);
    }

    [[nodiscard]] __forceinline bool is_valid() const {
        return address_ > static_cast<std::uintptr_t>(0x1000)
            && address_ < static_cast<std::uintptr_t>(sizeof(void*) == 4 ? 0x7FFEFFFF : 0x7FFFFFFEFFFF);
    }

    [[nodiscard]] __forceinline Address jmp(const std::ptrdiff_t offset = 0x1) const {
        std::uintptr_t base = address_ + offset;

        const auto displacement = *reinterpret_cast<std::int32_t*>(base);

        base += displacement;
        base += sizeof(std::uint32_t);

        return Address(base);
    }

    [[nodiscard]] __forceinline Address sub(const std::ptrdiff_t value) const {
        return Address(address_ - value);
    }

    template <typename T>
    __forceinline T as() const {
        return reinterpret_cast<T>(address_);
    }

    __forceinline explicit operator bool() const {
        return is_valid();
    }

private:
    std::uintptr_t address_{ 0 };
};