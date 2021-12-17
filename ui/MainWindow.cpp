//===-- MainWindow.cpp - Main window of the UI ----------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include "MainWindow.h"
#include "Cell.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("AMU");

    auto* root = new QWidget;
    auto* rootLayout = new QVBoxLayout(root);
    rootLayout->setSpacing(12);
    rootLayout->setContentsMargins(24, 24, 24, 24);

    for (unsigned i = 0; i < 5; ++i) {
        auto* cell = new Cell(i + 1);
        rootLayout->addWidget(cell);
    }
    rootLayout->addStretch(1);

    setCentralWidget(root);
}

MainWindow::~MainWindow()
{
}
