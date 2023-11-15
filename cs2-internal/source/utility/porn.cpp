#include "porn.h"

#include <Windows.h>
#include <winternl.h>


PIMAGE_NT_HEADERS get_nt_headers(const std::uintptr_t module_base) {
    const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_base);

    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
        return nullptr;

    const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(module_base + dos_header->e_lfanew);

    if (nt_headers->Signature != IMAGE_NT_SIGNATURE)
        return nullptr;

    return nt_headers;
}

std::optional<std::vector<porn::ModuleInfo>> porn::get_loaded_modules() {
#ifdef _WIN64
    const auto peb = reinterpret_cast<PPEB>(__readgsqword(0x60));
#else
    const auto peb = reinterpret_cast<PPEB>(__readfsdword(0x30));
#endif

    if (peb == nullptr)
        return std::nullopt;

    const PLIST_ENTRY head = &peb->Ldr->InMemoryOrderModuleList;

    std::vector<ModuleInfo> modules;

    for (auto current = head->Flink; current != head; current = current->Flink) {
        const auto entry = CONTAINING_RECORD(current, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        if (entry->FullDllName.Buffer == nullptr)
            continue;

        const auto module_base = reinterpret_cast<std::uintptr_t>(entry->DllBase);

        const PIMAGE_NT_HEADERS nt_headers = get_nt_headers(module_base);

        if (nt_headers == nullptr)
            continue;

        const auto module_path = std::wstring(entry->FullDllName.Buffer);

        if (const std::size_t module_name_begin = module_path.find_last_of('\\'); module_name_begin != std::wstring::npos) {
            const std::wstring module_name = module_path.substr(module_name_begin + 1);

            const ModuleInfo info = {
                .name = module_name,
                .base = module_base,
                .size = nt_headers->OptionalHeader.SizeOfImage
            };

            modules.push_back(info);
        }
    }

    return modules;
}

std::optional<porn::ModuleInfo> porn::get_module_by_name(const std::wstring_view module_name) {
    static const auto modules = get_loaded_modules();

    if (!modules)
        return std::nullopt;

    const auto it = std::ranges::find_if(*modules, [&module_name](const porn::ModuleInfo& module) {
        return module.name == module_name;
        });

    if (it != modules->end())
        return *it;

    return std::nullopt;
}
