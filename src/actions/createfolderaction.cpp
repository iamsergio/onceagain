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

#include "createfolderaction.h"

#include <QDir>

CreateFolderAction::CreateFolderAction(QObject *parent)
    : Action(parent)
{
}

QString CreateFolderAction::folderName() const
{
    return m_folderName;
}

void CreateFolderAction::setFolderName(const QString &folderName)
{
    if (m_folderName != folderName) {
        m_folderName = folderName;
        emit folderNameChanged();
    }
}

bool CreateFolderAction::execute()
{
    if (m_folderName.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "foldername is emptyy";
        return false;
    }

    QDir dir;
    if (!dir.mkpath(m_folderName)) {
        qWarning() << "Error creating" << m_folderName;
        return false;
    }

    qDebug() << "Created" << m_folderName;
    return true;

}
