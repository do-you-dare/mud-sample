
#include <example/Generated/Module.h>

#ifdef EXAMPLE_REFLECT
#include <example/Generated/Convert.h>

#define EXAMPLE_REFLECTION_IMPL
#include <example/Generated/Meta.h>
#endif

	example::example()
		: Module("example")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudmath::module();
        mudui::module();
        muduio::module();
        mudgfx::module();
        mudedit::module();
        mudgen::module();

#ifdef EXAMPLE_REFLECT
        // setup reflection meta data
		example_meta(*this);
#endif
	}

#ifdef _EXAMPLE_MODULE
extern "C"
EXAMPLE_EXPORT Module& getModule()
{
	return example::module();
}
#endif
