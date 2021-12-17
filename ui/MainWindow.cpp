//===-- ui/MainWindow.cpp - Main window of the UI -------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_lastId(0)
    , m_rootLayout(new QVBoxLayout)
{
    setWindowTitle("AMU");

    auto* root = new QWidget;
    root->setLayout(m_rootLayout);
    m_rootLayout->setSpacing(12);
    m_rootLayout->setContentsMargins(24, 24, 24, 24);
    m_rootLayout->addStretch(1);

    pushNewCell();

    setCentralWidget(root);
    resize(600, 700);
}

void MainWindow::pushNewCell()
{
    auto* cell = new Cell(this, ++m_lastId);
    m_cells.append(cell);
    m_rootLayout->insertWidget(m_rootLayout->count() - 1, cell);
}

void MainWindow::cellEvaluated(unsigned id)
{
    if (id == m_cells.last()->id())
        pushNewCell();
}
