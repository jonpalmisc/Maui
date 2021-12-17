//===-- ui/Cell.h - Notebook cell widget ----------------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#pragma once

#include <QLabel>
#include <QLineEdit>

class MainWindow;

/// A notebook cell.
class Cell : public QWidget {
    Q_OBJECT

    MainWindow* m_mainWindow;
    unsigned m_id;

    QWidget* m_inputSubcell;
    QWidget* m_outputSubcell;

    QLabel* m_inputLabel;
    QLineEdit* m_inputField;

    QLabel* m_outputLabel;
    QLabel* m_outputField;

public:
    Cell(MainWindow* mainWindow, unsigned id, QWidget* parent = nullptr);

    /// Get the cell's ID.
    unsigned id() const { return m_id; }

    /// Evaluate the cell's current input
    void evaluateCurrentInput();

    /// Show the output sub-cell.
    void showOutput();
};
