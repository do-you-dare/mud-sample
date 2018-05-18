

#include <example/Generated/Types.h>
#include <example/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> EXAMPLE_EXPORT Type& type<ShapeType>() { static Type ty("ShapeType"); return ty; }
    
    template <> EXAMPLE_EXPORT Type& type<MyObject>() { static Type ty("MyObject"); return ty; }
}
