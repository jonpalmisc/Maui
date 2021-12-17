//===-- Cell.cpp - Notebook cell widget -----------------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include "Cell.h"
#include "MainWindow.h"
#include "Theme.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

Cell::Cell(MainWindow* mainWindow, unsigned id, QWidget* parent)
    : QWidget(parent)
    , m_mainWindow(mainWindow)
    , m_id(id)
    , m_inputSubcell(new QWidget)
    , m_outputSubcell(new QWidget)
    , m_inputLabel(new QLabel)
    , m_inputField(new QLineEdit)
    , m_outputLabel(new QLabel)
    , m_outputField(new QLabel)
{
    // Configure all text controls in the cell to use the mono font.
    m_inputLabel->setFont(Theme::monoFont());
    m_inputField->setFont(Theme::monoFont());
    m_outputLabel->setFont(Theme::monoFont());
    m_outputField->setFont(Theme::monoFont());

    // Disable the cell labels so they have a lighter text color.
    m_inputLabel->setEnabled(false);
    m_outputLabel->setEnabled(false);

    // Format the input and output labels with the cell ID.
    m_inputLabel->setText(QString(" In[%1] := ").arg(m_id));
    m_outputLabel->setText(QString("Out[%1] := ").arg(m_id));

    // Add placeholder content to the cell fields.
    m_inputField->setText("Solve[2 300*^-9 == 1/2 l/1.33, l]");
    m_outputField->setText("{{l -> 1.596 10*-6}}");

    // Shorthand for creating subcell layouts.
    auto makeSubcellLayout = [](QWidget* label, QWidget* field) {
        auto* layout = new QHBoxLayout;
        layout->setContentsMargins(12, 12, 12, 12);
        layout->addWidget(label);
        layout->addWidget(field, 1);

        return layout;
    };

    // Create the sub-cell layouts.
    auto* inputLayout = makeSubcellLayout(m_inputLabel, m_inputField);
    auto* outputLayout = makeSubcellLayout(m_outputLabel, m_outputField);

    // Apply the sub-cell layouts and stylesheets.
    m_inputSubcell->setStyleSheet("QWidget { background: #FFFFFF; }");
    m_inputSubcell->setLayout(inputLayout);
    m_outputSubcell->setStyleSheet("QWidget { background: #F5F5F5; }");
    m_outputSubcell->setLayout(outputLayout);

    // Place everything into the root layout.
    auto* rootLayout = new QVBoxLayout(this);
    rootLayout->setSpacing(0);
    rootLayout->addWidget(m_inputSubcell);
    rootLayout->addWidget(m_outputSubcell);

    // Hide the output cell initially.
    m_outputSubcell->setVisible(false);

    connect(m_inputField, &QLineEdit::returnPressed, this, &Cell::evaluateCurrentInput);
}

void Cell::evaluateCurrentInput()
{
    m_outputField->setText("TODO");
    showOutput();

    m_mainWindow->cellEvaluated(m_id);
}

void Cell::showOutput()
{
    m_outputSubcell->setVisible(true);
}
