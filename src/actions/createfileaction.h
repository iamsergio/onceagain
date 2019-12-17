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

#ifndef CREATEFILEACTION_H
#define CREATEFILEACTION_H

#include "action.h"

class CreateFileAction : public Action
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged USER true)
    Q_PROPERTY(QString contents READ contents WRITE setContents NOTIFY contentsChanged USER true)
    Q_PROPERTY(QString copyFrom READ copyFrom WRITE setCopyFrom NOTIFY copyFromChanged USER true)
    Q_PROPERTY(bool useCamelCaseFileName READ useCamelCaseFileName WRITE setUseCamelCaseFileName NOTIFY useCamelCaseFileNameChanged)
public:
    explicit CreateFileAction(QObject *parent = nullptr);
    QString fileName() const;
    void setFileName(const QString &);
    QString contents() const;
    void setContents(const QString &);

    QString copyFrom() const;
    void setCopyFrom(const QString &);

    bool useCamelCaseFileName() const;
    void setUseCamelCaseFileName(bool);

Q_SIGNALS:
    void fileNameChanged();
    void contentsChanged();
    void copyFromChanged();
    void useCamelCaseFileNameChanged();

protected:
    bool execute_Impl() override;

private:
    bool createNewFile();
    bool copyFileFrom();

    QString m_fileName;
    QString m_contents;
    QString m_copyFrom;
    bool m_useCamelCaseFileName = false;
};

#endif
