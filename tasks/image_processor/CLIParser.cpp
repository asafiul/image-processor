//
// Created by Azat on 27.10.2023.
//

#include "CLIParser.h"

CLIParser::CLIParser(int argc, char** argv) {
    for (int count = 0; count < argc;) {
        std::string filter_name = *(argv + count);
        if (filter_name[0] != '-') {
            throw std::invalid_argument("Filter name cannot start with no hyphen.");
        }
        FilterSettings* fs = new FilterSettings(filter_name.substr(1, static_cast<int32_t>(filter_name.size()) - 1));

        ++count;
        while (count != argc) {
            if (*(argv + count)[0] == '-') {
                break;
            }
            fs->Add(*(argv + count));
            ++count;
        }
        fs_vec.push_back(fs);
    }
}
