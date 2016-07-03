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

#ifndef REMOVEDIRECTORY_H
#define REMOVEDIRECTORY_H

#include "action.h"

class RemoveDirectory : public Action
{
    Q_OBJECT
    Q_PROPERTY(QString folderName READ folderName WRITE setFolderName NOTIFY folderNameChanged USER true)
    Q_PROPERTY(bool removeItself READ removeItself WRITE setRemoveItself NOTIFY removeItselfChanged USER true)
public:
    explicit RemoveDirectory(QObject *parent = nullptr);
    ~RemoveDirectory();

    QString folderName() const;
    void setFolderName(const QString &);

    bool removeItself() const;
    void setRemoveItself(bool);

Q_SIGNALS:
    void folderNameChanged();
    void removeItselfChanged();

protected:
    bool execute() override;

private:
    QString m_folderName;
    bool m_removeItself = false;
};

#endif
