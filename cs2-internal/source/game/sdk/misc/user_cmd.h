#pragma once

#include "base_user_cmd_pb.h"

namespace sdk {
    class UserCmdBase {
    public:
        std::uint8_t padding_0[0x50];
        float forward_move;
        float side_move;
    };

    class UserCmd {
    public:
        std::uint8_t padding_0[0x30];
        UserCmdBase* user_cmd_base;
        std::uint8_t padding_1[0x18];
        std::uint32_t buttons;
    };
}