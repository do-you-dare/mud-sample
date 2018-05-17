-- mud sample

solution "mud-sample"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		"x32",
		"x64"
	}

	language "C++"
    
    
PROJECT_DIR    = path.getabsolute("..")
BUILD_DIR      = path.join(PROJECT_DIR, "build")
MUD_DIR        = path.join(PROJECT_DIR, "mud")

dofile(path.join(MUD_DIR, "scripts/toolchain_mud.lua"))
dofile(path.join(MUD_DIR, "scripts/mud.lua"))
dofile(path.join(MUD_DIR, "scripts/mud_example.lua"))

dofile "example.lua"
