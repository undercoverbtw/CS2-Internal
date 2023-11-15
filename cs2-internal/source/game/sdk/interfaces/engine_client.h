#pragma once

namespace sdk {
    class EngineClient {
    public:
        std::int32_t get_max_clients() {
            return call_virtual<31, std::int32_t>(this);
        }

        bool is_in_game() {
            return call_virtual<32, bool>(this);
        }

        bool is_connected() {
            return call_virtual<33, bool>(this);
        }

		// return CBaseHandle index
		int GetLocalPlayer()
		{
			int nIndex = -1;

			call_virtual<44, void>(this, std::ref(nIndex), 0);

			return nIndex + 1;
		}

		[[nodiscard]] const char* GetLevelName()
		{
			return call_virtual<53, const char*>(this);
		}

		[[nodiscard]] const char* GetLevelNameShort()
		{
			return call_virtual<54, const char*>(this);
		}

		[[nodiscard]] const char* GetProductVersionString()
		{
			return call_virtual<77, const char*>(this);
		}
    };
}