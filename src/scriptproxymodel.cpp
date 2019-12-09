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

    return true;
}

void ScriptProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);

    // ScriptModel is static, so we can connect straight off the bat

    ScriptModel *scriptModel = qobject_cast<ScriptModel*>(sourceModel);
    Q_ASSERT(scriptModel);
    const int count = scriptModel->rowCount();
    for (int i = 0; i < count; ++i) {
        if (Script *script = scriptModel->script(sourceModel->index(i, 0))) {
            connect(script, &Script::visibleChanged, this, [this]{
                invalidateFilter();
            });
        }
    }
}
