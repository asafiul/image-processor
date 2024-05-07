#pragma once

#ifndef CMAKELISTS_TXT_EDGEDETECTION_H
#define CMAKELISTS_TXT_EDGEDETECTION_H

#include "../Filter.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection() : threshold_(0) {
    }

    explicit EdgeDetection(double threshold) : threshold_(threshold) {
    }

    void Apply(BMPImage &bmp_image) const override;

protected:
    constexpr static int32_t Matrix[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    double threshold_;
};

#endif  // CMAKELISTS_TXT_EDGEDETECTION_H
