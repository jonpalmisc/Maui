//===-- ui/MainWindow.cpp - Main window of the UI -------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include "MainWindow.h"

#include <QScrollArea>

// TODO: Remove hardcoding.
constexpr auto kKernelPath = "/Applications/Wolfram\\ Engine.app/Contents/Resources/Wolfram\\ Player.app/Contents/MacOS/WolframKernel -mathlink";

MainWindow::MainWindow(const QString& kernelPath, QWidget* parent)
    : QMainWindow(parent)
    , m_rootLayout(new QVBoxLayout)
{
    auto* root = new QWidget;
    root->setLayout(m_rootLayout);
    m_rootLayout->setSpacing(0);
    m_rootLayout->setContentsMargins(0, 0, 0, 0);
    m_rootLayout->addStretch(1);

    // Attempt to initialize the engine, initialize the UI based on the result.
    auto error = m_engine.init(kernelPath.toStdString());
    if (error == amu::Error::None)
        pushNewCell();
    else
        m_rootLayout->addWidget(new QLabel("Failed to initialize engine."));

    auto* scrollArea = new QScrollArea;
    scrollArea->setWidget(root);
    scrollArea->setWidgetResizable(true);

    setWindowTitle("Amu");
    setCentralWidget(scrollArea);
    resize(600, 700);
}

MainWindow::~MainWindow()
{
    m_engine.deinit();
}

void MainWindow::pushNewCell()
{
    auto* cell = new Cell(this);

    m_cells.append(cell);
    m_rootLayout->insertWidget(m_rootLayout->count() - 1, cell);
}

amu::Engine* MainWindow::engine()
{
    return &m_engine;
}

void MainWindow::cellEvaluated(unsigned id)
{
    if (id == m_cells.last()->id())
        pushNewCell();
}
