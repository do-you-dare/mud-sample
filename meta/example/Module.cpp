#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module .example;
#else
#include <meta/example/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/example/Convert.h>
#endif
#define EXAMPLE_REFLECTION_IMPL
#include <meta/example/Meta.h>

	example::example()
		: Module("example")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_pool::m();
        mud_refl::m();
        mud_proto::m();
        mud_srlz::m();
        mud_math::m();
        mud_geom::m();
        mud_procgen::m();
        mud_lang::m();
        mud_ctx::m();
        mud_ui::m();
        mud_uio::m();
        mud_gfx::m();
        mud_gfx_obj::m();
        mud_gfx_pbr::m();
        mud_gfx_gltf::m();
        mud_edit::m();
        mud_procgen_gfx::m();

        // setup reflection meta data
		example_meta(*this);
	}

#ifdef EXAMPLE_MODULE
extern "C"
Module& getModule()
{
	return example::m();
}
#endif
