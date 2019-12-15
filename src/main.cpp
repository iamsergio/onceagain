/*
  This file is part of onceagain.

  Copyright (C) 2016 Sérgio Martins <iamsergio@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "kernel.h"
#include "mainwindow.h"

#include <Python.h>

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QStandardPaths>
#include <QFileInfo>
#include <QScopeGuard>

static QString scriptsFolderPath()
{
    QByteArray scriptdirenv = qgetenv("ONCE_AGAIN_SCRIPTS_DIR");
    return scriptdirenv.isEmpty() ? QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                                  : QString::fromUtf8(scriptdirenv);
}

static QString absolutePath(const QString &path)
{
    QString absolute;
    if (!path.isEmpty()) {
        QFileInfo info(path);
        absolute = info.absoluteFilePath();
        if (info.isDir())
            absolute += "/";
    }

    return absolute;
}

int main(int argv, char **argc)
{
    // Disable QML cache. Performance isn't noticeable on desktop. Let's not litter with *.qmlc files
    qputenv("QML_DISABLE_DISK_CACHE", "1");

    Py_Initialize();
    auto cleanPython = qScopeGuard([] {Py_Finalize(); });

    QApplication app(argv, argc);
    app.setWindowIcon(QIcon(":/onceagain.png"));

    const QString baseTarget = app.arguments().size() >= 2 ? absolutePath(app.arguments().at(1))
                                                           : QStringLiteral(".");


    if (!QFileInfo::exists(baseTarget)) {
        qWarning() << "Base target doesn't exist";
        return -1;
    }

    auto kernel = Kernel::create(scriptsFolderPath(), baseTarget);
    MainWindow mw(kernel);
    mw.show();

    return app.exec();
}
