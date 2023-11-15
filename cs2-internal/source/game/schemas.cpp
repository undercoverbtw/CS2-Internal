#include "schemas.h"
#include "interfaces.h"
#include "sdk/sdk.h"

namespace schemas {
    std::unordered_map<fnv1a::Hash, std::uint16_t> schema_map;

    bool initialize() {

        const auto type_scopes = interfaces::get<sdk::SchemaSystem>()->type_scopes;

        for (std::int32_t i = 0; i < type_scopes.get_size(); ++i) {
            if (sdk::SchemaSystemTypeScope* current = type_scopes.get_element(i); current != nullptr) {
                for (const auto& class_binding : current->classes.get_elements()) {
                    if (class_binding == nullptr)
                        continue;

                    sdk::SchemaTypeDeclaredClass* class_info = current->find_declared_class(class_binding->binary_name);

                    if (class_info == nullptr)
                        continue;

                    sdk::SchemaClassFieldData* fields = class_info->get_fields();

                    if (fields == nullptr)
                        continue;

                    const std::uint16_t fields_count = class_info->get_fields_count();

                    for (std::uint16_t j = 0; j < fields_count; ++j) {
                        sdk::SchemaClassFieldData* field = &fields[j];

                        if (field == nullptr)
                            continue;

                        std::string key = class_binding->binary_name;

                        key += "->";
                        key += field->name;

                        schema_map.emplace(fnv1a::fnv_hash(key.c_str()), field->offset);
                    }
                }
            }
        }

        return !schema_map.empty();
    }

    std::uint16_t get_offset_impl(const fnv1a::Hash hash) {
        return schema_map[hash];
    }
}