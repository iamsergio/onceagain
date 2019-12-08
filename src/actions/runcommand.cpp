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

#include "runcommand.h"

#include <QProcess>
#include <QDir>

RunCommand::RunCommand(QObject *parent)
    : Action(parent)
{
}

QString RunCommand::command() const
{
    return m_command;
}

void RunCommand::setCommand(const QString &command)
{
    if (command != m_command) {
        m_command = command;
        Q_EMIT commandChanged();
    }
}

void RunCommand::setWorkingDirectory(const QString &dir)
{
    if (dir != m_workingDirectory) {
        m_workingDirectory = dir;
        Q_EMIT workingDirectoryChanged();
    }
}

QString RunCommand::workingDirectory() const
{
    return m_workingDirectory;
}

bool RunCommand::execute()
{
    if (m_command.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Command is empty";
        return false;
    }

    auto process = new QProcess(this);
    if (!m_workingDirectory.isEmpty()) {
        QDir dir(m_workingDirectory);
        if (!dir.exists()) {
            qWarning() << Q_FUNC_INFO << m_workingDirectory << "doesn't exist";
            return false;
        }

        process->setWorkingDirectory(m_workingDirectory);
    }

    connect(process, static_cast<void (QProcess::*)(int,QProcess::ExitStatus)>(&QProcess::finished), [this](int exitCode, QProcess::ExitStatus) {
        Q_EMIT processFinished(exitCode);
    });

    connect(this, &RunCommand::processFinished, process, &QObject::deleteLater);

    qDebug() << Q_FUNC_INFO << "Running" << m_command;
    process->start(m_command);
    return true;
}
