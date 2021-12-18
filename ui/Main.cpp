//===-- ui/Main.cpp - UI entry point --------------------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include "MainWindow.h"
#include "Theme.h"

#include <QApplication>
#include <QPalette>
#include <QStyleFactory>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
    app.setFont(Theme::sansFont());
    app.setPalette(Theme::palette());

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
