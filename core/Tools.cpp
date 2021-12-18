//===-- core/Tools.h - Utilities for working with WSTP --------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include <amu/Tools.h>
#include <string>

namespace amu {

std::string octalUnescape(const std::string& input)
{
    std::string result;

    // This is super sketchy and fragile but it's good enough for now.
    for (auto pos = input.begin(), end = input.end(); pos < end; ++pos) {
        if (*pos == '\\') {
            std::string octalSequence(pos + 1, pos + 4);
            result += (char)std::stoi(octalSequence, 0, 8);

            pos += 3;
            continue;
        }

        result += *pos;
    }

    return result;
}

int extractId(const char* name)
{
    std::string idString;

    auto c = name;
    while (*c != 0) {
        if (*c >= 0x30 && *c <= 0x39)
            idString += c;

        ++c;
    }

    return std::stoi(idString);
}

}
