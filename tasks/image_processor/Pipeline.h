#pragma once

#ifndef CMAKELISTS_TXT_PIPELINE_H
#define CMAKELISTS_TXT_PIPELINE_H

#include <vector>
#include "Filter.h"

#include "BMPImage.h"

class Pipeline {
public:
    Pipeline() {
    }

    ~Pipeline() {
        while (!pipeline.empty()) {
            delete pipeline.back();
            pipeline.pop_back();
        }
    }

    void Apply(BMPImage& bmp_image) {
        for (Filter* filter : pipeline) {
            filter->Apply(bmp_image);
        }
    }

    void Add(Filter* filter) {
        pipeline.emplace_back(filter);
    }

    std::vector<Filter*> pipeline;
};

#endif  // CMAKELISTS_TXT_PIPELINE_H
