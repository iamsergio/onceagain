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
#include <QFileInfo>
#include <QProcess>

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

QUrl CreateFolderAction::copyFrom() const
{
    return m_copyFrom;
}

void CreateFolderAction::setCopyFrom(const QUrl &copyFrom)
{
    if (m_copyFrom != copyFrom) {
        m_copyFrom = copyFrom;
        emit copyFromChanged();
    }
}

bool CreateFolderAction::execute()
{
    if (m_folderName.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "foldername is empty";
        return false;
    }

    const QString copyFrom = m_copyFrom.toLocalFile();
    if (m_copyFrom.isValid()) {
        QFileInfo info(copyFrom);
        if (!info.exists()) {
            qWarning() << Q_FUNC_INFO << "Dir doesn't exist" << copyFrom;
            return false;
        } else if (!info.isDir()) {
            qWarning() << Q_FUNC_INFO << "Path isn't a directory" << copyFrom;
            return false;
        }
    }

    QDir dir;
    if (!dir.mkpath(m_folderName)) {
        qWarning() << "Error creating" << m_folderName;
        return false;
    }

    if (m_copyFrom.isValid()) {
        QProcess process;
        QString command = QStringLiteral("rsync -av %1/ %2/").arg(copyFrom, m_folderName);
        qDebug() << "Running blocking command" << command;
        process.start(command);
        process.waitForFinished();
    }

    qDebug() << "Created" << m_folderName;
    return true;

}
