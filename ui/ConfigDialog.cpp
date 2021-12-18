//===-- ui/ConfigDialog.cpp - Program settings dialog ---------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include "ConfigDialog.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ConfigDialog::ConfigDialog(bool isAtStartup, QWidget* parent)
    : QDialog(parent)
    , m_kernelPathField(new QLineEdit)
    , m_useDefaultCheckbox(new QCheckBox("Use as default kernel"))
{
    // Create a button so kernel paths can be chosen interactively.
    auto* browseButton = new QPushButton("Browse...");
    connect(browseButton, &QPushButton::clicked, [this] {
        auto path = QFileDialog::getOpenFileName(this, "Select Wolfram Kernel", "");
        m_kernelPathField->setText(path);
    });

    // Create the save and quit buttons; only show the quit button if the
    // dialog was opened during the startup process.
    auto* saveButton = new QPushButton("Save");
    auto* quitButton = new QPushButton("Quit");
    quitButton->setVisible(isAtStartup);

    // Connect both buttons to the appropriate action.
    connect(quitButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);

    // Group the path layout field and browse button.
    auto* pathLayout = new QHBoxLayout;
    pathLayout->addWidget(m_kernelPathField);
    pathLayout->addWidget(browseButton);

    // Group the dialog buttons.
    auto* buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addWidget(saveButton);

    // Build the root layout.
    auto* rootLayout = new QVBoxLayout(this);
    rootLayout->addWidget(new QLabel("Kernel path:"));
    rootLayout->addLayout(pathLayout);
    rootLayout->addWidget(m_useDefaultCheckbox);
    rootLayout->addLayout(buttonLayout);
    rootLayout->addStretch(1);

    setMinimumWidth(384);
    setWindowTitle("Amu Configuration");
}

QString ConfigDialog::kernelPath() const
{
    return m_kernelPathField->text().replace(" ", "\\ ") + " -mathlink";
}

bool ConfigDialog::wantsPathAsDefault() const
{
    return m_useDefaultCheckbox->isChecked();
}
