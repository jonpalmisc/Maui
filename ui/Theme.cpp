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

QColor Theme::color(Theme::Color color)
{
    switch (color) {
    case Color::Background:
        return QColor("#B3B3B3");
    case Color::Midground:
        return QColor("#EAEAEA");
    case Color::MidgroundLight:
        return QColor("#FFFFFF");
    case Color::Text:
        return QColor("#2C2C2C");
    case Color::TextSecondary:
        return QColor("#8E8E8E");
    case Color::Selection:
        return QColor("#C9DFFA");
    case Color::Accent:
        return QColor("#2680EB");
    }
}

QPalette Theme::palette()
{
    using P = QPalette;

    QPalette p;
    p.setColor(P::Window, color(Color::Background));
    p.setColor(P::WindowText, color(Color::Text));
    p.setColor(P::Text, color(Color::Text));
    p.setColor(P::Highlight, color(Color::Selection));
    p.setColor(P::HighlightedText, color(Color::Text));
    p.setColor(P::Disabled, P::WindowText, color(Color::TextSecondary));
    p.setColor(P::Link, color(Color::Accent));

    return p;
}

const QFont& Theme::sansFont()
{
    if (!gSansFontInitialized) {
        gSansFont = QFont("Ubuntu", 13);
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
