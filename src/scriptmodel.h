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

#ifndef SCRIPTMODEL_H
#define SCRIPTMODEL_H

#include "script.h"

#include <QStandardItemModel>
#include <QList>

class QStandardItem;

enum UserRole {
    ScriptRole = Qt::UserRole,
    FolderPathRole,
    IsFolder
};

class ScriptModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit ScriptModel(Kernel *kernel, QObject *parent = 0);
    ~ScriptModel();

    void loadScripts();
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    void loadScripts(const QString &folder, QStandardItem *parent);
    Kernel *const m_kernel;
};

#endif
