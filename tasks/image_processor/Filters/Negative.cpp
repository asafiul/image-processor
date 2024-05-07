//
// Created by Azat on 29.10.2023.
//

#include "Negative.h"

void Negative::Apply(BMPImage& bmp_image) const {
    for (int i = 0; i < bmp_image.GetHeight(); ++i) {
        for (int j = 0; j < bmp_image.GetWidth(); ++j) {
            bmp_image.SetPixel(i, j, RGB(MAX_COLOR_VALUE) - bmp_image[i][j]);
        }
    }
}
