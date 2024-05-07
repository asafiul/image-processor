#pragma once

#ifndef CMAKELISTS_TXT_NEGATIVE_H
#define CMAKELISTS_TXT_NEGATIVE_H

#include "../Filter.h"

class Negative : public Filter {
public:
    Negative() {
    }

    void Apply(BMPImage &bmp_image) const override;
};

#endif  // CMAKELISTS_TXT_NEGATIVE_H
