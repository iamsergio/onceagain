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

#include "scriptproxymodel.h"
#include "scriptmodel.h"
#include "action.h"

#include <QFileInfo>
#include <script.h>

ScriptProxyModel::ScriptProxyModel(const QString &baseTargetPath, QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_baseTargetPath(baseTargetPath)
{
}

void ScriptProxyModel::setBaseTargetOnlyFolder(bool only)
{
    if (only != m_baseTargetOnlyFolder) {
        m_baseTargetOnlyFolder = only;
        invalidateFilter();
    }
}

void ScriptProxyModel::setBaseTargetOnlyFile(bool only)
{
    if (only != m_baseTargetOnlyFile) {
        m_baseTargetOnlyFile = only;
        invalidateFilter();
    }
}

bool ScriptProxyModel::filterAcceptsRow(int source_row, const QModelIndex &parent) const
{
    if (!sourceModel())
        return false;

    Script *script = sourceModel()->index(source_row, 0, parent).data(ScriptRole).value<Script*>();
    if (!script) {
        // It's a folder with scripts
        return true;
    }

    if (!script->visible())
        return false;

    Action *action = script->rootAction();
    if (!action)
        return false;

    QFileInfo info(m_baseTargetPath);

    if (action->assertBaseTargetIsFolder() && !info.isDir())
        return false;

    if (action->assertBaseTargetIsFile() && !info.isFile())
        return false;

    return true;
}
