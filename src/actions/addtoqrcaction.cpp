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

#include "addtoqrcaction.h"
#include "kernel.h"

AddToQRCAction::AddToQRCAction(QObject *parent)
    : PythonAction(parent)
{
    setName("AddToQRC");
    setPythonFileName("addtoqrc.py");
}

QString AddToQRCAction::qrcFilePath() const
{
    return m_qrcFilePath;
}

void AddToQRCAction::setQrcFilePath(const QString &qrcFilePath)
{
    if (m_qrcFilePath != qrcFilePath) {
        m_qrcFilePath = qrcFilePath;
        Q_EMIT qrcFilePathChanged();

        setVisible(!m_qrcFilePath.isEmpty());
    }
}

QString AddToQRCAction::qrcLine() const
{
    return m_qrcLine;
}

void AddToQRCAction::setQrcLine(const QString &line)
{
    if (m_qrcLine != line) {
        m_qrcLine = line;
        Q_EMIT qrcLineChanged();
    }
}
