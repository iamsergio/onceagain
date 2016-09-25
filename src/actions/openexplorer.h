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

#ifndef ONCE_AGAIN_OPENEXPLORER_H
#define ONCE_AGAIN_OPENEXPLORER_H

#include "runcommand.h"
#include <QUrl>

class OpenExplorer: public RunCommand
{
    Q_OBJECT
    Q_PROPERTY(QString command READ command CONSTANT)
    Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathChanged)
public:
    explicit OpenExplorer(QObject *parent = nullptr);

    void setPath(const QUrl &);
    QUrl path() const;

Q_SIGNALS:
    void commandChanged();
    void pathChanged();

private:
    QString explorerCommand() const;
    QUrl m_path;
};

#endif
