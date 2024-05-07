#pragma once

#ifndef CMAKELISTS_TXT_CROP_H
#define CMAKELISTS_TXT_CROP_H

#include "../Filter.h"

class Crop : public Filter {
public:
    Crop() {
    }

    Crop(int32_t height, int32_t width) : height_(height), width_(width) {
    }

    void Apply(BMPImage &bmp_image) const override;

protected:
    int32_t height_;
    int32_t width_;
};

#endif  // CMAKELISTS_TXT_CROP_H
