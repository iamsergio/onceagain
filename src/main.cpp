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

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QStandardPaths>

static QString scriptsFolderPath()
{
    QByteArray scriptdirenv = qgetenv("ONCE_AGAIN_SCRIPTS_DIR");
    return scriptdirenv.isEmpty() ? QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                                  : QString::fromUtf8(scriptdirenv);
}

int main(int argv, char **argc)
{
    QApplication app(argv, argc);

    const QString baseTarget = app.arguments().size() < 2 ? QString(QLatin1Char('.'))
                                                          : app.arguments().at(1);

    Kernel kernel(scriptsFolderPath(), baseTarget);
    MainWindow mw(&kernel);
    mw.show();

    return app.exec();
}