# mud-sample

[mud](https://github.com/hugoam/mud) sample module

build instructions (example with gcc on linux) :  
- `git clone --recursive https://github.com/hugoam/mud-sample`
- `cd mud-sample`
- `mud/bin/genie --gcc=linux-gcc gmake`
- `cd build/projects/gmake-linux`
- `make config=debug64 -j8`

once built, run one of the [examples](https://github.com/hugoam/mud/tree/master/example/) :
- `cd ../../linux64_gcc/bin`
- `./00_cube_d`
