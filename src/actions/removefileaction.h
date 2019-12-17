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

#ifndef REMOVE_FILE_ACTION_H
#define REMOVE_FILE_ACTION_H

#include "action.h"

class RemoveFileAction : public Action
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged USER true)
public:
    explicit RemoveFileAction(QObject *parent = nullptr);
    QString fileName() const;
    void setFileName(const QString &);

Q_SIGNALS:
    void fileNameChanged();

protected:
    bool execute_Impl() override;

private:
    QString m_fileName;
};

#endif
