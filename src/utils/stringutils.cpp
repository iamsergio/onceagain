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

#include "stringutils.h"

#include <QRegularExpression>
#include <QDebug>

StringUtils::StringUtils(QObject *parent)
    : QObject(parent)
{

}

QString StringUtils::camelCase(const QString &input, const QString &separator) const
{
    QStringList tokens = input.split(separator, QString::SkipEmptyParts);
    const int numTokens = tokens.size();
    for (int i = 0; i < numTokens; ++i)
        tokens[i].replace(0, 1, tokens[i][0].toUpper());

    return tokens.join(QString());
}

QString StringUtils::subString(const QString &hayStack, const QString &rx) const
{
    QRegularExpression re(rx, QRegularExpression::CaseInsensitiveOption | QRegularExpression::DotMatchesEverythingOption);
    auto m = re.match(hayStack);
    return m.captured(1);
}
