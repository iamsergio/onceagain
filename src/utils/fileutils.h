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

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>

class FileUtils : public QObject
{
    Q_OBJECT
public:
    explicit FileUtils(QObject *parent = 0);
    Q_INVOKABLE QString read(const QString &filename) const;
    Q_INVOKABLE QString randomName(int length) const;

    /// @brief goes up the path until finding the first CMakeLists.txt
    /// Stops if it finds a .git or .svn
    Q_INVOKABLE QString firstCMakeFileFrom(const QString &path) const;

    /// @brief The absolute path which we're transforming into relative
    /// @brief relativeTo the absolute path that contains @p path
    Q_INVOKABLE QString relativePathFrom(const QString &path, QString relativeTo) const;
};

#endif
