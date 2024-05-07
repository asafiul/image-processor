#pragma once

#ifndef CMAKELISTS_TXT_CLIPARSER_H
#define CMAKELISTS_TXT_CLIPARSER_H

#include <stdexcept>
#include <vector>
#include "FilterSettings.h"

class CLIParser {
public:
    CLIParser() {
    }

    ~CLIParser() {
        while (!fs_vec.empty()) {
            delete fs_vec.back();
            fs_vec.pop_back();
        }
    }

    CLIParser(int argc, char** argv);

    std::vector<FilterSettings*> fs_vec;
};

#endif  // CMAKELISTS_TXT_CLIPARSER_H
