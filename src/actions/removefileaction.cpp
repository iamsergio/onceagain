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

#include "removefileaction.h"

#include <QFile>

RemoveFileAction::RemoveFileAction(QObject *parent)
    : Action(parent)
{
}

QString RemoveFileAction::fileName() const
{
    return m_fileName;
}

void RemoveFileAction::setFileName(const QString &fileName)
{
    if (m_fileName != fileName) {
        m_fileName = fileName;
        Q_EMIT fileNameChanged();
    }
}

bool RemoveFileAction::execute_Impl()
{
    qDebug() << "Removing" << m_fileName;
    if (QFile::exists(m_fileName) && !QFile::remove(m_fileName)) {
        qWarning() << "RemoveFile:" << "Error removing file" << m_fileName;
        return false;
    }

    return true;
}
