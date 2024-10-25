# ImgLib

ImgLib is a C library for image processing.

## Description

ImgLib provides various functions for working with images, such as converting to grayscale, black and white images, adjusting brightness and contrast, applying filters, and more.

## Project Structure

```
../ImgLib/
├── CMakeLists.txt
├── src/
    ├── errors.c
    ├── errors.h
    ├── ImgLib.c
    ├── ImgLib.h
    ├── stb_image.h
    ├── stb_image_write.h
    ├── tools.c
    ├── tools.h
    └── operations/
        ├── adjustBrightness.c
        ├── adjustBrightness.h
        ├── adjustContrast.c
        ├── adjustContrast.h
        ├── gaussianBlur.c
        ├── gaussianBlur.h
        ├── grayscale.c
        ├── grayscale.h
        ├── negative.c
        ├── negative.h
        ├── sepiaFilter.c
        ├── sepiaFilter.h
        ├── sobelFilter.c
        ├── sobelFilter.h
        ├── tint.c
        ├── tint.h
        ├── toBlackAndWhite.c
        ├── toBlackAndWhite.h
        ├── toMirror.c
        ├── toMirror.h
        ├── Turn90.c
        └── Turn90.h
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
#include "src/ImgLib.h"
#include <stdio.h>

int main()
{
    Img* img = loadImg("src.png");
    ImgLibErrorInfo err;
    if ((err = imgAdjustContrast(img, 0.8f)).code != IMG_LIB_SUCCESS)
    {
        printf("ERR MSG: %s", err.message);
        return 1;
    }
    writeImg("out.png", *img);
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
- **imgTint(Img* img, float rFactor, float gFactor, float bFactor):** Applies a color tint to the image by scaling each of the red, green, and blue channels independently. The `rFactor`, `gFactor`, and `bFactor` parameters adjust the intensity of the respective color channels. A factor greater than 1.0 increases the intensity of the color, while a factor less than 1.0 reduces it. Pixel values are clamped between 0 and 255 to ensure valid color representation.
  
---

### **writeImg(const char* path, Img img, const IMG_LIB_IMG_TYPE type):**
Saves an image to a file in the specified format.

- **path**: The file path where the image will be saved.
- **img**: The image to be saved (structure containing the width, height, channels, and pixel data).
- **type**: The format in which to save the image. This can be one of the following:
    - `PNG`: Saves the image in PNG format using `stbi_write_png`.
    - `JPEG`: Saves the image in JPEG format using `stbi_write_jpg` with a quality factor of 100.
    - `BMP`: Saves the image in BMP format using `stbi_write_bmp`.
    - `TGA`: Saves the image in TGA format using `stbi_write_tga`.

---

### **loadImg(const char* path):**
Loads an image from the specified file.

- **path**: The file path of the image to load.
- **Returns**: A pointer to an `Img` structure that contains the loaded image data, including its width, height, and number of channels. The image data is stored in `img->data`.

Example:
```c
Img* img = loadImg("input.png");
if (img->data) {
    // Image successfully loaded, now you can process or save it
} else {
    printf("Failed to load image\n");
}
```

## 🛠 License
```
ImgLib is released under the MIT license, allowing free use in both commercial and non-commercial projects.
```

### Notes:
- **Installation**: Clearly outlines the steps for installing the library, including the necessary `#define IMG_LIB_IMPLEMENTATION`.
- **Usage**: Includes a usage example demonstrating how to load an image using `stb_image`, process it with `ImgLib`, and save it using `stb_image_write`.
- **Documentation**: Briefly describes the main functions, explaining their purpose.
- **License**: States that the library is released under the MIT license.
