#pragma once


#pragma once

#include <xorstr.h>
#include <string_view>
#include "../schemas.h"
#include "../../utility/types/fnv1a.h"
#include "../../utility/types/virtual.h"

#include "misc/cs_player_controller.h"
#include "misc/cs_player_pawn.h"
#include "misc/enums.h"
#include "misc/user_cmd.h"
#include "misc/utl_string.h"
#include "misc/utl_ts_hash.h"
#include "misc/utl_vector.h"

#include "interfaces/client_mode_shared.h"
#include "interfaces/csgo_input.h"
#include "interfaces/cvar.h"
#include "interfaces/engine_client.h"
#include "interfaces/game_resource_service.h"
#include "interfaces/localize.h"
#include "interfaces/resource_system.h"
#include "interfaces/schema_system.h"
#include "interfaces/source_2_client.h"