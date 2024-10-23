# ImgLib

ImgLib is a C library for image processing.

## Description

ImgLib provides various functions for working with images, such as converting to grayscale, black and white images, adjusting brightness and contrast, applying filters, and more.

## Project Structure

```
../ImgLib/
├── CMakeLists.txt      # CMake file for building
├── ImgLib.c            # Source file of the library
├── ImgLib.h            # Header file of the library
├── stb_image.h         # File for load img
└── stb_image_write.h   # File for write img 
```

## Requirements

- CMake (version 3.10 or higher)
- C compiler (e.g., GCC, Clang, or MSVC)

## Building

1. **Clone the repository**:

   ```bash
   git clone 'https://github.com/LincolnCox29/ImgLib'
   cd <repo-directory>
   ```

2. **Create a build directory**:

   ```bash
   mkdir build
   cd build
   ```

3. **Run CMake to generate build files**:

   ```bash
   cmake ..
   ```

4. **Build the project**:

   ```bash
   cmake --build .
   ```

After building, the compiled static library `ImgLib.lib` will be located in the `lib` directory.

## Usage

To use the library in your project, include the header file `ImgLib.h` and compile with `ImgLib.lib`.

Example usage:

```c
#include "ImgLib.h"
#include <stdio.h>

int main()
{
    Img* img = loadPng("img.png");
    ImgLibErrorInfo err;
    if ((err = imgSepiaFilter(img)).code != IMG_LIB_SUCCESS)
    {
        printf("ERR MSG: %s", err.message);
        return 1;
    }
    writePng("out.png", *img);
    return 0;
}
```

## 📚 Documentation

- **imgToGrayscale(Img* img, float factor):** Converts an image to grayscale. The factor adjusts the degree of conversion.
- **imgToBlackAndWhite(Img* img, float factor):** Converts an image to black and white. The factor adjusts the brightness threshold.
- **imgAdjustBrightness(Img* img, float factor):** Adjusts the brightness of the image. The factor scales the brightness of each pixel, where `factor > 1.0` increases brightness, and `factor < 1.0` decreases it. Pixel values are clamped between 0 and 255.
- **imgAdjustContrast(Img* img, float factor):** Adjusts the contrast of the image. The factor modifies the contrast where 1.0 keeps it unchanged, values greater than 1.0 increase contrast, and values less than 1.0 decrease it.
- **imgGaussianBlur(Img* img, unsigned iterations):** Applies Gaussian blur to the image. The `iterations` parameter controls how many times the blur is applied; more iterations result in a stronger blur effect.
- **imgSepiaFilter(Img* img):** Applies a sepia tone effect to the image. This filter modifies the red, green, and blue color channels to create a warm, vintage look.
- **imgSobelFilter(Img* img, float factor):** Applies the Sobel filter to detect edges in an image. The `sensitivityFactor` adjusts the strength of the gradient. A higher value enhances edge visibility, while a lower value reduces sensitivity to less distinct edges. This filter calculates the horizontal and vertical gradients using Sobel operators and combines them to highlight areas of high intensity change.
- **imgNegative(Img* img):** Inverts the colors of the image, creating a negative effect by subtracting each color component (red, green, blue) from 255.
- **imgToMirror(Img* img):** Creates a mirrored version of the image by flipping it horizontally.
- **imgTurn90(Img* img):** Rotates the image by 90 degrees.

## 🛠 License
```
ImgLib is released under the MIT license, allowing free use in both commercial and non-commercial projects.
```

### Notes:
- **Installation**: Clearly outlines the steps for installing the library, including the necessary `#define IMG_LIB_IMPLEMENTATION`.
- **Usage**: Includes a usage example demonstrating how to load an image using `stb_image`, process it with `ImgLib`, and save it using `stb_image_write`.
- **Documentation**: Briefly describes the main functions, explaining their purpose.
- **License**: States that the library is released under the MIT license.
