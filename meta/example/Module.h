
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/obj/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/proto/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/procgen/Module.h>
#include <meta/lang/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-obj/Module.h>
#include <meta/gfx-pbr/Module.h>
#include <meta/gfx-gltf/Module.h>
#include <meta/edit/Module.h>
#include <meta/procgen-gfx/Module.h>
#endif
        
#include <example/Forward.h>
#include <example/Types.h>
#include <example/Api.h>

#include <meta/example/Convert.h>

#ifndef EXAMPLE_REFL_EXPORT
#define EXAMPLE_REFL_EXPORT MUD_IMPORT
#endif

	export_ class EXAMPLE_REFL_EXPORT example : public Module
	{
	private:
		example();

	public:
		static example& m() { static example instance; return instance; }
	};

#ifdef EXAMPLE_MODULE
extern "C"
EXAMPLE_REFL_EXPORT Module& getModule();
#endif
