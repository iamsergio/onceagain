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

#include "kernel.h"
#include "actions/createfolderaction.h"
#include "actions/createfileaction.h"
#include "actions/runcommand.h"
#include "actions/removedirectory.h"
#include "actions/removefileaction.h"

#include "fileutils.h"
#include "stringutils.h"
#include "cmakeutils.h"

#include "scriptmodel.h"

#include <QDir>
#include <QDebug>
#include <QQmlComponent>
#include <QFileInfo>
#include <QDir>

static void registerTypes()
{
    qmlRegisterType<Action>("OnceAgain", 1, 0, "Action");
    qmlRegisterType<CreateFolderAction>("OnceAgain", 1, 0, "CreateFolder");
    qmlRegisterType<CreateFileAction>("OnceAgain", 1, 0, "CreateFile");
    qmlRegisterType<RemoveDirectory>("OnceAgain", 1, 0, "RemoveDirectory");
    qmlRegisterType<RemoveFileAction>("OnceAgain", 1, 0, "RemoveFile");
    qmlRegisterType<RunCommand>("OnceAgain", 1, 0, "RunCommand");
}

Kernel::Kernel(const QString &scriptsFolder, const QString &baseTarget, QObject *parent)
    : QObject(parent)
    , m_scriptsFolder(scriptsFolder)
    , m_baseTarget(baseTarget)
    , m_fileUtils(new FileUtils(this))
    , m_stringUtils(new StringUtils(this))
    , m_cmakeUtils(new CMakeUtils(m_stringUtils, m_fileUtils, this))
    , m_scriptModel(new ScriptModel(this))
    , m_externalEditor(QString::fromUtf8(qgetenv("ONCE_AGAIN_EDITOR")))
    , m_externalFileExplorer(QString::fromUtf8(qgetenv("ONCE_AGAIN_FILE_EXPLORER")))
    , m_templatesFolder(m_scriptsFolder + QStringLiteral("/templates"))
{
    registerTypes();
    ensureFoldersExist();
}

FileUtils *Kernel::fileUtils() const
{
    return m_fileUtils;
}

StringUtils *Kernel::stringUtils() const
{
    return m_stringUtils;
}

CMakeUtils *Kernel::cmakeUtils() const
{
    return m_cmakeUtils;
}

QString Kernel::scriptsFolder() const
{
    return m_scriptsFolder;
}

QString Kernel::templatesFolder() const
{
    return m_templatesFolder;
}

QString Kernel::baseTarget() const
{
    return m_baseTarget;
}

void Kernel::setBaseTarget(const QString &target)
{
    if (m_baseTarget != target) {
        m_baseTarget = target;
        emit baseTargetChanged(target);
    }
}

ScriptModel *Kernel::scriptModel() const
{
    return m_scriptModel;
}

void Kernel::loadScripts()
{
    m_scriptModel->loadScripts();
}

QString Kernel::externalEditor() const
{
    return m_externalEditor;
}

QString Kernel::externalFileExplorer() const
{
    return m_externalFileExplorer;
}

void Kernel::ensureFoldersExist()
{
    ensureFolderExists(m_scriptsFolder);
    ensureFolderExists(m_templatesFolder);
}

void Kernel::ensureFolderExists(const QString &path)
{
    QFileInfo info(path);
    if (!info.exists()) {
        QDir dir;
        dir.mkpath(path);
    }
}
