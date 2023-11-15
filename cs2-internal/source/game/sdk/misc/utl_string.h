#pragma once

namespace sdk {
    class UtlString {
    public:
        explicit operator const char* () const {
            return value_;
        }

        [[nodiscard]] const char* get() const {
            return value_;
        }

    public:
        const char* value_;
    };
}