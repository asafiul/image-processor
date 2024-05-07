//
// Created by Azat on 30.10.2023.
//

#include <vector>
#include "EdgeDetection.h"
#include "Grayscale.h"

void EdgeDetection::Apply(BMPImage& bmp_image) const {
    BMPImage filtered;
    filtered.Assign(bmp_image.GetHeight(), bmp_image.GetWidth());
    for (int i = 0; i < bmp_image.GetHeight(); ++i) {
        for (int j = 0; j < bmp_image.GetWidth(); ++j) {
            filtered.SetPixel(i, j, bmp_image[i][j]);
        }
    }
    Grayscale grayscale;
    grayscale.Apply(filtered);
    for (int32_t i = 0; i < bmp_image.GetHeight(); ++i) {
        for (int32_t j = 0; j < bmp_image.GetWidth(); ++j) {
            std::vector<int32_t> dp = {0, 0, 0};
            for (int32_t delta_i = -1; delta_i <= 1; ++delta_i) {
                for (int32_t delta_j = -1; delta_j <= 1; ++delta_j) {
                    int32_t x = std::clamp(i + delta_i, 0, bmp_image.GetHeight() - 1);
                    int32_t y = std::clamp(j + delta_j, 0, bmp_image.GetWidth() - 1);
                    RGB* last_pixel = filtered.GetPixel(x, y);
                    int32_t delt = Matrix[delta_i + 1][delta_j + 1];
                    dp[0] += last_pixel->GetB() * delt;
                    dp[1] += last_pixel->GetG() * delt;
                    dp[2] += last_pixel->GetR() * delt;
                }
            }
            bmp_image.SetPixel(i, j, RGB(dp[0] > threshold_ ? MAX_COLOR_VALUE : 0));
        }
    }
}
