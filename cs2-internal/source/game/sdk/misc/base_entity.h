#pragma once

namespace sdk {
    class BaseEntity {
    public:
        std::uint8_t get_team_num() {
            return *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint64_t>(this) + schemas::get_offset("C_BaseEntity->m_iTeamNum"));
        }

        std::uint32_t get_flags() {
            return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint64_t>(this) + schemas::get_offset("C_BaseEntity->m_fFlags"));
        }

        std::uint32_t get_health() {
            return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint64_t>(this) + schemas::get_offset("C_BaseEntity->m_iHealth"));
        }
    };
}