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

#ifndef ONCE_MORE_KERNEL_H
#define ONCE_MORE_KERNEL_H

#include "script.h"

#include <QObject>

class QString;
class FileUtils;
class StringUtils;
class ScriptModel;
class Action;

class Kernel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString externalEditor READ externalEditor CONSTANT)
    Q_PROPERTY(QObject* currentAction READ currentAction NOTIFY currentActionChanged)
public:
    static Kernel* create(const QString &scriptsFolder, const QString &baseTarget, QObject *parent = nullptr);
    static Kernel* instance();

    FileUtils *fileUtils() const;
    StringUtils *stringUtils() const;
    CMakeUtils *cmakeUtils() const;

    QString scriptsFolder() const;
    QString templatesFolder() const;

    QString baseTarget() const;

    ScriptModel *scriptModel() const;
    void loadScripts();

    QString externalEditor() const;
    QString externalFileExplorer() const;

    Action *currentAction() const;
    void setCurrentAction(Action *);

Q_SIGNALS:
    void baseTargetChanged(const QString &);
    void currentActionChanged(Action*);

private:
    explicit Kernel(const QString &scriptsFolder, const QString &baseTarget, QObject *parent = 0);
    void ensureFoldersExist();
    void ensureFolderExists(const QString &path);
    const QString m_scriptsFolder;
    QString m_baseTarget;
    FileUtils *const m_fileUtils;
    StringUtils *const m_stringUtils;
    CMakeUtils *const m_cmakeUtils;
    ScriptModel *const m_scriptModel;
    const QString m_externalEditor;
    const QString m_externalFileExplorer;
    const QString m_templatesFolder;
    Action *m_currentAction = nullptr;
};

Q_DECLARE_METATYPE(Kernel*)

#endif
