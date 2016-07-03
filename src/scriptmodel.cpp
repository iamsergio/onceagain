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

#include "scriptmodel.h"
#include "kernel.h"

#include <QDir>
#include <QUrl>
#include <QDebug>
#include <QFileInfo>
#include <QFileInfoList>
#include <QApplication>
#include <QFont>

ScriptModel::ScriptModel(Kernel *kernel, QObject *parent)
    : QStandardItemModel(parent)
    , m_kernel(kernel)
{
}

ScriptModel::~ScriptModel()
{
}

void ScriptModel::loadScripts()
{
    clear();
    beginResetModel();
    loadScripts(m_kernel->scriptsFolder(), invisibleRootItem());
    endResetModel();
}

QVariant ScriptModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QStandardItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags ScriptModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant ScriptModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::FontRole) {
        QFont f = qApp->font();
        f.setBold(data(index, IsFolder).toBool());
        return f;
    }

    return QStandardItemModel::data(index, role);
}

void ScriptModel::loadScripts(const QString &folder, QStandardItem *parent)
{
    QDir dir(folder);
    const QFileInfoList infos = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs | QDir::Readable);
    for (const auto &info : infos) {
        if (info.isFile() && info.fileName().endsWith(QStringLiteral(".qml"))) {
            auto script = new Script(QUrl::fromLocalFile(info.absoluteFilePath()), m_kernel);
            if (script->isValid()) {
                auto item = new QStandardItem(script->name());
                item->setData(QVariant::fromValue(script), ScriptRole);
                item->setData(folder, FolderPathRole);
                item->setData(false, IsFolder);
                parent->appendRow(item);
            }
        } else if (info.isDir() && info.fileName() != QStringLiteral("templates")) {
            auto item = new QStandardItem(info.fileName());
            item->setData(info.absoluteFilePath(), FolderPathRole);
            item->setData(true, IsFolder);
            parent->appendRow(item);
            loadScripts(info.absoluteFilePath(), item);
        }
    }
}
