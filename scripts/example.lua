-- mud example module

example = mud_module(nil, "example", PROJECT_DIR, "example", nil, nil, nil, mud.mud)
    
mud_shell("example", { example }, {})


