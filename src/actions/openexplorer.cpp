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

#include "openexplorer.h"
#include "kernel.h"

#include <QProcess>
#include <QDir>

OpenExplorer::OpenExplorer(QObject *parent)
    : RunCommand(parent)
{
    setCommand(explorerCommand());
}

void OpenExplorer::setPath(const QUrl &path)
{
    if (m_path != path) {
        m_path = path;
        emit pathChanged();
        setCommand(explorerCommand());
    }
}

QUrl OpenExplorer::path() const
{
    return m_path;
}

QString OpenExplorer::explorerCommand() const
{
    const auto &cmd = Kernel::instance()->externalFileExplorer();
    return cmd.contains(QLatin1String("%1")) ? cmd.arg(QDir::toNativeSeparators(path().toLocalFile()))
                                             : cmd;
}
