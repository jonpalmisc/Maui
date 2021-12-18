//===-- ui/Theme.h - Theme and font utilities -----------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include <QColor>
#include <QFont>
#include <QPalette>

/// Central UI theming interface.
class Theme {
public:
    /// A single color.
    enum class Color {
        Background,
        Midground,
        MidgroundLight,
        Text,
        TextSecondary,
        Selection,
        Accent,
    };

    /// Get the specified theme color.
    static QColor color(Color color);

    /// Get a `QPalette` using the theme colors.
    static QPalette palette();

    /// Get the application-wide stylesheet.
    static QString stylesheet();

    /// Get the configured sans-serif font for the UI.
    static const QFont& sansFont();

    /// Get the configured monospace font for the UI.
    static const QFont& monoFont();
};
