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
        emit nameChanged();
    }
}

void Action::setAssertBaseTargetIsFolder(bool assert)
{
    if (assert != m_assertBaseTargetIsFolder) {
        m_assertBaseTargetIsFolder = assert;
        emit assertBaseTargetIsFolderChanged();
    }
}

bool Action::assertBaseTargetIsFolder() const
{
    return m_assertBaseTargetIsFolder;
}

bool Action::assertBaseTargetIsFile() const
{
    return m_assertBaseTargetIsFile;
}

void Action::setAssertBaseTargetIsFile(bool assert)
{
    if (assert != m_assertBaseTargetIsFile) {
        m_assertBaseTargetIsFile = assert;
        emit assertBaseTargetIsFileChanged();
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
        emit abortIfPreviousFailed();
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
        emit descriptionChanged();
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
        emit enabledChanged();
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
        emit hiddenPropertiesChanged();
    }
}

bool Action::execute()
{
    if (!canExecute())
        return false;

    bool success = true;
    int numActionsRun = 0;
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
        ++numActionsRun;
        success &= !m_inErrorState;
    }

    if (success) {
        if (numActionsRun > 0) {
            qDebug() << QString("%1: executed successfully").arg(name());
        } else {
            qDebug() << "No action was run";
        }
    } else {
        qWarning() << QString("%1: failed to run action!").arg(name());
    }

    return success;
}

bool Action::canExecute() const
{
    // The QML file might have a JavaScript function called canExecute(), which does some validations

    const bool methodExists = metaObject()->indexOfMethod("canExecute()") != -1;
    if (methodExists) {
        QVariant returnedValue;
        const bool methodWasCalled = QMetaObject::invokeMethod(const_cast<Action*>(this),
                                                               "canExecute",
                                                               Q_RETURN_ARG(QVariant, returnedValue));
        return methodWasCalled && returnedValue.toBool();
    } else {
        // No validations were needed
        return true;
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
        emit defaultBaseTargetChanged();
    }
}
