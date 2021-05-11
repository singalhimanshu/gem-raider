# gem-raider

A gem raider game written in C++.

# Build Dependencies

- [cmake](https://cmake.org/)
- [ninja](https://ninja-build.org/) or [GNU Make](https://www.gnu.org/software/make/)
- [SDL2](https://www.libsdl.org/)

# Build Instructions

If you are using ninja - 

``` shell
mkdir -p build
cd build
cmake -G Ninja ..
ninja
```

If you are using make - 

``` shell
mkdir -p build
cd build
cmake ..
make
```


# Run

From the project root execute the following command - 

``` shell
./build/bin/gem-raider
```
