## 📚 Documentation

- imgToGrayscale(Img* img, float factor): Converts an image to grayscale. The factor adjusts the degree of conversion.
  
  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_ToGrayscale/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_ToGrayscale/OIPL_ToGrayscale.png" width="300"></td>
    </tr>
  </table>

- imgToBlackAndWhite(Img* img, float factor): Converts an image to black and white. The factor adjusts the brightness threshold.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_ToBlackAndWhite/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_ToBlackAndWhite/OIPL_ToBlackAndWhite.png" width="300"></td>
    </tr>
  </table>

- imgAdjustBrightness(Img* img, float factor): Adjusts the brightness of the image. The factor scales the brightness of each pixel, where `factor > 1.0` increases brightness, and `factor < 1.0` decreases it. Pixel values are clamped between 0 and 255.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_AdjustBrightness/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_AdjustBrightness/OIPL_AdjustBrightness.png" width="300"></td>
    </tr>
  </table>

- imgAdjustContrast(Img* img, float factor): Adjusts the contrast of the image. The factor modifies the contrast where 1.0 keeps it unchanged, values greater than 1.0 increase contrast, and values less than 1.0 decrease it.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_AdjustContrast/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_AdjustContrast/OIPL_AdjustContrast.png" width="300"></td>
    </tr>
  </table>

- imgGaussianBlur(Img* img, unsigned iterations): Applies Gaussian blur to the image. The `iterations` parameter controls how many times the blur is applied; more iterations result in a stronger blur effect.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_GaussianBlur/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_GaussianBlur/OIPL_GaussianBlur.png" width="300"></td>
    </tr>
  </table>

- imgSepiaFilter(Img* img): Applies a sepia tone effect to the image. This filter modifies the red, green, and blue color channels to create a warm, vintage look.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_SepiaFilter/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_SepiaFilter/OIPL_SepiaFilter.png" width="300"></td>
    </tr>
  </table>

- imgSobelFilter(Img* img, float factor): Applies the Sobel filter to detect edges in an image. The `sensitivityFactor` adjusts the strength of the gradient. A higher value enhances edge visibility, while a lower value reduces sensitivity to less distinct edges. This filter calculates the horizontal and vertical gradients using Sobel operators and combines them to highlight areas of high intensity change.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_SobelFilter/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_SobelFilter/OIPL_SobelFilter.png" width="300"></td>
    </tr>
  </table>

- imgNegative(Img* img): Inverts the colors of the image, creating a negative effect by subtracting each color component (red, green, blue) from 255.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_Negative/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/OIPL_Negative/OIPL_Negative.png" width="300"></td>
    </tr>
  </table>

- imgToMirror(Img* img): Creates a mirrored version of the image by flipping it horizontally.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/ToMirror/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/ToMirror/ToMirror.png" width="300"></td>
    </tr>
  </table>

- imgTurn90(Img* img): Rotates the image by 90 degrees.
- imgTint(Img* img, float rFactor, float gFactor, float bFactor): Applies a color tint to the image by scaling each of the red, green, and blue channels independently. The `rFactor`, `gFactor`, and `bFactor` parameters adjust the intensity of the respective color channels. A factor greater than 1.0 increases the intensity of the color, while a factor less than 1.0 reduces it. Pixel values are clamped between 0 and 255 to ensure valid color representation.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/Tint/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/Tint/Tint.png" width="300"></td>
    </tr>
  </table>

- imgSharpen(Img* img): Applies a sharpening filter to the image, enhancing the edges and fine details. This effect is achieved by using a convolution kernel that increases the contrast of neighboring pixels.

  <table> 
      <tr> 
          <td style="text-align: center;">Original Image</td> 
          <td style="text-align: center;">Modified Image</td>
      </tr> 
      <tr> 
          <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/Sharpen/source.png" width="300"></td> 
          <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/Sharpen/Sharpen.png" width="300"></td> 
      </tr> 
  </table>

- imgBilinearInterpolation(Img* img, int newHeight, int newWidth): Resizes the image to the specified `height` and `width` using bilinear interpolation.

- imgChromaticAberration(Img* img, int shiftX, int shiftY): Simulates a chromatic aberration effect by shifting color channels (red, green, and blue) independently. The `shiftX` and `shiftY` parameters control the horizontal and vertical offset for the color channels, creating a subtle color fringing effect similar to optical distortions often seen in lower-quality lenses. This function can be used in combination with the Gaussian blur filter to reduce artifacts, resulting in a smoother and more natural aberration effect.

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/ChromaticAberration/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/ChromaticAberration/ChromaticAberration.png" width="300"></td>
    </tr>
  </table>

---

- imgAddText(Img* img, int centerX, int centerY, char* text, unsigned fontSize, const OIPLFont* font, int r, int g, int b):  
  Renders text onto an image at the specified position and size. The text is centered at `(centerX, centerY)` with the given `fontSize`, using the provided `OIPLFont`. The `r`, `g`, and `b` parameters define the text color in RGB. 

### Parameters:
- **`img`**: Pointer to the target image.
- **`centerX, centerY`**: Coordinates where the text is centered.
- **`text`**: Null-terminated string to render.
- **`fontSize`**: Size of the text in pixels.
- **`font`**: Pointer to the `OIPLFont` structure containing font data.
- **`r, g, b`**: Color values (0-255) for the red, green, and blue channels of the text.

### Description:
- The function calculates the text width and line height based on the font's metrics and scales it according to the desired font size.  
- The text is rendered character by character, blending it with the background. Each glyph is placed at its computed position, ensuring proper spacing and kerning.  
- Color blending ensures that the text appears anti-aliased on the image.

### Example Usage:
```c
#include "OpenIPL.h"
#include <stdio.h>

#define printError(errPtr) (printf("ERR --> CODE: %d MSG: %s\n", (errPtr)->code, (errPtr)->message))

int main()
{
    OIPL_ErrorInfo err;
    OIPL_Img* img = OIPL_imgLoad("src.png");
    OIPL_Font* font = OIPL_fontLoad("font.ttf");

    int halfWidth = (int)(img->width / 2);
    err = OIPL_AddText(img, halfWidth, 300, "Test Text", 30, font, 255, 255, 255);
    if (err.code)
    {
        OIPL_imgFree(img);
        OIPL_fontFree(font);
        printError(&err);
        return 1;
    }

    err = OIPL_imgWrite("out.png", img);
    OIPL_imgFree(img);
    OIPL_fontFree(font);
    if (err.code)
    {
        printError(&err);
        return 1;
    }
}
```

  <table>
    <tr>
      <td style="text-align: center;">Original Image</td>
      <td style="text-align: center;">Modified Image</td>
    </tr>
    <tr>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/AddText/source.png" width="300"></td>
      <td><img src="https://github.com/LincolnCox29/OpenIPL/blob/master/examples/AddText/AddText.png" width="300"></td>
    </tr>
  </table>

---

### writeImg(const char* path, Img* img):
Saves an image to a file in the specified format.

- **path**: The file path where the image will be saved.
- **img**: The image to be saved (structure containing the width, height, channels, and pixel data).
- **type**: The format in which to save the image. This can be one of the following:
    - `PNG`: Saves the image in PNG format using `stbi_write_png`.
    - `JPEG`: Saves the image in JPEG format using `stbi_write_jpg` with a quality factor of 100.
    - `BMP`: Saves the image in BMP format using `stbi_write_bmp`.
    - `TGA`: Saves the image in TGA format using `stbi_write_tga`.

---

### loadImg(const char* path):
Loads an image from the specified file.

- **path**: The file path of the image to load.
- **Returns**: A pointer to an `Img` structure that contains the loaded image data, including its width, height, and number of channels. The image data is stored in `img->data`.

Example:
```c
OIPL_Img* img = OIPL_imgLoad("input.png");
if (img->data) {
    // Image successfully loaded, now you can process or save it
} else {
    printf("Failed to load image\n");
}
```

---

### imgFree(Img* img):
Frees the memory allocated for an image structure and its associated pixel data.

- **img**: A pointer to the `Img` structure whose memory is to be freed. This structure typically contains the image's width, height, channels, and a pointer to the pixel data.
- **Details**: 
    - The function first checks if the `img` pointer is `NULL` to avoid errors.
    - It releases the memory allocated for the pixel data (`img->data`) using `free()`.
    - It sets `img->data` to `NULL` to prevent dangling pointers.
    - If the `Img` structure itself was dynamically allocated, it will also be freed.

- **Example Usage**:
    ```c
    OIPL_Img* image = OIPL_imgLoad("path/to/image.png");
    if (image != NULL) {
        // Process the image as needed
        OIPL_imgFree(image); // Properly frees the allocated memory
    }
    ```
