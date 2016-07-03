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

#ifndef CREATECLASSACTION_H
#define CREATECLASSACTION_H

#include "createfileaction.h"

class CreateClassAction : public CreateFileAction
{
    Q_OBJECT
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(QString includeGuard READ includeGuard WRITE setIncludeGuard NOTIFY includeGuardChanged)
public:
    explicit CreateClassAction(QObject *parent = nullptr);

    QString className() const;
    void setClassName(const QString &);

    QString includeGuard() const;
    void setIncludeGuard(const QString &);

Q_SIGNALS:
    void classNameChanged();
    void useCamelCaseFileNameChanged();
    void includeGuardChanged();

protected:
    bool execute() override;

private:
    QString m_className;
    QString m_includeGuard;
};

#endif
