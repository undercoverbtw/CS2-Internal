#pragma once

#include <unordered_map>

namespace sdk {
    class ConVar {
    public:
        const char* name;
        std::uint8_t padding_0[0x4];
        std::uint64_t flags;
    };

    class CVar {
    public:
        std::uint64_t* get_first_cvar_iterator(std::uint64_t& index) {
            return call_virtual<12, std::uint64_t*>(this, &index);
        }

        std::uint64_t* get_next_cvar_iterator(std::uint64_t& index) {
            return call_virtual<13, std::uint64_t*>(this, &index, index);
        }

        ConVar* find_var_by_index(const std::uint16_t index) {
            return call_virtual<37, ConVar*>(this, index);
        }

        ConVar* find_var_by_name(const std::string_view name) {
            std::uint64_t i = 0;

            get_first_cvar_iterator(i);

            while (i != 0xFFFFFFFF) {
                ConVar* cvar = find_var_by_index(i);

                if (cvar == nullptr)
                    break;

                if (strcmp(cvar->name, name.data()) == 0)
                    return cvar;

                get_next_cvar_iterator(i);
            }

            return nullptr;
        }

    private:
        std::unordered_map<std::string, ConVar*> cvar_map_;
    };
}