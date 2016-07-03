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

#include "removedirectory.h"

#include <QDir>
#include <QDirIterator>

// Like QDir::removeRecursively() but doesn't remove the dir itself
static bool removeRecursively(QDir &dir)
{
    if (!dir.exists())
        return true;

    bool success = true;
    const QString dirPath = dir.path();

    QDirIterator di(dirPath, QDir::AllEntries | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
    while (di.hasNext()) {
        di.next();
        const QFileInfo& fi = di.fileInfo();
        const QString &filePath = di.filePath();
        bool ok;
        if (fi.isDir() && !fi.isSymLink()) {
            ok = QDir(filePath).removeRecursively(); // recursive
        } else {
            ok = QFile::remove(filePath);
            if (!ok) { // Read-only files prevent directory deletion on Windows, retry with Write permission.
                const QFile::Permissions permissions = QFile::permissions(filePath);
                if (!(permissions & QFile::WriteUser))
                    ok = QFile::setPermissions(filePath, permissions | QFile::WriteUser)
                        && QFile::remove(filePath);
            }
        }
        if (!ok)
            success = false;
    }

    return success;
}

RemoveDirectory::RemoveDirectory(QObject *parent)
    : Action(parent)
{
}

RemoveDirectory::~RemoveDirectory()
{
}

bool RemoveDirectory::execute()
{
    if (!m_folderName.startsWith("/") || m_folderName.size() == 1) {
        qWarning() << "RemoveDirectory: Won't try to remove non-absolute path, it's dangerous for you";
        return false;
    }

    QDir dir(m_folderName);
    qDebug() << "Removing" << m_folderName << "...";
    return m_removeItself ? dir.removeRecursively() : removeRecursively(dir);
}

QString RemoveDirectory::folderName() const
{
    return m_folderName;
}

void RemoveDirectory::setFolderName(const QString &folderName)
{
    if (m_folderName != folderName) {
        m_folderName = folderName;
        emit folderNameChanged();
    }
}

bool RemoveDirectory::removeItself() const
{
    return m_removeItself;
}

void RemoveDirectory::setRemoveItself(bool remove)
{
    if (m_removeItself != remove) {
        m_removeItself = remove;
        emit removeItselfChanged();
    }
}
