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

#include "createfileaction.h"

#include <QFile>
#include <QTextStream>

CreateFileAction::CreateFileAction(QObject *parent)
    : Action(parent)
{
}

QString CreateFileAction::fileName() const
{
    return m_fileName;
}

void CreateFileAction::setFileName(const QString &fileName)
{
    if (m_fileName != fileName) {
        m_fileName = fileName;
        emit fileNameChanged();
    }
}

QString CreateFileAction::contents() const
{
    return m_contents;
}

void CreateFileAction::setContents(const QString &contents)
{
    if (contents != m_contents) {
        m_contents = contents;
        emit contentsChanged();
    }
}

QString CreateFileAction::copyFrom() const
{
    return m_copyFrom;
}

void CreateFileAction::setCopyFrom(const QString &copy)
{
    if (copy != m_copyFrom) {
        m_copyFrom = copy;
        emit copyFrom();
    }
}

bool CreateFileAction::execute()
{
    if (m_copyFrom.isEmpty()) {
        return createNewFile();
    } else {
        return copyFileFrom();
    }
}

bool CreateFileAction::createNewFile()
{
    if (m_fileName.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "filename is empty";
        return false;
    }

    QFile file(m_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file" << m_fileName << "; error=" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    out << m_contents;

    qDebug() << "Created" << m_fileName;
    return true;
}

bool CreateFileAction::copyFileFrom()
{
    qDebug() << "Copying from " << m_copyFrom << " to " << m_fileName;
    return QFile::copy(m_copyFrom, m_fileName);
}

bool CreateFileAction::useCamelCaseFileName() const
{
    return m_useCamelCaseFileName;
}

void CreateFileAction::setUseCamelCaseFileName(bool use)
{
    if (m_useCamelCaseFileName != use) {
        m_useCamelCaseFileName = use;
        emit useCamelCaseFileNameChanged();
    }
}

