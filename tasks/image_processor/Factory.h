#pragma once

#ifndef CMAKELISTS_TXT_FACTORY_H
#define CMAKELISTS_TXT_FACTORY_H

#include <map>
#include "Filter.h"
#include "FilterSettings.h"
#include "Filters/Grayscale.h"
#include "Filters/Negative.h"
#include "Filters/Crop.h"
#include "Filters/Sharpening.h"
#include "Filters/EdgeDetection.h"
#include "Filters/Mosaic.h"
#include "Pipeline.h"

using FilterCreatePtr = Filter *(*)(const FilterSettings &);

class Factory {
public:
    Factory();

    void CreatePipeline(std::vector<FilterSettings *> &fs_vec, Pipeline &pipeline);

    Filter *CreateFilter(const FilterSettings &fs);

    static Filter *CreateGrayscaleFilter(const FilterSettings &fs);

    static Filter *CreateNegativeFilter(const FilterSettings &fs);

    static Filter *CreateCropFilter(const FilterSettings &fs);

    static Filter *CreateSharpeningFilter(const FilterSettings &fs);

    static Filter *CreateEdgeDetectionFilter(const FilterSettings &fs);

    static Filter *CreateMosaicFilter(const FilterSettings &fs);

protected:
    std::map<std::string, FilterCreatePtr> filters_table;
};

#endif  // CMAKELISTS_TXT_FACTORY_H
