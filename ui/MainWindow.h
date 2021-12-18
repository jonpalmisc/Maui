//===-- ui/MainWindow.h - Main window of the UI ---------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of Maui, an open source UI for the Wolfram Engine. The
// source code for Maui is available at <https://github.com/jonpalmisc/Maui>.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "Cell.h"

#include <maui/Engine.h>

#include <QMainWindow>
#include <QVBoxLayout>

/// Main application window.
class MainWindow : public QMainWindow {
    Q_OBJECT

    maui::Engine m_engine;

    QList<Cell*> m_cells;
    QVBoxLayout* m_rootLayout;

    /// Create a new cell and place it at the bottom of the notebook.
    void pushNewCell();

public:
    MainWindow(const QString& kernelPath, QWidget* parent = nullptr);
    ~MainWindow();

    /// Get a handle to the connected engine.
    maui::Engine* engine();

public Q_SLOTS:

    /// Slot to signal that a cell has been evaluated.
    void cellEvaluated(unsigned id);
};
