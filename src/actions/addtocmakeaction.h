/*
  This file is part of onceagain.

  Copyright (C) 2019 Sérgio Martins <iamsergio@gmail.com>

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

#pragma once

#include "pythonaction.h"

class AddToCMakeAction : public PythonAction
{
    Q_OBJECT
    Q_PROPERTY(QString cmakeFilePath READ cmakeFilePath WRITE setCmakeFilePath NOTIFY cmakeFilePathChanged)
    Q_PROPERTY(QString cmakeVariable READ cmakeVariable WRITE setCmakeVariable NOTIFY cmakeVariableChanged)
    Q_PROPERTY(QString cmakeLine READ cmakeLine WRITE setCmakeLine NOTIFY cmakeLineChanged)
public:
    explicit AddToCMakeAction(QObject *parent = nullptr);

    QString cmakeFilePath() const;
    void setCmakeFilePath(const QString &cmakeFilePath);

    QString cmakeVariable() const;
    void setCmakeVariable(const QString &cmakeVariable);

    QString cmakeLine() const;
    void setCmakeLine(const QString &cmakeLine);

Q_SIGNALS:
    void cmakeFilePathChanged();
    void cmakeVariableChanged();
    void cmakeLineChanged();

private:
    QString m_cmakeFilePath;
    QString m_cmakeVariable;
    QString m_cmakeLine;
};
