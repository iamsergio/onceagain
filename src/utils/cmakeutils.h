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

#ifndef CMAKEUTILS_H
#define CMAKEUTILS_H

#include <QObject>

class FileUtils;
class StringUtils;

class CMakeUtils : public QObject
{
    Q_OBJECT
public:
    explicit CMakeUtils(StringUtils *stringUtils, FileUtils *fileUtils, QObject *parent = 0);

    /**
     * Insert a word into a list of words, preserving alphabetical order.
     * The list is assumed to be separated by \n.
     * Indentation is also preserved.
     *
     * @param list The \n separated list of words.
     * @param newItem The word to be inserted
     * @return The new list
     */
    Q_INVOKABLE QString insertIntoTokenList(const QString &list, const QString &newItem) const;

    /**
     * Looks inside @p cmakeCode for the first SET instruction on @p variableName and returns
     * the list of tokens inside that SET()
     *
     * Example:
     * cmakeCode = (...)
     *             SET(SRC_BAR a.cpp
     *                         b.cpp
     *                         c.cpp)
     *             (...)
     *
     * variableName = "SRC_BAR"
     *
     * returns = "a.cpp\nb.cpp\c.cpp"
     */
    Q_INVOKABLE QString listForSET(const QString &variableName, const QString &cmakeCode) const;


    Q_INVOKABLE QString insertIntoSET(const QString &newItem,
                                      const QString &variableName,
                                      const QString &cmakeFilename);

private:
    StringUtils *const m_stringUtils;
    FileUtils *const m_fileUtils;
};

#endif
