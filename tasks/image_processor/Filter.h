#pragma once

#ifndef CMAKELISTS_TXT_FILTER_H
#define CMAKELISTS_TXT_FILTER_H

#include "BMPImage.h"

class Filter {
public:
    virtual ~Filter() {
    }

    virtual void Apply(BMPImage& bmp_image) const = 0;
};

#endif  // CMAKELISTS_TXT_FILTER_H
