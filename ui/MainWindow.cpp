//===-- ui/MainWindow.cpp - Main window of the UI -------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of Maui, an open source UI for the Wolfram Engine. The
// source code for Maui is available at <https://github.com/jonpalmisc/Maui>.
//
//===----------------------------------------------------------------------===//

#include "MainWindow.h"

#include <QScrollArea>

MainWindow::MainWindow(const QString& kernelPath, QWidget* parent)
    : QMainWindow(parent)
    , m_rootLayout(new QVBoxLayout)
{
    auto* root = new QWidget;
    root->setLayout(m_rootLayout);
    m_rootLayout->setSpacing(12);
    m_rootLayout->setContentsMargins(12, 12, 12, 12);
    m_rootLayout->addStretch(1);

    // Attempt to initialize the engine, initialize the UI based on the result.
    auto error = m_engine.init(kernelPath.toStdString());
    if (error == maui::Error::None)
        pushNewCell();
    else
        m_rootLayout->addWidget(new QLabel("Failed to initialize engine."));

    auto* scrollArea = new QScrollArea;
    scrollArea->setWidget(root);
    scrollArea->setWidgetResizable(true);

    setContentsMargins(0, 0, 0, 0);
    setWindowTitle("Maui");
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

maui::Engine* MainWindow::engine()
{
    return &m_engine;
}

void MainWindow::cellEvaluated(unsigned id)
{
    if (id == m_cells.last()->id())
        pushNewCell();
}
