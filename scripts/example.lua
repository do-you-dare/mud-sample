-- mud example module

project "example"
    kind "ConsoleApp"

    mud_module("example", PROJECT_DIR, "example", "EXAMPLE")
    
    uses_mud()
    uses_mud_gfx()
    mud_binary("example")

