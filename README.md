# About

The program itself (zetget) is designed to turn a saved or captures image into a PDF without any text recognition. The software is also accessible as a dynamic library (libzetget) to be used in other software.

This software uses OpenCV and ImageMagick.

# Build 

The following instructions work for Unix systems.

Clone and enter the repo
```bash
git clone https://github.com/davidpkj/zetget && cd zetget
```
Create and enter the build environment
```bash
mkdir build && cd build
```
Build it
```bash
cmake .. && make -j $(nproc)
```

# Usage

The standard usage is:
```bash
zetget [input-path] [output-path]
```