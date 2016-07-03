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

#include "cmakeutils.h"
#include "stringutils.h"
#include "fileutils.h"

#include <QString>
#include <QStringList>
#include <QDebug>

CMakeUtils::CMakeUtils(StringUtils *stringUtils, FileUtils *fileUtils, QObject *parent)
    : QObject(parent)
    , m_stringUtils(stringUtils)
    , m_fileUtils(fileUtils)
{
}

static int indentation(const QString &s)
{
    int count = 0;
    for (auto c : s) {
        if (c.isSpace())
            ++count;
        else
            break;
    }
    return count;
}

QString CMakeUtils::insertIntoTokenList(const QString &list, const QString &newItem) const
{
    QStringList lines = list.split("\n");
    const int firstItemIndentation = lines.isEmpty() ? 0 : indentation(lines.first());
    const int lastItemIndentation = lines.isEmpty() ? 0 : indentation(lines.last());

    std::transform(lines.cbegin(), lines.cend(), lines.begin(), [](const QString &s) {
        return s.trimmed();
    });

    lines.push_back(newItem);
    lines.sort(Qt::CaseInsensitive);

    if (firstItemIndentation > 0)
        lines[0] = lines[0].rightJustified(firstItemIndentation);

    for (int i = 1, num = lines.size(); i < num; ++i) {
        lines[i] = QString(lastItemIndentation, ' ') + lines[i];
    }

    return lines.join(QLatin1String("\n"));
}

QString CMakeUtils::listForSET(const QString &variableName, const QString &cmakeCode) const
{
    return m_stringUtils->subString(cmakeCode, QString("SET\\(%1(.*?)\\)").arg(variableName));
}

QString CMakeUtils::insertIntoSET(const QString &newItem, const QString &variableName, const QString &cmakeFilename)
{
    QString cmakeContents = m_fileUtils->read(cmakeFilename);
    const QString srcList = listForSET(QString("%1").arg(variableName), cmakeContents);
    const QString newList = insertIntoTokenList(srcList, newItem);
    return cmakeContents.replace(srcList, newList);
}
