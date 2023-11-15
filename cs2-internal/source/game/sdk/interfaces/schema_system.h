#pragma once

namespace sdk {
    class SchemaClassBinding {
    public:
        SchemaClassBinding* parent;
        const char* binary_name;
        const char* module_name;
    };

    class SchemaClassFieldData {
    public:
        const char* name;
        std::uint8_t padding_0[0x8];
        std::uint16_t offset;
        std::uint8_t padding_1[0xE];
    };

    class SchemaTypeDeclaredClass {
    public:
        std::uint16_t get_fields_count() {
            return *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1C);
        }

        SchemaClassFieldData* get_fields() {
            return *reinterpret_cast<SchemaClassFieldData**>(reinterpret_cast<std::uint64_t>(this) + 0x28);
        }
    };

    class SchemaSystemTypeScope {
    public:
        SchemaTypeDeclaredClass* find_declared_class(const char* class_name) {
            return call_virtual<5, SchemaTypeDeclaredClass*>(this, class_name);
        }

    public:
        std::uint8_t padding_0[0x8];
        char name[256];
        std::uint8_t padding_1[0x450];
        UtlTSHash<SchemaClassBinding*> classes;
    };

    class SchemaSystem {
    public:
        SchemaSystemTypeScope* find_type_scope_for_module(const char* module_name) {
            return call_virtual<13, SchemaSystemTypeScope*>(this, module_name);
        }

    public:
        std::uint8_t padding_0[0x190];
        UtlVector<SchemaSystemTypeScope*> type_scopes;
    };
}