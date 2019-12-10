/*
  This file is part of onceagain.

  Copyright (C) 2019 Sérgio Martins <iamsergio@gmail.com>

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

#include "addtocmakeaction.h"
#include "kernel.h"

AddToCMakeAction::AddToCMakeAction(QObject *parent)
    : PythonAction("addtocmakeaction.py", parent)
{
    if (Kernel::instance()->baseTarget().endsWith("CMakeLists.txt"))
        m_cmakeFilePath = Kernel::instance()->baseTarget();
}

QString AddToCMakeAction::cmakeFilePath() const
{
    return m_cmakeFilePath;
}

void AddToCMakeAction::setCmakeFilePath(const QString &cmakeFilePath)
{
    if (m_cmakeFilePath == cmakeFilePath)
        return;

    m_cmakeFilePath = cmakeFilePath;
    Q_EMIT cmakeFilePathChanged();
}