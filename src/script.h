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

#ifndef ONCE_AGAIN_SCRIPT_H
#define ONCE_AGAIN_SCRIPT_H

#include <QUrl>
#include <QObject>
#include <QString>
#include <QList>
#include <QMetaProperty>

class QQuickItem;
class Action;
class FileUtils;
class StringUtils;
class CMakeUtils;
class Kernel;

class Script : public QObject
{
    Q_OBJECT

    ///@brief Returns if the script is visible to the user
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    typedef QList<Script*> List;
    explicit Script(const QUrl &source, Kernel *kernel);
    bool isValid() const;
    QString name() const;
    QList<QMetaProperty> configurableProperties() const;
    Action * rootAction() const;
    QString description() const;
    QUrl sourceUrl() const;
    QString baseTarget() const;

    bool execute() const;

    bool visible() const;
    void setVisible(bool visible);

Q_SIGNALS:
    void visibleChanged(bool visible);

private:
    void loadSourceQml();
    Action * m_rootAction = nullptr;
    const QUrl m_sourceQml;
    Kernel *const m_kernel;
    bool m_visible = true;
};

#endif
