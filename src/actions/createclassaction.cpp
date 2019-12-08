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

#include "createclassaction.h"

CreateClassAction::CreateClassAction(QObject *parent)
    : CreateFileAction(parent)
{
}

QString CreateClassAction::className() const
{
    return m_className;
}

void CreateClassAction::setClassName(const QString &name)
{
    if (name != m_className) {
        m_className = name;
        Q_EMIT classNameChanged();
    }
}

QString CreateClassAction::includeGuard() const
{
    return m_includeGuard;
}

void CreateClassAction::setIncludeGuard(const QString &guard)
{
    if (m_includeGuard != guard) {
        m_includeGuard = guard;
        Q_EMIT includeGuardChanged();
    }
}

bool CreateClassAction::execute()
{
    return CreateFileAction::execute();
}
