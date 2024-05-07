//
// Created by Azat on 27.10.2023.
//

#include "Factory.h"

const int32_t MAX_INT_LENGTH = 9;

bool IsInt(std::string const& str) {
    auto it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        it++;
    }
    return !str.empty() && it == str.end();
}

Factory::Factory() {
    filters_table.insert({"gs", &CreateGrayscaleFilter});
    filters_table.insert({"neg", &CreateNegativeFilter});
    filters_table.insert({"crop", &CreateCropFilter});
    filters_table.insert({"sharp", &CreateSharpeningFilter});
    filters_table.insert({"edge", &CreateEdgeDetectionFilter});
    filters_table.insert({"mosaic", &CreateMosaicFilter});
}

void Factory::CreatePipeline(std::vector<FilterSettings*>& fs_vec, Pipeline& pipeline) {
    for (size_t i = 0; i < fs_vec.size(); ++i) {
        Filter* created_filter = CreateFilter(*fs_vec[i]);
        if (created_filter) {
            pipeline.Add(created_filter);
        }
    }
}

Filter* Factory::CreateFilter(const FilterSettings& fs) {
    if (filters_table.find(fs.filter_name) == filters_table.end()) {
        throw std::invalid_argument("Filter name:{" + fs.filter_name + "} is not exist.");
    }
    return filters_table[fs.filter_name](fs);
}

Filter* Factory::CreateGrayscaleFilter(const FilterSettings& fs) {
    if (fs.filter_name != "gs") {
        throw std::logic_error("createGrayscaleFilterFilter function not for a " + fs.filter_name + ".");
    }
    if (!fs.parameters.empty()) {
        throw std::invalid_argument("-gs can't have more than 0 parameters.");
    }
    Filter* result = new Grayscale();
    return result;
}

Filter* Factory::CreateNegativeFilter(const FilterSettings& fs) {
    if (fs.filter_name != "neg") {
        throw std::logic_error("createNegativeFilter function not for a " + fs.filter_name + ".");
    }
    if (!fs.parameters.empty()) {
        throw std::invalid_argument("-neg can't have more than 0 parameters.");
    }
    Filter* result = new Negative();
    return result;
}

Filter* Factory::CreateCropFilter(const FilterSettings& fs) {
    if (fs.filter_name != "crop") {
        throw std::logic_error("createCropFilter function not for a " + fs.filter_name + ".");
    }
    if (fs.parameters.size() != 2) {
        throw std::invalid_argument("-crop must gain 2 parameters.");
    }
    if (!IsInt(fs.parameters[0])) {
        throw std::invalid_argument("-crop first parameter must be integer.");
    }
    if (fs.parameters[0].size() > MAX_INT_LENGTH) {
        throw std::invalid_argument("-crop first parameter is too high.");
    }
    if (!IsInt(fs.parameters[1])) {
        throw std::invalid_argument("-crop second parameter must be integer.");
    }
    if (fs.parameters[1].size() > MAX_INT_LENGTH) {
        throw std::invalid_argument("-crop second parameter is too high.");
    }
    int32_t height = stoi(fs.parameters[0]);
    int32_t width = stoi(fs.parameters[1]);
    if (height <= 0) {
        throw std::invalid_argument("-crop height must be bigger than 0.");
    }
    if (width <= 0) {
        throw std::invalid_argument("-crop width must be bigger than 0.");
    }
    Filter* result = new Crop(stoi(fs.parameters[0]), stoi(fs.parameters[1]));
    return result;
}

Filter* Factory::CreateSharpeningFilter(const FilterSettings& fs) {
    if (fs.filter_name != "sharp") {
        throw std::logic_error("createSharpeningFilter function not for a " + fs.filter_name + ".");
    }
    if (!fs.parameters.empty()) {
        throw std::invalid_argument("-sharp can't have more than 0 parameters.");
    }
    Filter* result = new Sharpening();
    return result;
}

Filter* Factory::CreateEdgeDetectionFilter(const FilterSettings& fs) {
    if (fs.filter_name != "edge") {
        throw std::logic_error("createEdgeDetection function not for a " + fs.filter_name + ".");
    }
    if (fs.parameters.size() != 1) {
        throw std::invalid_argument("-edge must gain 1 parameter.");
    }
    double threshold = 0;
    try {
        threshold = std::stod(fs.parameters[0]);
    } catch (...) {
        throw std::invalid_argument("-edge Incorrect threshold parameter.");
    }
    Filter* result = new EdgeDetection(threshold * MAX_COLOR_VALUE_DOUBLE);
    return result;
}

Filter* Factory::CreateMosaicFilter(const FilterSettings& fs) {
    if (fs.filter_name != "mosaic") {
        throw std::logic_error("createMosaic function not for a " + fs.filter_name + ".");
    }
    if (fs.parameters.size() != 1) {
        throw std::invalid_argument("-mosaic must gain 1 parameter.");
    }
    if (!IsInt(fs.parameters[0])) {
        throw std::invalid_argument("-mosaic parameter must be integer.");
    }
    int32_t width = stoi(fs.parameters[0]);
    if (width <= 0) {
        throw std::invalid_argument("-mosaic parameter must be >0.");
    }
    Mosaic* result = new Mosaic(width);
    return result;
}
