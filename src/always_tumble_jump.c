#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"

// Patches a function in the base game that's used to check if the player should tumble in the air.
RECOMP_PATCH bool player_isFallTumbling(void) {
    recomp_printf("enum_option: %d\n", recomp_get_config_u32("enum_option"));
    recomp_printf("number_option: %d\n", recomp_get_config_double("number_option"));
    char* string_option = recomp_get_config_string("string_option");
    if (string_option != NULL) {
        recomp_printf("string_option: %s\n", string_option);
        recomp_free_config_string(string_option);
    }

    // Always tumble.
    return TRUE;
}
