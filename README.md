# OpenIPL

OpenIPL(Open Image Processing Library) is a C library for image processing.

## Description

OpenIPL provides various functions for working with images, such as converting to grayscale, black and white images, adjusting brightness and contrast, applying filters, and more.
OpenIPL leverages the [SIMDe (SIMD Everywhere)](https://github.com/simd-everywhere/simde?ysclid=m2swyts7k7237665902) library to enable cross-platform parallelized calculations, optimizing processing speed and efficiency.

## Project Structure

```
../OpenIPL/
├── README.md
├── CMakeLists.txt
├── tests.c
└── src/
    ├── operations/
    └── simde/
```

## Requirements

- [CMake](https://cmake.org/download/) (version 3.10 or higher)
- C compiler (e.g., [GCC](https://gcc.gnu.org/releases.html), [Clang](https://releases.llvm.org/), or MSVC)

## Building

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

After building, the compiled static library `OpenIPL.lib` will be located in the `lib` directory.

## Usage

To use the library in your project, include the header file `OpenIPL.h` and compile with `OpenIPL.lib`.

Example usage:

```c
#include "OpenIPL.h"
#include <stdio.h>

int main()
{
    Img* img = loadImg("src.png");
    OpenIPLErrorInfo err = imgBilinearInterpolation(img, 256, 256);
    if (err.code != OIPL_SUCCESS)
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
  
  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/Grayscale.png" width="300"></td>
    </tr>
  </table>

- **imgToBlackAndWhite(Img* img, float factor):** Converts an image to black and white. The factor adjusts the brightness threshold.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/BlackAndWhite.png" width="300"></td>
    </tr>
  </table>

- **imgAdjustBrightness(Img* img, float factor):** Adjusts the brightness of the image. The factor scales the brightness of each pixel, where `factor > 1.0` increases brightness, and `factor < 1.0` decreases it. Pixel values are clamped between 0 and 255.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/Brightness.png" width="300"></td>
    </tr>
  </table>

- **imgAdjustContrast(Img* img, float factor):** Adjusts the contrast of the image. The factor modifies the contrast where 1.0 keeps it unchanged, values greater than 1.0 increase contrast, and values less than 1.0 decrease it.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/Contrast.png" width="300"></td>
    </tr>
  </table>

- **imgGaussianBlur(Img* img, unsigned iterations):** Applies Gaussian blur to the image. The `iterations` parameter controls how many times the blur is applied; more iterations result in a stronger blur effect.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/GaussianBlur.png" width="300"></td>
    </tr>
  </table>

- **imgSepiaFilter(Img* img):** Applies a sepia tone effect to the image. This filter modifies the red, green, and blue color channels to create a warm, vintage look.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/SepiaFilter.png" width="300"></td>
    </tr>
  </table>

- **imgSobelFilter(Img* img, float factor):** Applies the Sobel filter to detect edges in an image. The `sensitivityFactor` adjusts the strength of the gradient. A higher value enhances edge visibility, while a lower value reduces sensitivity to less distinct edges. This filter calculates the horizontal and vertical gradients using Sobel operators and combines them to highlight areas of high intensity change.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/SobelFilter.png" width="300"></td>
    </tr>
  </table>

- **imgNegative(Img* img):** Inverts the colors of the image, creating a negative effect by subtracting each color component (red, green, blue) from 255.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/Negative.png" width="300"></td>
    </tr>
  </table>

- **imgToMirror(Img* img):** Creates a mirrored version of the image by flipping it horizontally.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/imgToMirror.png" width="300"></td>
    </tr>
  </table>

- **imgTurn90(Img* img):** Rotates the image by 90 degrees.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/imgTurn90.png" width="300"></td>
    </tr>
  </table>

- **imgTint(Img* img, float rFactor, float gFactor, float bFactor):** Applies a color tint to the image by scaling each of the red, green, and blue channels independently. The `rFactor`, `gFactor`, and `bFactor` parameters adjust the intensity of the respective color channels. A factor greater than 1.0 increases the intensity of the color, while a factor less than 1.0 reduces it. Pixel values are clamped between 0 and 255 to ensure valid color representation.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/tint.png" width="300"></td>
    </tr>
  </table>

- **imgSharpen(Img img):** Applies a sharpening filter to the image, enhancing the edges and fine details. This effect is achieved by using a convolution kernel that increases the contrast of neighboring pixels.

  <table> 
      <tr> 
          <td style="text-align: center;">Original Image</td> 
          <td style="text-align: center;">Modified Image</td>
      </tr> 
      <tr> 
          <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/source.png" width="300"></td> 
          <td><img src="https://github.com/LincolnCox29/ImgLib/blob/master/examples/Sharpen.png" width="300"></td> 
      </tr> 
  </table>

- **imgBilinearInterpolation(Img* img, int newHeight, int newWidth):** Resizes the image to the specified `height` and `width` using bilinear interpolation.

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
OpenIPL is released under the MIT license, allowing free use in both commercial and non-commercial projects.
```
