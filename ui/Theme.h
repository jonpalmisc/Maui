//===-- ui/Theme.h - Theme and font utilities -----------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include <QFont>

/// Central UI theming interface.
class Theme {
public:
    /// Get the configured sans-serif font for the UI.
    static const QFont& sansFont();

    /// Get the configured monospace font for the UI.
    static const QFont& monoFont();
};
