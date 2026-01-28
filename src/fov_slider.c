#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"

typedef struct {
    s32 unk0;
    void *transistion_info;
    u8 state;
    void *model_ptr;
    f32 rotation;
    f32 timer;
    void *anctrl;
    s32 substate;
} TransitionInfo;

extern TransitionInfo s_current_transition;

RECOMP_HOOK ("func_80295C14") void OnPlayerUpdate(void) { 
    if (s_current_transition.model_ptr == assetcache_get(ASSET_467_MODEL_TRANSITION_FALLING_JIGGIES) || 
        getGameMode() != GAME_MODE_3_NORMAL && 
        getGameMode() != GAME_MODE_4_PAUSED || 
        level_get() == LEVEL_D_CUTSCENE ||
        map_get() == MAP_91_FILE_SELECT) {
			viewport_setFOVy(40);
        } else {
            viewport_setFOVy(recomp_get_config_double("number_option"));
        }
}
