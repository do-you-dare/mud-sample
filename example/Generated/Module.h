
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <uio/Generated/Module.h>
#include <gfx/Generated/Module.h>
#include <edit/Generated/Module.h>
#include <gen/Generated/Module.h>
        
#include <example/Generated/Forward.h>
#include <example/Generated/Types.h>

#include <example/example.h>

	class EXAMPLE_EXPORT example : public Module
	{
	private:
		example();

	public:
		static example& module() { static example instance; return instance; }
	};

#ifdef _EXAMPLE_MODULE
extern "C"
EXAMPLE_EXPORT Module& getModule();
#endif
