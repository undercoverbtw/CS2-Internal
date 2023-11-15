#pragma once
#include <cstdint>

namespace sdk {
    class CSGOInput {
    public:
        static UserCmd* get_user_cmd(sdk::CSGOInput* input, const std::int32_t slot) {
            const auto sequence_number = *reinterpret_cast<std::uint32_t*>(
                0x4350 * slot + reinterpret_cast<std::uint64_t>(input) + 0x4414
            );

            const auto v1 = reinterpret_cast<std::uint64_t>(input) + 0x70 * (sequence_number % 150);
            const auto v2 = v1 + 0x4350 * slot + 0x250;

            return reinterpret_cast<UserCmd*>(v2);
        }
    };
}