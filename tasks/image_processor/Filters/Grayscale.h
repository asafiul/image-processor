#pragma once

#ifndef CMAKELISTS_TXT_GRAYSCALE_H
#define CMAKELISTS_TXT_GRAYSCALE_H

#include "../Filter.h"

class Grayscale : public Filter {
public:
    Grayscale() {
    }

    void Apply(BMPImage &bmp_image) const override;
};

#endif  // CMAKELISTS_TXT_GRAYSCALE_H
