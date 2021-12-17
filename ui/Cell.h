//===-- Cell.h - Notebook cell widget -------------------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#pragma once

#include <QLabel>

/// A notebook cell.
class Cell : public QWidget {
    Q_OBJECT

    unsigned m_id;

    QWidget* m_inputSubcell;
    QWidget* m_outputSubcell;

    QLabel* m_inputLabel;
    QLabel* m_inputField;

    QLabel* m_outputLabel;
    QLabel* m_outputField;

public:
    Cell(unsigned id, QWidget* parent = nullptr);

    /// Show the output sub-cell.
    void showOutput();
};
