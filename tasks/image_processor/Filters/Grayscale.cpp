//
// Created by Azat on 27.10.2023.
//

#include "Grayscale.h"

void Grayscale::Apply(BMPImage& bmp_image) const {
    const double coef_for_b = 0.114;
    const double coef_for_g = 0.587;
    const double coef_for_r = 0.299;
    for (int i = 0; i < bmp_image.GetHeight(); ++i) {
        for (int j = 0; j < bmp_image.GetWidth(); ++j) {
            uint8_t grey =
                static_cast<uint8_t>(coef_for_b * bmp_image[i][j].GetB() + coef_for_g * bmp_image[i][j].GetG() +
                                     coef_for_r * bmp_image[i][j].GetR());
            bmp_image.SetPixel(i, j, RGB(grey));
        }
    }
}
