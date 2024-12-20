# OpenIPL

OpenIPL(Open Image Processing Library) is a C library for image processing.

## Description

OpenIPL provides various functions for working with images, such as converting to grayscale, black and white images, adjusting brightness and contrast, applying filters, and more.
OpenIPL leverages the [SIMDe (SIMD Everywhere)](https://github.com/simd-everywhere/simde?ysclid=m2swyts7k7237665902) library to enable cross-platform parallelized calculations, optimizing processing speed and efficiency.

## Project Structure

```
../OpenIPL/
├── README.md
├── LICENSE
├── CMakeLists.txt
├── scripts/
├   ├── tests.c
├   └── build.py
└── src/
    ├── operations/
    └── simde/
```

## Requirements

- [CMake](https://cmake.org/download/) (version 3.10 or higher)
- C compiler (e.g., [GCC](https://gcc.gnu.org/releases.html), [Clang](https://releases.llvm.org/), or MSVC)

## Building

### Manual Build

1. **Clone the repository**:

   ```bash
   git clone 'https://github.com/LincolnCox29/OpenIPL'
   cd <repo-directory>
   ```

2. **Create a build directory**:

   ```bash
   mkdir build
   cd build
   ```

3. **Run CMake to generate build files**:

   ```bash
   cmake -DCMAKE_BUILD_TYPE=Release ..
   ```

4. **Build the project**:

   ```bash
   cmake --build . --config Release
   ```

### Automatic Build (Recommended)

For convenience, you can use the provided Python script to automate the entire build process:

1. **Clone the repository**:

   ```bash
   git clone 'https://github.com/LincolnCox29/OpenIPL'
   cd <repo-directory>
   ```

2. Make sure Python is installed on your system. If it’s not, you can download it [here](https://www.python.org/).

3. **Simply run the script**:

   ```bash
   python OpenIPL/scripts/build.py
   ```

   This script will:
   - Create the build directory.
   - Configure the project with CMake.
   - Build the project in Release mode.

---

After building, the compiled static library `OpenIPL.lib` will be located in the `lib` directory.

---

## Usage

To use the library in your project, include the header file `OpenIPL.h` and compile with `OpenIPL.lib`.

Example usage:

```c
#include "OpenIPL.h"
#include <stdio.h>

#define printError(errPtr) (printf("ERR --> CODE: %d MSG: %s\n", (errPtr)->code, (errPtr)->message))

int main()
{
	OpenIPLErrorInfo err;
	Img* img = OIPL_imgLoad("src.png");

	err = OIPL_ChromaticAberration(img, 3, 3, -3, -3, 0.5);
	if (err.code)
	{
		OIPL_imgFree(img);
		printError(&err);
		return err.code;
	}

	err = OIPL_imgWrite("out.png", img);
        OIPL_imgFree(img);
	if (err.code)
	{
		printError(&err);
		return err.code;
	}
	return 0;
}
```

## 📚 Documentation

Examples and instructions can be found here: [DOCS](https://github.com/LincolnCox29/OpenIPL/blob/master/DOCS.md)

## 🛠 License
```
OpenIPL is released under the MIT license, allowing free use in both commercial and non-commercial projects.
```
