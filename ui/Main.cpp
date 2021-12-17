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
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#CACACA"));
    palette.setColor(QPalette::WindowText, QColor("#2C2C2C"));
    palette.setColor(QPalette::Text, QColor("#2C2C2C"));
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor("#8E8E8E"));

    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
    app.setFont(Theme::sansFont());
    app.setPalette(palette);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
