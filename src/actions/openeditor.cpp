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

#include "openeditor.h"
#include "kernel.h"

#include <QProcess>
#include <QDir>

OpenEditor::OpenEditor(QObject *parent)
    : RunCommand(parent)
{
    setCommand(editorCommand());
}

void OpenEditor::setFilename(const QString &filename)
{
    if (m_filename != filename) {
        m_filename = filename;
        emit filenameChanged();
        setCommand(editorCommand());
    }
}

QString OpenEditor::filename() const
{
    return m_filename;
}

QString OpenEditor::editorCommand() const
{
    return Kernel::instance()->externalEditor().arg(filename());
}