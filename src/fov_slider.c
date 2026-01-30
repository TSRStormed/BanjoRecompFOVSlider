#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"

typedef struct {
    u8 uid;
    u8 state;
    u8 next_state;
    // u8 pad3[1];
    f32 duration;
    s32 model_index;
    s32 anim_index;
    f32 scale;
}TransitionInfo;

extern struct{
    s32 unk0; //times drawn?
    TransitionInfo *transistion_info;
    u8 state;
    //u8 pad9[3]; //not needed
    void * model_ptr; //asset_ptr
    f32 rotation;
    f32 timer;
    AnimCtrl *anctrl;
    s32 substate; //times update called?
} s_current_transition;

RECOMP_HOOK ("func_80295C14") void OnPlayerUpdate(void) { 

    bool force_default_fov = FALSE;

    if (s_current_transition.transistion_info != NULL) {
        if (s_current_transition.transistion_info->model_index == ASSET_467_MODEL_TRANSITION_FALLING_JIGGIES 
            && s_current_transition.model_ptr != NULL) {
            force_default_fov = TRUE;
        }
    }

    if (getGameMode() != GAME_MODE_3_NORMAL && getGameMode() != GAME_MODE_4_PAUSED) {
        force_default_fov = TRUE;
    }

    if (level_get() == LEVEL_D_CUTSCENE || map_get() == MAP_91_FILE_SELECT) {
        force_default_fov = TRUE;
    }

    if (force_default_fov) {
        viewport_setFOVy(40);
    } else {
        viewport_setFOVy(recomp_get_config_double("number_option"));
    }
}
