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

typedef enum {
    TRANSITION_STATE_0_NONE,
    TRANSITION_STATE_1_LOADING,
    TRANSITION_STATE_2_BLACK_IN,
    TRANSITION_STATE_3_BLACK_OUT,
    TRANSITION_STATE_4_FADE_IN,
    TRANSITION_STATE_5_FADE_OUT,
    TRANSITION_STATE_6_LOADING_WHITE,
    TRANSITION_STATE_7_WHITE_IN,
    TRANSITION_STATE_8_WHITE_OUT
} TransitionState;

extern TransitionInfo s_current_transition;

RECOMP_HOOK ("func_80295C14") void OnPlayerUpdate(void) { 

    if (s_current_transition.state == TRANSITION_STATE_4_FADE_IN || s_current_transition.state == TRANSITION_STATE_5_FADE_OUT ||
        getGameMode() != GAME_MODE_3_NORMAL && getGameMode() != GAME_MODE_4_PAUSED ||
        level_get() == LEVEL_D_CUTSCENE ||
        map_get() == MAP_91_FILE_SELECT) {
        viewport_setFOVy(40);
    } else {
        viewport_setFOVy(recomp_get_config_double("number_option"));
    }    
}
