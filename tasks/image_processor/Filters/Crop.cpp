//
// Created by Azat on 29.10.2023.
//

#include "Crop.h"

void Crop::Apply(BMPImage& bmp_image) const {
    int32_t h = std::min(height_, bmp_image.GetHeight());
    int32_t w = std::min(width_, bmp_image.GetWidth());
    BMPImage filtered;
    filtered.Assign(h, w);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            filtered.SetPixel(i, j, bmp_image[i + (bmp_image.GetHeight() - h)][j]);
        }
    }
    bmp_image.SwapImage(filtered);
}
