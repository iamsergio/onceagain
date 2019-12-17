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

#include "fileutils.h"

#include <QFileInfo>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <stdlib.h>

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

FileUtils::FileUtils(QObject *parent)
    : QObject(parent)
{
#ifdef Q_OS_WIN
    srand(GetTickCount());
#else
    srand(time(0));
#endif
}

QString FileUtils::read(const QString &filename) const
{
    if (!QFile::exists(filename)) {
        qWarning() << Q_FUNC_INFO << "File doesn't exist" << filename;
        return QString();
    }

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString::fromUtf8(file.readAll());
    }

    return QString();
}

QString FileUtils::randomName(int length) const
{
    static const QString chars = QStringLiteral("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    QString result;
    result.reserve(length);

    for (int i = 0; i < length; ++i) {
        result.append(chars[rand() % chars.size()]);
    }

    return result;
}

QString FileUtils::firstCMakeFileFrom(const QString &path) const
{
    QFileInfo info(path);
    if (!info.exists(path) || !info.isDir())
        return {};

    QDir dir(path);
    const QStringList blockers = { ".git", ".svn" };

    do {
        const QString candidate = QStringLiteral("%1/CMakeLists.txt").arg(dir.path());
        if (QFileInfo::exists(candidate))
            return candidate;

        // For safety reasons, stop at the root of the repo
        for (const QString &blocker : blockers) {
            if (QFileInfo::exists(QStringLiteral("%1/%2").arg(dir.path(), blocker)))
                return {};
        }
    } while (dir.cdUp());

    return {};
}

QString FileUtils::relativePathFrom(const QString &path, QString relativeTo) const
{
    QFileInfo info(path);
    QFileInfo relativeToInfo(relativeTo);

    if (!info.exists()) {
        qWarning() << Q_FUNC_INFO << "Path doesn't exist" << path;
        return {};
    }

    if (!relativeToInfo.exists()) {
        qWarning() << Q_FUNC_INFO << "Path doesn't exist" << relativeTo;
        return {};
    }

    QDir relativeToDir(relativeToInfo.isFile() ? relativeToInfo.path()
                                               : relativeTo);

    if (info.absoluteFilePath().startsWith(relativeToDir.path())) {
        return info.absoluteFilePath().remove(0, relativeToDir.path().size() + 1); // +1 to remove the slash
    }

    return {};
}
