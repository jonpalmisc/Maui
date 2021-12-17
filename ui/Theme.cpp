//===-- ui/Theme.cpp - Theme and font utilities ---------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include "Theme.h"

QFont gMonoFont, gSansFont;
bool gMonoFontInitialized = false;
bool gSansFontInitialized = false;

const QFont& Theme::sansFont()
{
    if (!gSansFontInitialized) {
        gSansFont = QFont("Ubuntu", 14);
        gSansFontInitialized = true;
    }

    return gSansFont;
}

const QFont& Theme::monoFont()
{
    if (!gMonoFontInitialized) {
        gMonoFont = QFont("Ubuntu Mono", 14);
        gMonoFontInitialized = true;
    }

    return gMonoFont;
}
