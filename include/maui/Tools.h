//===-- include/Maui/Tools.h - Utilities for working with WSTP -------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of Maui, an open source UI for the Wolfram Engine. The
// source code for Maui is available at <https://github.com/jonpalmisc/Maui>.
//
//===----------------------------------------------------------------------===//

#pragma once

#include <string>

namespace maui {

/// Unescape a string with octal escape sequences. Frequently needed to process
//  WSTP (return) text packets.
///
/// \param input The escaped string to unescape
std::string octalUnescape(const std::string& input);

/// Extract the ID from a formatted input/output name.
///
/// \param name The formatted name to parse
int extractId(const char* name);

}
