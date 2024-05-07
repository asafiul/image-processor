#pragma once

#ifndef CMAKELISTS_TXT_FILTERSETTINGS_H
#define CMAKELISTS_TXT_FILTERSETTINGS_H

#include <string>
#include <vector>

class FilterSettings {
public:
    FilterSettings() {
    }

    explicit FilterSettings(const std::string& filter_name) : filter_name(filter_name) {
    }

    FilterSettings(const std::string& filter_name, std::vector<std::string> parameters)
        : filter_name(filter_name), parameters(parameters) {
    }

    void Add(const std::string& s) {
        parameters.push_back(s);
    }

    std::string filter_name;
    std::vector<std::string> parameters = {};
};

#endif  // CMAKELISTS_TXT_FILTERSETTINGS_H
