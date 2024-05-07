//
// Created by Azat on 31.10.2023.
//

#include <random>
#include "Mosaic.h"

RGB GetRandom(int32_t low_x, int32_t low_y, int32_t high_x, int32_t high_y, BMPImage& filtered) {
    static std::mt19937 rnd(static_cast<int64_t>(low_x) * static_cast<int64_t>(low_y));
    int32_t x = low_x + static_cast<int32_t>(rnd() % (high_x - low_x));
    int32_t y = low_y + static_cast<int32_t>(rnd() % (high_y - low_y));
    return filtered[x][y];
}

void Mosaic::Apply(BMPImage& bmp_image) const {
    BMPImage filtered;
    filtered.Assign(bmp_image.GetHeight(), bmp_image.GetWidth());
    for (int i = 0; i < bmp_image.GetHeight(); ++i) {
        for (int j = 0; j < bmp_image.GetWidth(); ++j) {
            filtered.SetPixel(i, j, bmp_image[i][j]);
        }
    }
    for (int32_t i = 0; i < bmp_image.GetHeight(); i += width_) {
        for (int32_t j = 0; j < bmp_image.GetWidth(); j += width_) {
            int32_t high_i = std::min(i + width_, bmp_image.GetHeight());
            int32_t high_j = std::min(j + width_, bmp_image.GetWidth());
            for (int cur_i = i; cur_i < high_i; ++cur_i) {
                for (int cur_j = j; cur_j < high_j; ++cur_j) {
                    bmp_image.SetPixel(cur_i, cur_j, GetRandom(i, j, high_i, high_j, filtered));
                }
            }
        }
    }
}
