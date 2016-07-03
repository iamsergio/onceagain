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

#ifndef SCRIPTPROXYMODEL_H
#define SCRIPTPROXYMODEL_H

#include <QSortFilterProxyModel>

class ScriptProxyModel : public QSortFilterProxyModel
{
public:
    explicit ScriptProxyModel(const QString &baseTargetPath, QObject *parent = nullptr);
    void setBaseTargetOnlyFolder(bool);
    void setBaseTargetOnlyFile(bool);
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
private:
    bool m_baseTargetOnlyFolder = false;
    bool m_baseTargetOnlyFile = false;
    const QString m_baseTargetPath;
};

#endif