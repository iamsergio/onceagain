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

#ifndef CREATEFOLDER_ACTION_H
#define CREATEFOLDER_ACTION_H

#include "action.h"
#include <QUrl>

class CreateFolderAction : public Action
{
    Q_OBJECT
    Q_PROPERTY(QString folderName READ folderName WRITE setFolderName NOTIFY folderNameChanged USER true)
    Q_PROPERTY(QUrl copyFrom READ copyFrom WRITE setCopyFrom NOTIFY copyFromChanged USER true);
public:
    explicit CreateFolderAction(QObject *parent = nullptr);

    QString folderName() const;
    void setFolderName(const QString &);

    QUrl copyFrom() const;
    void setCopyFrom(const QUrl &);

Q_SIGNALS:
    void folderNameChanged();
    void copyFromChanged();

protected:
    bool execute() override;

private:
    QString m_folderName;
    QUrl m_copyFrom;
};

#endif
