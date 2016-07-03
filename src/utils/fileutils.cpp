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

#include <QFile>
#include <QDebug>

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
