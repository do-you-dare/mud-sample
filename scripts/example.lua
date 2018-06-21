-- mud example module

project "example"
    kind "ConsoleApp"

    example = mud_module(nil, "example", PROJECT_DIR, "example", nil, nil, nil, mud.all)
    example.decl(example, false)
        
    mud_refl(example)
    example.refl.decl(example.refl, false)
    
    mud_shell("example")

