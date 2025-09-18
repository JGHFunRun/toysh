# ToySH - JGHFunRun's Toy Shell

## Building

Start by cloning the repo:

```sh
git clone https://github.com/JGHFunRun/toysh.git
cd toysh
```

All build instructions are for in-source builds. If you want an out of source
build, replace invocations of CMake as `cmake ..` with `cmake -Spath/to/source
-Bpath/to/build`. In source builds should always be inside of the directories
`build/`.

### Linux

_All instructions assume you are starting in the root source directory_

#### With Make

```sh
mkdir build
cd build
cmake .. #-G'Unix Makefiles'
make # to build the application
make doc # to build documentation
make all doc # to build both
```

#### With Ninja

```sh
git clone https://github.com/JGHFunRun/toysh.git && cd toysh

mkdir build
cd build
cmake .. -G'Ninja'
ninja # to build the application
ninja doc # to build documentation
ninja all doc # to build both
```

### Windows

Windows is not yet supported. I aim to support Visual Studio 2022 .sln files and
Ninja in the future. Also maybe Mingw.
