#pragma once

#include <example/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <pool/Types.h>
#include <refl/Types.h>
#include <proto/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <procgen/Types.h>
#include <lang/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#include <uio/Types.h>
#include <gfx/Types.h>
#include <gfx-obj/Types.h>
#include <gfx-pbr/Types.h>
#include <gfx-gltf/Types.h>
#include <edit/Types.h>
#include <procgen-gfx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> EXAMPLE_EXPORT Type& type<ShapeType>();
    
    export_ template <> EXAMPLE_EXPORT Type& type<MyObject>();
}
