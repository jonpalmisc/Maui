//===-- ui/Main.cpp - UI entry point --------------------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of Maui, an open source UI for the Wolfram Engine. The
// source code for Maui is available at <https://github.com/jonpalmisc/Maui>.
//
//===----------------------------------------------------------------------===//

#include "ConfigDialog.h"
#include "MainWindow.h"
#include "Theme.h"

#include <QApplication>
#include <QPalette>
#include <QSettings>
#include <QStyleFactory>

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationDomain("com.jonpalmisc");
    QCoreApplication::setApplicationName("Maui");

    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
    app.setPalette(Theme::palette());
    app.setStyleSheet(Theme::stylesheet());
    app.setFont(Theme::sansFont());

    // Load the user's settings, clearing them if requested.
    QSettings settings;
    if (app.arguments().contains("-reset"))
        settings.clear();

    // Use the default kernel path or prompt the user to choose a kernel.
    auto kernelPath = settings.value("engine/kernelPath").toString();
    if (kernelPath.isEmpty()) {
        auto* configDialog = new ConfigDialog(true);
        if (configDialog->exec() != QDialog::Accepted)
            return 1;

        // Use the kernel path chosen in the dialog; set as default if requested.
        kernelPath = configDialog->kernelPath();
        if (configDialog->wantsPathAsDefault())
            settings.setValue("engine/kernelPath", kernelPath);
    }

    auto mainWindow = new MainWindow(kernelPath);
    mainWindow->show();

    return app.exec();
}
