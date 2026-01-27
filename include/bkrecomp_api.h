#ifndef __BKRECOMP_API_H__
#define __BKRECOMP_API_H__

#include "modding.h"
#include "enums.h"
#include "PR/ultratypes.h"

// Pull in some typedefs to avoid needing to include decomp headers.
typedef struct actorMarker_s ActorMarker;
typedef struct cude_s Cube;
typedef union prop_s Prop;

typedef enum {
    EXTENSION_TYPE_MARKER,
    EXTENSION_TYPE_PROP,
} ExtensionType;

// ActorMarkers
typedef u32 MarkerExtensionId;

// Registers an actor marker data extension of a given size that applies to a single type of actor marker specified by `type`.
// Returns a handle that can be passed to `bkrecomp_get_extended_marker_data` along with an ActorMarker* to get the data.
// This must be called before any actor markers have spawned. It is recommended to call this from a `recomp_on_init` callback.
RECOMP_IMPORT("*", MarkerExtensionId bkrecomp_extend_marker(enum marker_e type, u32 size));

// Registers an actor marker data extension of the given size that applies to all actor markers in the game.
// Returns a handle that can be passed to `bkrecomp_get_extended_marker_data` along with an ActorMarker* to get the data.
// This must be called before any actor markers have spawned. It is recommended to call this from a `recomp_on_init` callback.
RECOMP_IMPORT("*", MarkerExtensionId bkrecomp_extend_marker_all(u32 size));

// Returns a pointer to the extended actor marker data associated with a given extension for the provided ActorMarker*.
RECOMP_IMPORT("*", void* bkrecomp_get_extended_marker_data(ActorMarker* marker, MarkerExtensionId extension));

// Returns the spawn index for a given actor marker in the current map. This is an incremental value that starts at 0 when a map
// is loaded and counts up by one for every actor marker spawned.
// Note that this may not be deterministic for map spawn list actor markers, as other mods could potentially spawn additional actor markers
// before the map's spawn list is processed.
RECOMP_IMPORT("*", u32 bkrecomp_get_marker_spawn_index(ActorMarker* marker));

// Props
typedef u32 PropExtensionId;

// Registers a prop data extension of the given size that applies to all props in the game.
// Returns a handle that can be passed to `bkrecomp_get_extended_prop_data` along with a Prop* and Cube* to get the data.
// This must be called before any props have spawned. It is recommended to call this from a `recomp_on_init` callback.
RECOMP_IMPORT("*", PropExtensionId bkrecomp_extend_prop_all(u32 size));

// Returns a pointer to the extended prop data associated with a given extension for the provided Prop* in the provided Cube*.
// The return value is undefined if the provided Prop is not in the provided Cube.
RECOMP_IMPORT("*", void *bkrecomp_get_extended_prop_data(Cube* cube, Prop* prop, PropExtensionId extension_id));

// Returns the spawn index for a given prop in the current map. This is an incremental value that starts at 0 when a map
// is loaded and counts up by one for every prop spawned.
// Note that this may not be deterministic for map spawn list props, as other mods could potentially spawn additional props
// before the map's spawn list is processed.
RECOMP_IMPORT("*", u32 bkrecomp_get_prop_spawn_index(Cube* cube, Prop* prop));

#endif
