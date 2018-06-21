

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module .example;
#else
#include <example/Types.h>
#include <example/Api.h>
#include <obj/Vector.h>
//#include <proto/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> EXAMPLE_EXPORT Type& type<ShapeType>() { static Type ty("ShapeType"); return ty; }
    
    template <> EXAMPLE_EXPORT Type& type<MyObject>() { static Type ty("MyObject"); return ty; }
}
