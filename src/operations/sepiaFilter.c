#include "../errors.h"
#include "../tools.h"

OIPL_ErrorInfo OIPL_SepiaFilter(OIPL_Img* img)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    const int totalChannels = img->height * img->width * img->channels;
    int newColors[3] = { 0,0,0 };

    for (int pIndex = 0; pIndex < totalChannels; pIndex += img->channels)
    {
        newColors[0] = (int)(
            (0.393 * img->data[pIndex]) + (0.769 * img->data[pIndex + 1]) + (0.189 * img->data[pIndex + 2]));
        newColors[1] = (int)(
            (0.349 * img->data[pIndex]) + (0.686 * img->data[pIndex + 1]) + (0.168 * img->data[pIndex + 2]));
        newColors[2] = (int)(
            (0.272 * img->data[pIndex]) + (0.534 * img->data[pIndex + 1]) + (0.131 * img->data[pIndex + 2]));

        for (short i = 0; i < 3; i++)
        {
            clampColorValueInt(&(newColors[i]));
            img->data[pIndex + i] = ((unsigned char)newColors[i]);
        }
    }

    return SUCCESS;
}