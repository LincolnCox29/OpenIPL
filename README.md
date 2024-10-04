# ImgLib

**ImgLib** is an open-source image processing library that supports various image formats. The library provides functions for image transformations such as converting to grayscale or black and white. It is recommended to use **ImgLib** in conjunction with the [stb_image](https://github.com/nothings/stb) library (for loading images) and [stb_image_write](https://github.com/nothings/stb) library (for saving images).

## 📥 Installation

1. Download and add `ImgLib.h` to your project directory.
2. Include the library in your code by adding the following lines:

```c
#define IMG_LIB_IMPLEMENTATION
#include "ImgLib.h"
```

## 🚀 Usage

After installation, you can use the library's functions for image processing. For example:

```c
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMG_LIB_IMPLEMENTATION
#include "ImgLib.h"

int main() {
    Img img;
    img.data = stbi_load("image.png", &img.width, &img.height, &img.channels, 0);
    
    if (img.data == NULL) {
        printf("Error loading image\n");
        return 1;
    }

    ImgLibErrorInfo err = imgToGrayscale(&img, 1.0f);
    if (err.code != IMG_LIB_SUCCESS) {
        printf("Error: %s\n", err.message);
        return 1;
    }

    stbi_write_png("output.png", img.width, img.height, img.channels, img.data, img.width * img.channels);
    stbi_image_free(img.data);

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
<<<<<<< HEAD
- **imgSobelFilter(Img* img, float factor):** Applies the Sobel filter to detect edges in an image. The `sensitivityFactor` adjusts the strength of the gradient. A higher value enhances edge visibility, while a lower value reduces sensitivity to less distinct edges. This filter calculates the horizontal and vertical gradients using Sobel operators and combines them to highlight areas of high intensity change.
=======
- **imgNegative(Img* img):** Inverts the colors of the image, creating a negative effect by subtracting each color component (red, green, blue) from 255.

>>>>>>> df433b4f6b2b9f543272942015ce14fa42f1789c

## 🛠 License

**ImgLib** is released under the MIT license, allowing free use in both commercial and non-commercial projects.

```

### Notes:
- **Installation**: Clearly outlines the steps for installing the library, including the necessary `#define IMG_LIB_IMPLEMENTATION`.
- **Usage**: Includes a usage example demonstrating how to load an image using `stb_image`, process it with `ImgLib`, and save it using `stb_image_write`.
- **Documentation**: Briefly describes the main functions, explaining their purpose.
- **License**: States that the library is released under the MIT license.
