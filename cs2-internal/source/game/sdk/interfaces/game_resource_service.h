#pragma once

namespace sdk {
    class CGameEntitySystem;

    class GameResourceService {
    public:
        std::uint8_t pad[0x58];
        CGameEntitySystem* pGameEntitySystem;
    };
}





