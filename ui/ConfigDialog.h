//===-- ui/ConfigDialog.h - Program settings dialog -----------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#pragma once

#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>

/// Configuration dialog for choosing the kernel path.
class ConfigDialog : public QDialog {
    QLineEdit* m_kernelPathField;
    QCheckBox* m_useDefaultCheckbox;

public:
    ConfigDialog(bool isAtStartup = false, QWidget* parent = nullptr);

    /// Get the chosen kernel path.
    QString kernelPath() const;

    /// Was the chosen kernel path intended to be the default?
    bool wantsPathAsDefault() const;
};
