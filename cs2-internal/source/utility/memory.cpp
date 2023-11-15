#include "memory.h"
#include "porn.h"
#include <string>

#include <charconv>

namespace memory {
    std::vector<std::int32_t> pattern_to_bytes(const std::string_view pattern) {
        std::vector<std::int32_t> bytes;

        for (std::size_t i = 0; i < pattern.size(); ++i) {
            // Skip the current character if it is a space.
            if (pattern[i] == ' ')
                continue;

            // Insert a dummy byte if the current character is a wildcard.
            if (pattern[i] == '?') {
                bytes.push_back(-1);

                continue;
            }

            // Check if there are at least two characters left.
            if (i + 1 < pattern.size()) {
                std::int32_t value = 0;

                // Convert the next two characters to hexadecimal.
                if (const auto [ptr, ec] = std::from_chars(pattern.data() + i, pattern.data() + i + 2, value, 16); ec == std::errc())
                    bytes.push_back(value);

                // Skip the next character.
                ++i;
            }
        }

        return bytes;
    }

    Address find_pattern(const std::wstring_view module_name, const std::string_view pattern) {
        const std::optional<porn::ModuleInfo> module = porn::get_module_by_name(module_name);

        if (!module)
            return {};

        const auto module_data = reinterpret_cast<std::uint8_t*>(module->base);

        const std::vector<std::int32_t> pattern_bytes = pattern_to_bytes(pattern);

        for (std::size_t i = 0; i < module->size - pattern.size(); ++i) {
            bool found = true;

            for (std::size_t j = 0; j < pattern_bytes.size(); ++j) {
                // Check if the current byte does not match the pattern byte and the pattern byte is not a wildcard.
                if (module_data[i + j] != pattern_bytes[j] && pattern_bytes[j] != -1) {
                    found = false;

                    break;
                }
            }

            if (found)
                return Address(reinterpret_cast<std::uintptr_t>(&module_data[i]));
        }

        return {};
    }
}