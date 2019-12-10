/*
  This file is part of onceagain.

  Copyright (C) 2019 Sérgio Martins <iamsergio@gmail.com>

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

#pragma once

#include "pythonaction.h"

class AddToQRCAction : public PythonAction
{
    Q_OBJECT
    Q_PROPERTY(QString qrcFilePath READ qrcFilePath WRITE setQrcFilePath NOTIFY qrcFilePathChanged)
    Q_PROPERTY(QString qrcLine READ qrcLine WRITE setQrcLine NOTIFY qrcLineChanged)
public:
    explicit AddToQRCAction(QObject *parent = nullptr);
    QString qrcFilePath() const;
    void setQrcFilePath(const QString &qrcFilePath);

    QString qrcLine() const;
    void setQrcLine(const QString &);
Q_SIGNALS:
    void qrcFilePathChanged();
    void qrcLineChanged();

private:
    QString m_qrcFilePath;
    QString m_qrcLine;
};
