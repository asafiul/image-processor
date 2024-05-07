#pragma once

#ifndef CMAKELISTS_TXT_SHARPENING_H
#define CMAKELISTS_TXT_SHARPENING_H

#include "../Filter.h"

class Sharpening : public Filter {
public:
    Sharpening() {
    }

    void Apply(BMPImage &mp_image) const override;

protected:
    constexpr static int32_t Matrix[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};

#endif  // CMAKELISTS_TXT_SHARPENING_H
