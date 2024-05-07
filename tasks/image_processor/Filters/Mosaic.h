#pragma once

#ifndef CMAKELISTS_TXT_MOSAIC_H
#define CMAKELISTS_TXT_MOSAIC_H

#include "../Filter.h"

class Mosaic : public Filter {
public:
    Mosaic() : width_(1) {
    }

    explicit Mosaic(int32_t width) : width_(width) {
    }

    void Apply(BMPImage &bmp_image) const override;

protected:
    int32_t width_;
};

#endif  // CMAKELISTS_TXT_MOSAIC_H
