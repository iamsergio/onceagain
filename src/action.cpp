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

#include "action.h"

#include <QDebug>
#include <QMetaMethod>
#include <QScopeGuard>

Action::Action(QObject *parent)
    : QObject(parent)
    , m_description(tr("No description set"))
{
}

QString Action::name() const
{
    return m_name.isEmpty() ? metaObject()->className() : m_name;
}

void Action::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        Q_EMIT nameChanged();
    }
}

Action *Action::abortIfPreviousFailed() const
{
    return m_abortIfPreviousFailed;
}

void Action::setAbortIfPreviousFailed(Action *action)
{
    if (m_abortIfPreviousFailed != action) {
        m_abortIfPreviousFailed = action;
        Q_EMIT abortIfPreviousFailed();
    }
}

bool Action::inErrorState() const
{
    return m_inErrorState;
}

QString Action::description() const
{
    return m_description;
}

void Action::setDescription(const QString &desc)
{
    if (m_description != desc) {
        m_description = desc;
        Q_EMIT descriptionChanged();
    }
}

bool Action::enabled() const
{
    return m_enabled;
}

void Action::setEnabled(bool enabled)
{
    if (enabled != m_enabled) {
        m_enabled = enabled;
        Q_EMIT enabledChanged();
    }
}

QStringList Action::hiddenProperties() const
{
    return m_hiddenProperties;
}

void Action::setHiddenProperties(const QStringList &props)
{
    if (m_hiddenProperties != props) {
        m_hiddenProperties = props;
        Q_EMIT hiddenPropertiesChanged();
    }
}

bool Action::execute()
{
    if (!canExecute())
        return false;

    bool success = true;
    auto guard = qScopeGuard([this, &success] {
        if (success) {
            qDebug() << QString("%1: executed successfully").arg(name());
        } else {
            qWarning() << QString("%1: failed to run action!").arg(name());
        }
    });


    if (!execute_Impl()) {
        // First, execute our own action.
        success = false;
        return false;
    }

    // Then, execute our children's actions
    for (Action *action : m_childActions) {
        if (!action->enabled())
            continue;

        if (Action *previous = action->abortIfPreviousFailed()) {
            if (previous->inErrorState()) {
                m_inErrorState = true;
                continue;
            }
        }

        m_inErrorState = !action->execute();
        success &= !m_inErrorState;
    }

    return success;
}

bool Action::visible() const
{
    return m_visible;
}

void Action::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    m_visible = visible;
    Q_EMIT visibleChanged(m_visible);
}

bool Action::isDebug() const
{
    return m_isDebug;
}

void Action::setIsDebug(bool is)
{
    if (m_isDebug != is) {
        m_isDebug = is;
        Q_EMIT isDebugChanged();
    }
}

bool Action::canExecute() const
{
    return m_canExecute;
}

void Action::setCanExecute(bool can)
{
    if (can != m_canExecute) {
        m_canExecute = can;
        Q_EMIT canExecuteChanged(can);
    }
}

QQmlListProperty<Action> Action::childActions()
{
    return QQmlListProperty<Action>(this, m_childActions);
}

QUrl Action::defaultBaseTarget() const
{
    return m_defaultBaseTarget;
}

void Action::setDefaultBaseTarget(const QUrl &url)
{
    if (m_defaultBaseTarget != url) {
        m_defaultBaseTarget = url;
        Q_EMIT defaultBaseTargetChanged();
    }
}

bool Action::execute_Impl()
{
    return true;
}
