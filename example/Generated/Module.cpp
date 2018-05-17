
#include <example/Generated/Module.h>

#include <example/Generated/Convert.h>

#define EXAMPLE_REFLECTION_IMPL
#include <example/Generated/Meta.h>

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

        // setup reflection meta data
#ifdef EXAMPLE_REFLECTION_IMPL
		example_meta(*this);
#endif
	}

#ifdef _EXAMPLE_MODULE
extern "C"
 Module& getModule()
{
	return example::module();
}
#endif
